#!/bin/bash

# Check if commit message is provided
if [ -z "$1" ]; then
    echo "Error: Please provide a commit message"
    echo "Usage: $0 \"your commit message\""
    exit 1
fi

# Check if there are any changes to commit
if [[ -n $(git status --porcelain) ]]; then
    # Add all changes
    git add .
    
    # Commit with provided message
    git commit -m "$1"
    
    # Push to remote repository
    git push
    
    echo "Changes committed and pushed successfully with message: $1"
else
    echo "No changes to commit"
fi
