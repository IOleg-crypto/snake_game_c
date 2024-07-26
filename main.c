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
//constants
#define SCREEN_WIDTH 80
#define SCREEN_HEIGHT 25

typedef struct
{
     int x , y;
} Vector2D;

int main(int argc , char **argv)
{
    //initialise screen
    WINDOW *win = initscr();
    
    //take player input
    keypad(win, true);
    nodelay(win, true);
    curs_set(0);
    
    //snake parts
    Vector2D head = {0 , 0};
    Vector2D dir = {1 , 0};
    
    //game loop
    while (true)
    {
        //pressed key
        int pressed = wgetch(win);
        switch (pressed){
            case KEY_UP:
              dir.x = -1;
              dir.y = 0;
              break;
            case KEY_DOWN:
              dir.x = 1;
              dir.y = 0;
              break;
            case KEY_LEFT:
              dir.x = 0;
              dir.y = -1;
              break;
            case KEY_RIGHT:
              dir.x = 0;
              dir.y = 1;
              break;
            if (pressed == '\e')
            {
                break;
            }
        }
    }
}