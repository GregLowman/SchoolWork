#!/bin/bash
git status 
git add
read -p "Enter files to stage: " files
git add ${files:-.}
read -p "Enter commit message: " message
git commit -m "$message"
git pull 
git push
