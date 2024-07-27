#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <conio.h>
#include <ctype.h>
#include <windows.h>
#include <process.h>
#include <ncurses.h>
#include <unistd.h>
#include <stdbool.h>

// constants
#define SCREEN_WIDTH 60
#define SCREEN_HEIGHT 40
#define MAX_SCORE 256
#define FRAME_TIME 110000

typedef struct {
    int x, y;
} Vector2D;

//global variables
Vector2D segments[MAX_SCORE + 1];
int score = 0;
WINDOW *win;
 // snake parts
Vector2D head = {0, 0};
Vector2D dir = {1, 0};
// berry
Vector2D berry;
//score
char score_message[15];
// game state
bool is_running = true;

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
    
     // initialize color
    if (has_colors() == FALSE) {
        endwin();
        fprintf(stderr, "Your terminal does not support color\n");
        exit(1);
    }
    start_color();
    use_default_colors();
    init_pair(1, COLOR_RED, -1);
    init_pair(2, COLOR_GREEN, -1);
    init_pair(3, COLOR_YELLOW, -1);


    berry.x = rand() % width;
    berry.y = rand() % height;

    // update score message
    sprintf(score_message, "[ Score: %d ]", score);
}

void quit_game()
{
     // exit cleanly from application
    endwin();
    // clear screen, place cursor on top, and un-hide cursor
    printf("\e[1;1H\e[2J");
    printf("\e[?25h");

    exit(0);
}

void restart_game() {
    head.x = 0;
    head.y = 0;
    dir.x = 1;
    dir.y = 0;
    score = 0;
    sprintf(score_message, "[ Score: %d ]", score);
    is_running = true;
}

void draw_border(int y, int x, int width, int height) {
    // top row
    mvaddch(y, x, ACS_ULCORNER);
    mvaddch(y, x + width * 2 + 1, ACS_URCORNER);
    for (int i = 1; i < width * 2 + 1; i++) {
        mvaddch(y, x + i, ACS_HLINE);
    }
    // vertical lines
    for (int i = 1; i < height + 1; i++) {
        mvaddch(y + i, x, ACS_VLINE);
        mvaddch(y + i, x + width * 2 + 1, ACS_VLINE);
    }
    // bottom row
    mvaddch(y + height + 1, x, ACS_LLCORNER);
    mvaddch(y + height + 1, x + width * 2 + 1, ACS_LRCORNER);
    for (int i = 1; i < width * 2 + 1; i++) {
        mvaddch(y + height + 1, x + i, ACS_HLINE);
    }
}

void input_keyboard(WINDOW *win)
{
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
                quit_game();
                break;
            case 'q':
                restart_game();
                break;
                
        }
}
int main(int argc, char **argv) {
    //init screen
    init(SCREEN_HEIGHT , SCREEN_WIDTH);
    // game loop
    while (true) {
        // pressed key
        input_keyboard(win);
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
