echo "Building snake game"
gcc main.c -IC:/msys64/mingw64/include -IC:/msys64/mingw64/include/ncurses -LC:/msys64/mingw64/lib -lncurses -lncursesw -o snake_game.exe
