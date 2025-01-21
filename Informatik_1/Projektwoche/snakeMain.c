#include <windows.h>
#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <time.h>
#include <locale.h>
#include <math.h>
#include "snakeLib.h"
#include "titleScreen.h"

#define MAX_X 20
#define MAX_Y 20

#define EMPTYSPACE ". "
#define FOODSPACE 'O'
#define SNAKESPACE 'S'

HANDLE h;
COORD coord;
Food food;
int score;
char screen[MAX_Y][MAX_X * 2];

void initScreen(Snake* snake) {
    for (int y = 0; y < MAX_Y; y++) {
        for (int x = 0; x < MAX_X; x++) {
            screen[y][x * 2] = EMPTYSPACE[0];
            screen[y][x * 2 + 1] = EMPTYSPACE[1];
        }
        screen[y][MAX_X * 2 - 1] = '\n';
    }
    screen[MAX_Y][MAX_X * 2 - 1] = '\0'; // Null terminator for string

    for (int i = 0; i < snake->size; i++) {
        screen[snake->body[i].y][snake->body[i].x] = SNAKESPACE;
    }
}

void spawnFood(Snake* snake) {
    bool foodInsideSnake;
    do {
        foodInsideSnake = false;
        food.pos.x = 2 * (rand() % (MAX_X - 1)); // Ensure it's within bounds
        food.pos.y = rand() % (MAX_Y - 1);
        
        for (int i = 0; i < snake->size; i++) {
            if (same_position(snake->body[i], food.pos)) {
                foodInsideSnake = true;
                break;
            }
        }
    } while (foodInsideSnake);

    food.value = 1000;
    screen[food.pos.y][food.pos.x] = FOODSPACE;
}

void deathAnimation(Snake* snake){
    for(int i = snake->size-1; i >= 0; i--){
    screen[snake->body[0].y][snake->body[0].x] = 'X';
    SetConsoleCursorPosition(h, coord);
    printf(screen[0]);
    Sleep(25 * i / (snake->size-1));
    screen[snake->body[0].y][snake->body[0].x] = SNAKESPACE;
    screen[snake->body[i].y][snake->body[i].x] = *EMPTYSPACE;
    SetConsoleCursorPosition(h, coord);
    printf(screen[0]);
    Sleep(25 * i / (snake->size-1));
    }
}

bool gameTick(Snake *snake, Direction dir) {
    Position direction = {0, 0};
    switch (dir) {
        case UP: direction.y = -1; break;
        case DOWN: direction.y = 1; break;
        case LEFT: direction.x = -2; break;
        case RIGHT: direction.x = 2; break;
    }

    Position snakeHead = add_position(snake->body[0], direction);
    if (snakeHead.x < 0 || snakeHead.y < 0 || snakeHead.x >= MAX_X * 2 || snakeHead.y >= MAX_Y) {
        deathAnimation(snake);
        return true; // Wall collision
    }

    screen[snakeHead.y][snakeHead.x] = SNAKESPACE;

    Position tailBuffer = snake->body[snake->size - 1];
    bool collisionWithSnake = false;

    for (int i = snake->size - 1; i >= 1; i--) {
        if (same_position(snake->body[i], snakeHead)) {
            collisionWithSnake = true;
        }
        snake->body[i] = snake->body[i - 1];
    }

    snake->body[0] = snakeHead;

    if (same_position(snakeHead, food.pos)) {
        snake->body[snake->size] = tailBuffer;
        snake->size++;
        score += food.value;
        spawnFood(snake);
    } else {
        screen[tailBuffer.y][tailBuffer.x] = EMPTYSPACE[0];
    }

    if (collisionWithSnake) {
        deathAnimation(snake);
        return true;
    }
    return false;
}

int main() {
    while (1) { // Restart mechanism instead of `goto`
        system("chcp 437 > nul");
        srand(time(NULL));
        h = GetStdHandle(STD_OUTPUT_HANDLE);
        coord.X = 0;
        coord.Y = 0;
        int taste;
        int game_over = 0;
        char ch;
        Direction dirLast;
        score = 0;

        Position startPos = {2 * (MAX_X / 2), MAX_Y / 2}; 
        int initial_size = 5;
        Direction initial_direction = RIGHT;
        Snake* snake = snake_create(initial_size, initial_direction, startPos, MAX_X * MAX_Y, 2);

        setlocale(LC_ALL, ""); 
        system("cls");
        titleScreen();
        while ((ch = getch()) != 13) {}

        system("cls");
        initScreen(snake);
        spawnFood(snake);

        do {
            if (dirLast) {
                if (snake->dir != dirLast && food.value > 0) {
                    food.value -= 100;
                }
            }

            game_over = gameTick(snake, snake->dir);
            dirLast = snake->dir;

            SetConsoleCursorPosition(h, coord);
            printf(screen[0]);
            printf("\nSCORE: %i\tFOOD VALUE: %i \n", score, food.value);

            Sleep(50 / (sqrt(snake->size) / initial_size));

            if (kbhit()) {
                taste = getch();
                if (taste == 224) {
                    taste = getch();
                    switch (taste) {
                        case 72: if (snake->dir != DOWN) snake->dir = UP; break;
                        case 80: if (snake->dir != UP) snake->dir = DOWN; break;
                        case 75: if (snake->dir != RIGHT) snake->dir = LEFT; break;
                        case 77: if (snake->dir != LEFT) snake->dir = RIGHT; break;
                    }
                }
            }
        } while (!game_over);

        printf("\n'q' to quit, 'ENTER' to restart\n");
        if (getch() == 'q') break;

        free(snake->body);
        free(snake);
    }
    return 0;
}
