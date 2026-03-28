#!/bin/bash

git add . || { echo "git add failed"; exit 1; }
read -p "commit message >:" msg
git commit -m "$msg" || { echo "git commit failed"; exit 1; }
echo "message committed..."
git push origin "$(git branch --show-current)"|| { echo "git push failed"; exit 1; }
