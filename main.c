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
#define SCREEN_HEIGHT 25
#define MAX_SCORE 256
#define FRAME_TIME 110000

typedef struct {
    int x, y;
} Vector2D;

typedef struct {
    Vector2D segments[MAX_SCORE + 1];
    int score;
    WINDOW *win;
    Vector2D head;
    Vector2D dir;
    Vector2D berry;
    char score_message[15];
    bool is_running;
} GameState;

void update_snake_position(Vector2D *head, Vector2D dir) {
    head->x += dir.x;
    head->y += dir.y;
}

void draw_snake(WINDOW *win, Vector2D head, Vector2D *segments, int score) {
    mvwaddch(win, head.y, head.x * 2, 'O');
    for (int i = 0; i < score; i++) {
        mvwaddch(win, segments[i].y, segments[i].x * 2, 'o');
    }
}

void draw_berry(WINDOW *win, Vector2D berry) {
     mvwaddch(win, berry.y, berry.x * 2, '*');
}

void check_boundaries(Vector2D *head, int width, int height) {
    if (head->x >= width * 2) 
        head->x = 0;
    else if (head->x < 0) 
        head->x = width - 1;
    if (head->y >= height) 
        head->y = 0;
    else if (head->y < 0) 
        head->y = height - 1;
}

void init(GameState *state, int width, int height) {
    // initialise screen
    initscr();
    cbreak();
    noecho();
    curs_set(0);
    srand(time(NULL));

    // set up window
    state->win = initscr();
    scrollok(state->win, TRUE);
    keypad(state->win, TRUE);
    nodelay(state->win, TRUE);
    
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

    state->berry.x = rand() % width;
    state->berry.y = rand() % height;

    // update score message
    sprintf(state->score_message, "[ Score: %d ]", state->score);
}

void quit_game() {
    // exit cleanly from application
    endwin();
    // clear screen, place cursor on top, and un-hide cursor
    printf("\e[1;1H\e[2J");
    printf("\e[?25h");

    exit(0);
}

void restart_game(GameState *state) {
    state->head.x = 0;
    state->head.y = 0;
    state->dir.x = 1;
    state->dir.y = 0;
    state->score = 0;
    sprintf(state->score_message, "[ Score: %d ]", state->score);
    state->is_running = true;
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

void input_keyboard(GameState *state) {
    int pressed = wgetch(state->win);
    switch (pressed) {
        case KEY_UP:
            state->dir.x = 0;
            state->dir.y = -1;
            break;
        case KEY_DOWN:
            state->dir.x = 0;
            state->dir.y = 1;
            break;
        case KEY_LEFT:
            state->dir.x = -1;
            state->dir.y = 0;
            break;
        case KEY_RIGHT:
            state->dir.x = 1;
            state->dir.y = 0;
            break;
        case 'w':
            state->dir.x = 0;
            state->dir.y = -1;
            break;
        case 's':
            state->dir.x = 0;
            state->dir.y = 1;
            break;
        case 'a':
            state->dir.x = -1;
            state->dir.y = 0;
            break;
        case 'd':
            state->dir.x = 1;
            state->dir.y = 0;
            break;
        case 'e':
            quit_game();
            break;
        case 'q':
            restart_game(state);
            break;
    }
}

void collide_berry_and_snake(GameState *state) {
    state->score += 1;
    state->berry.x = rand() % SCREEN_WIDTH / 4;
    state->berry.y = rand() % SCREEN_HEIGHT / 4;
}

int main(int argc, char **argv) {
    GameState state = {
        .score = 0,
        .head = {0, 0},
        .dir = {1, 0},
        .is_running = true
    };

    init(&state, SCREEN_WIDTH, SCREEN_HEIGHT);

    // game loop
    while (true) {
        // pressed key
        input_keyboard(&state);
        update_snake_position(&state.head, state.dir);
        
        // update segments
        for (int i = state.score; i > 0; i--) {
            state.segments[i].x = state.segments[i - 1].x;
            state.segments[i].y = state.segments[i - 1].y;
        }
        state.segments[0].x = state.head.x;
        state.segments[0].y = state.head.y;
        
        //--draw snake--
        werase(state.win);
        draw_border(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT);
        draw_berry(state.win, state.berry);
        draw_snake(state.win, state.head, state.segments, state.score);

        if (state.head.x == state.berry.x && state.head.y == state.berry.y) {
            collide_berry_and_snake(&state);
        }

        mvwprintw(state.win, 0, 0, "Score: %d", state.score);

        // check screen boundaries
        check_boundaries(&state.head, SCREEN_WIDTH, SCREEN_HEIGHT);

        wrefresh(state.win);
        usleep(FRAME_TIME);
    }

    endwin();
    return 0;
}
