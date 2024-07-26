#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <conio.h>
#include <time.h>
#include <ctype.h>
#include <time.h>
#include <windows.h>
#include <process.h>
#include <curses.h>

int main(int argc , char **argv)
{
    int screen_width = 80;
    int screen_height = 25;

    initscr();
    curs_set(0);
    noecho();
    cbreak();
    srand(time(NULL));
    
    
    return 0;
}