// snake_text_gui.c
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/time.h>    // Für struct timeval
#include "snake_logic.h"

#define WIDTH 20
#define HEIGHT 10
#define FPS 5

// Spielfeld initialisieren
void init_field(char field[HEIGHT][WIDTH]) {
    for (int i = 0; i < HEIGHT; i++) {
        for (int j = 0; j < WIDTH; j++) {
            field[i][j] = ' ';
        }
    }
}

// Schlange ins Spielfeld zeichnen
void draw_snake(char field[HEIGHT][WIDTH], Snake *snake) {
    for (int i = 0; i < snake->size; i++) {
        int x = snake->body[i].x;
        int y = snake->body[i].y;
        if (x >= 0 && x < WIDTH && y >= 0 && y < HEIGHT) {
            field[y][x] = 'O'; // Schlangenkörper
        }
    }
}

// Spielfeld auf der Konsole darstellen
void render_field(char field[HEIGHT][WIDTH]) {
    // Konsole leeren (ANSI Escape Code)
    printf("\033[H\033[J");

    // Rahmen zeichnen
    for (int i = 0; i < WIDTH + 2; i++) printf("#");
    printf("\n");

    for (int i = 0; i < HEIGHT; i++) {
        printf("#"); // linke Grenze
        for (int j = 0; j < WIDTH; j++) {
            printf("%c", field[i][j]);
        }
        printf("#\n"); // rechte Grenze
    }

    for (int i = 0; i < WIDTH + 2; i++) printf("#");
    printf("\n");
}

// Eingaben verarbeiten (mit getchar)
Direction get_input(Direction currentDir) {
    if (1==1) { // Prüfen, ob eine Taste gedrückt wurde
        char ch = getchar();
        switch (ch) {
            case 'w': return UP;
            case 's': return DOWN;
            case 'a': return LEFT;
            case 'd': return RIGHT;
        }
    }
    return currentDir;
}

int main() {
    // Erstelle das Spielfeld
    char field[HEIGHT][WIDTH];

    // Erstelle eine Schlange
    Snake *snake = snake_create(WIDTH / 2, HEIGHT / 2, 3, RIGHT);

    Direction dir = RIGHT;
    int running = 1;

    while (running) {
        // Initialisiere das Spielfeld
        init_field(field);

        // Eingabe holen
        dir = get_input(dir);

        // Bewege die Schlange
        snake_change_direction(snake, dir);
        snake_move(snake);

        // Schlange ins Spielfeld zeichnen
        draw_snake(field, snake);

        // Spielfeld rendern
        render_field(field);

        // FPS kontrollieren (warte für eine Weile)
        usleep(1000000 / FPS);
    }

    // Speicher freigeben
    snake_destroy(snake);
    return 0;
}
