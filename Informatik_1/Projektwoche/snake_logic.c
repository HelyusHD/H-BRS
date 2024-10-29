// snake_logic.c
#include <stdio.h>
#include <stdlib.h>
#include "snake_logic.h"

// Erstelle eine Schlange mit einer Startgröße und einer Startposition
Snake* snake_create(int startX, int startY, int startSize, Direction startDir) {
    Snake *snake = (Snake *)malloc(sizeof(Snake));
    snake->size = startSize;
    snake->dir = startDir;

    snake->body = (Position *)malloc(startSize * sizeof(Position));

    for (int i = 0; i < startSize; i++) {
        snake->body[i].x = startX - i;
        snake->body[i].y = startY;
    }

    return snake;
}

// Zerstöre die Schlange
void snake_destroy(Snake *snake) {
    free(snake->body);
    free(snake);
}

// Bewege die Schlange
void snake_move(Snake *snake) {
    for (int i = snake->size - 1; i > 0; i--) {
        snake->body[i] = snake->body[i - 1];
    }

    switch (snake->dir) {
        case UP:
            snake->body[0].y -= 1;
            break;
        case DOWN:
            snake->body[0].y += 1;
            break;
        case LEFT:
            snake->body[0].x -= 1;
            break;
        case RIGHT:
            snake->body[0].x += 1;
            break;
    }
}

// Ändere die Bewegungsrichtung
void snake_change_direction(Snake *snake, Direction newDir) {
    snake->dir = newDir;
}
