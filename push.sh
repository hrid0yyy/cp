#!/bin/bash

# Check if in a git repository
if ! git rev-parse --is-inside-work-tree >/dev/null 2>&1; then
    echo "Error: Not in a git repository"
    exit 1
fi

# Load .env file
if [ -f .env ]; then
    source .env
else
    echo "Error: .env file not found in current directory"
    exit 1
fi

# Check if Groq API key is set in .env
if [ -z "$GROQ_API_KEY" ]; then
    echo "Error: GROQ_API_KEY not set in .env file"
    exit 1
fi

# Check for changes in the working directory
if [[ -n $(git status --porcelain) ]]; then
    echo "Staging all changes..."
    # Stage all changes
    git add .
    
    # Verify staged changes
    if [[ -z $(git diff --staged) ]]; then
        echo "Error: No changes were staged. Possible .gitignore or empty changes."
        git status
        exit 1
    fi
    
    # Capture git diff of staged changes
    DIFF=$(git diff --staged)
    
    # Debug: Show diff size
    echo "Staged changes detected (size: $(echo "$DIFF" | wc -l) lines)"
    
    # Prepare prompt for Groq API
    PROMPT="Analyze the following git diff and generate a concise, professional commit message (max 50 words) summarizing the changes:\n\n$DIFF"
    
    # Escape newlines and quotes for JSON
    ESCAPED_PROMPT=$(echo -n "$PROMPT" | sed ':a;N;$!ba;s/\n/\\n/g' | sed 's/"/\\"/g')
    
    # Call Groq API to generate commit message
    RESPONSE=$(curl -s -w "\n%{http_code}" -X POST https://api.groq.com/openai/v1/chat/completions \
        -H "Authorization: Bearer $GROQ_API_KEY" \
        -H "Content-Type: application/json" \
        -d '{
            "model": "llama-3.3-70b-versatile",
            "messages": [
                {
                    "role": "user",
                    "content": "'"$ESCAPED_PROMPT"'"
                }
            ],
            "max_tokens": 100,
            "temperature": 0.7
        }')
    
    # Extract HTTP status code (last line of response)
    HTTP_STATUS=$(echo "$RESPONSE" | tail -n 1)
    
    # Extract response body (remove HTTP status code)
    RESPONSE_BODY=$(echo "$RESPONSE" | sed -e '$d')
    
    # Debug: Log raw API response to a file
    echo "$RESPONSE_BODY" > groq_api_response.json
    echo "Debug: Raw API response saved to groq_api_response.json"
    
    # Check HTTP status
    if [ "$HTTP_STATUS" != "200" ]; then
        echo "Error: Groq API request failed with HTTP status $HTTP_STATUS"
        echo "Check groq_api_response.json for details"
        # Fallback commit message
        COMMIT_MSG="Update on $(date +'%Y-%m-%d %H:%M:%S')"
        echo "Warning: Using fallback commit message due to API failure"
    else
        # Extract commit message from response
        COMMIT_MSG=$(echo "$RESPONSE_BODY" | grep -o '"content":"[^"]*"' | sed 's/"content":"//' | sed 's/"$//' | head -n 1)
        
        if [ -z "$COMMIT_MSG" ]; then
            # Fallback commit message if parsing fails
            COMMIT_MSG="Update on $(date +'%Y-%m-%d %H:%M:%S')"
            echo "Warning: Failed to parse commit message from Groq API response, using fallback"
            echo "Check groq_api_response.json for details"
        fi
    fi
    
    # Commit with generated message
    git commit -m "$COMMIT_MSG"
    
    # Push to remote repository
    git push
    
    echo "Changes committed and pushed successfully with message: $COMMIT_MSG"
else
    echo "No changes to commit"
    git status
fi