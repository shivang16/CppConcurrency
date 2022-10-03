#!/bin/sh

CUR_DIR=$(pwd)
PROJECT_DIR="${CUR_DIR}"
FILES_TO_PUSH=$(git status --porcelain | awk '{print $2}')
FILES_CHANGES=$(git status --porcelain | awk '{print $1}')
ECHO "Git status is:" $(git status --porcelain);
ECHO "File Changes are: "$FILES_CHANGES
ECHO "Files to push are: "$FILES_TO_PUSH;
NAME=(`echo ${FILES_TO_PUSH}`);
CHANGES=(`echo ${FILES_CHANGES}`);

for i in "${!CHANGES[@]}"; do
    ECHO "Currently processing file: "${NAME[$i]}
    if [ ${CHANGES[$i]}  == "D" ]; then  
        COMMIT_MESSAGE="${NAME[$i]} DELETED";
    elif [ ${CHANGES[$i]}  == "M" ]; then  
        COMMIT_MESSAGE="${NAME[$i]} MODIFIED";
    elif [ ${CHANGES[$i]}  == "??" ]; then  
        COMMIT_MESSAGE="${NAME[$i]} ADDED";
    elif [ ${CHANGES[$i]}  == "AM" ]; then  
        COMMIT_MESSAGE="${NAME[$i]} ADDED";
    fi
    git add ${NAME[$i]};
    ECHO "Commit message is: $COMMIT_MESSAGE";    
    git commit -m "$COMMIT_MESSAGE";
    git push
done