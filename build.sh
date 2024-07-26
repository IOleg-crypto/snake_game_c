#!/bin/bash

echo "Building snake game"

gcc main.c -IC:/msys64/mingw64/include -IC:/msys64/mingw64/include/ncurses -LC:/msys64/mingw64/lib -lncurses -lncursesw -o snake_game.exe

if [ $? -eq 0 ]; then
    echo "Success"
else
    echo "Failure"
fi
