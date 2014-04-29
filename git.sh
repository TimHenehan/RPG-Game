#!/bin/bash

cd $(dirname $0)

#git remote add origin https://github.com/andy29485/RPG-Game.git

git pull https://github.com/andy29485/RPG-Game.git

git add -A
git commit
git push origin master
