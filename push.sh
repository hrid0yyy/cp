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
    
    # Call Groq API to generate commit message
    RESPONSE=$(curl -s -X POST https://api.groq.com/openai/v1/chat/completions \
        -H "Authorization: Bearer $GROQ_API_KEY" \
        -H "Content-Type: application/json" \
        -d '{
            "model": "llama-3.3-70b-versatile",
            "messages": [
                {
                    "role": "user",
                    "content": "'"${PROMPT}"'"
                }
            ],
            "max_tokens": 100,
            "temperature": 0.7
        }')
    
    # Extract commit message from response
    COMMIT_MSG=$(echo "$RESPONSE" | grep -o '"content":"[^"]*"' | sed 's/"content":"//' | sed 's/"$//')
    
    if [ -z "$COMMIT_MSG" ]; then
        # Fallback commit message if API fails
        COMMIT_MSG="Update on $(date +'%Y-%m-%d %H:%M:%S')"
        echo "Warning: Failed to generate commit message from Groq API, using fallback"
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