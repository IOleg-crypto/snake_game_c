#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <conio.h>
#include <ctype.h>
#include <windows.h>
#include <process.h>
#include <ncurses.h>
#include <unistd.h>

// constants
#define SCREEN_WIDTH 25
#define SCREEN_HEIGHT 15
#define MAX_SCORE 256
#define FRAME_TIME 110000

typedef struct {
    int x, y;
} Vector2D;

Vector2D segments[256];
int score = 0;
WINDOW *win;

void update_snake_position(Vector2D *head, Vector2D dir) {
    head->x += dir.x;
    head->y += dir.y;
}

void draw_snake(WINDOW *win, Vector2D head, Vector2D *segments, int score) {
    for (int i = 0; i < score; i++) {
        mvwaddch(win, segments[i].y, segments[i].x *7 , 'o');
    }
    mvwaddch(win, head.y, head.x * 2, 'O');
}

void draw_berry(WINDOW *win, Vector2D berry) {
    mvwaddch(win, berry.y, berry.x * 2, '@');
}

void check_boundaries(Vector2D *head, int width, int height) {
     if (head->x >= width * 2) 
         head->x = 0;
    else if (head->x < 0) 
        head->x = width - 1;
    if (head->y >= height * 2) 
        head->y = 0;
    else if (head->y < 0) 
        head->y = height - 1;
}

void init(int width , int height) {
   // initialise screen
    initscr();
    cbreak();
    noecho();
    curs_set(0);
    srand(time(NULL));

    // set up window
    win = newwin(height, width * 2, 0, 0);
    keypad(win, TRUE);
    nodelay(win, TRUE);
}

int main(int argc, char **argv) {
    //init screen
    init(SCREEN_HEIGHT , SCREEN_WIDTH);
    // snake parts
    Vector2D head = {0, 0};
    Vector2D dir = {1, 0};

    // berry
    Vector2D berry = {rand() % SCREEN_WIDTH, rand() % SCREEN_HEIGHT};

    // game loop
    while (true) {
        // pressed key
        int pressed = wgetch(win);
        switch (pressed) {
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
                endwin();
                exit(0);
        }

        update_snake_position(&head, dir);

        //--draw snake--
        werase(win);
        draw_berry(win, berry);
        draw_snake(win, head, segments, score);

        if (head.x == berry.x && head.y == berry.y) {
            score += 1;
            berry.x = rand() % SCREEN_WIDTH / 4;
            berry.y = rand() % SCREEN_HEIGHT / 4;
        }

        mvwprintw(win, 0, 0, "Score: %d", score);

        // check screen boundaries
        check_boundaries(&head, SCREEN_WIDTH, SCREEN_HEIGHT);

        wrefresh(win);
        usleep(100000);
    }

    endwin();
    return 0;
}
