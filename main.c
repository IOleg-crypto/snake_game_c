#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <conio.h>
#include <time.h>
#include <ctype.h>
#include <windows.h>
#include <process.h>
#include <curses.h>
#include <unistd.h>
//constants
#define SCREEN_WIDTH 80
#define SCREEN_HEIGHT 25

typedef struct
{
     int x , y;
} Vector2D;

Vector2D segments[256];

int score = 0;

int main(int argc , char **argv)
{
    //initialise screen
    WINDOW *win = initscr();
    
    //take player input
    keypad(win, true);
    nodelay(win, true);
    curs_set(0);
    srand(time(NULL));
    
    //snake parts
    Vector2D head = {0 , 0};
    Vector2D dir = {1 , 0};
    
    //berry
    Vector2D berry = {rand() % SCREEN_WIDTH , rand() % SCREEN_HEIGHT};
    
    //game loop
    while (true)
    {
        //pressed key
        int pressed = wgetch(win);
        switch (pressed){
            case KEY_UP:
              dir.x = 0;
              dir.y = -1;
              break;
            case KEY_DOWN:
              dir.x = 0;
              dir.y = 1;
              break;
            case KEY_LEFT:
              dir.x = -1;
              dir.y = 0;
              break;
            case KEY_RIGHT:
              dir.x = 1;
              dir.y = 0;
              break;
            case 'w':
              dir.x = 0;
              dir.y = -1;
              break;
            case 's':
              dir.x = 0;
              dir.y = 1;
              break;
            case 'a':
              dir.x = -1;
              dir.y = 0;
              break;
            case 'd':
              dir.x = 1;
              dir.y = 0;
              break; 
            case 'e':
              exit(0);
        }
        head.x += dir.x;
        head.y += dir.y;
        
        //--draw snake--
        
        erase();
        mvaddch(berry.y, berry.x * 2, '@');
        
        //make snake length
        for (int i = 0; i < score; i++)
        {
            mvaddch(segments[i].y, segments[i].x *2 , 'o');
        }
        mvaddch(head.y, head.x, '0');
        if (head.x == berry.x && head.y == berry.y)
        {
            score += 1;
            berry.x = rand() % SCREEN_WIDTH;
            berry.y = rand() % SCREEN_HEIGHT;
        }
        
        mvprintw(0, 0, "Score: %d" , score);
        
    
        //check screen boundaries
        if (head.x >= SCREEN_WIDTH) head.x = 0;
        else if (head.x < 0) head.x = SCREEN_WIDTH - 1;
        if (head.y >= SCREEN_HEIGHT) head.y = 0;
        else if (head.y < 0) head.y = SCREEN_HEIGHT - 1;
          
        usleep(100000);
    }
    endwin();
    return 0;
}