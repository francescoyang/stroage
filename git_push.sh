#!/bin/sh
git init
git add .
git commit -m 'qt storage manager'
git remote add origin git@github.com:acanoe/stroage.git
git push -f git@github.com:acanoe/stroage.git  master 
