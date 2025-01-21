#include <windows.h>
#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <time.h>
#include <locale.h>
#include <math.h>
#include "snakeLib.h"
#include "titleScreen.h"
#include "deathScreen.h"
#include <string.h>

#define MAX_X 45
#define MAX_Y 25

#define EMPTYSPACE ". "
#define FOODSPACE 'O'
#define SNAKESPACE 'S'

#define MAX_LINE 256
#define MAX_ENTRIES 200
#define TEMP_FILE "temp_score.txt"
#define SCORE_FILE "score.txt"

HANDLE h;
COORD coord;
Food food;
int score;
char screen[MAX_Y][MAX_X * 2];

int safeScore(char* userName, int userScore){
    FILE *file = fopen(SCORE_FILE, "r"); // Open file for reading
    if (file == NULL) {
        printf("Error opening file!\n");
        return 1;
    }

    FILE *temp = fopen(TEMP_FILE, "w"); // Temporary file for writing updated data
    if (temp == NULL) {
        printf("Error opening temp file!\n");
        fclose(file);
        return 1;
    }

    char line[MAX_LINE];
    int found = 0; // Flag to check if user exists

    while (fgets(line, sizeof(line), file) != NULL) {
        char name[MAX_LINE];
        int score;
        
        if (sscanf(line, "%[^|]|%d", name, &score) == 2) { // Read "name|score"
            if (strcmp(name, userName) == 0) { // Check if user exists
                found = 1;
                if (userScore > score) { 
                    fprintf(temp, "%s|%d\n", name, userScore); // Update score
                } else {
                    fprintf(temp, "%s|%d\n", name, score); // Keep old score
                }
            } else {
                fprintf(temp, "%s|%d\n", name, score); // Copy other users
            }
        }
    }

    // If the user wasn't found, add them
    if (!found) {
        fprintf(temp, "%s|%d\n", userName, userScore);
    }

    fclose(file);
    fclose(temp);

    // Replace the old file with the new one
    remove(SCORE_FILE);
    rename(TEMP_FILE, SCORE_FILE);
    return 0;
}

// Struktur für einen Score-Eintrag
typedef struct {
    char name[MAX_LINE];
    int score;
} ScoreEntry;

// Vergleichsfunktion für qsort (absteigende Reihenfolge)
int compareScores(const void *a, const void *b) {
    return ((ScoreEntry *)b)->score - ((ScoreEntry *)a)->score;
}

void displayTopScores() {
    ScoreEntry scores[MAX_ENTRIES];
    int count = 0;

    FILE *file = fopen(SCORE_FILE, "r");
    if (file == NULL) {
        printf("Fehler: Konnte die Score-Datei nicht öffnen!\n");
        return;
    }

    // Einlesen der Scores aus der Datei
    while (fscanf(file, "%49[^|]|%d\n", scores[count].name, &scores[count].score) == 2) {
        count++;
        if (count >= MAX_ENTRIES) break;  // Verhindert das Überlaufen des Arrays
    }
    fclose(file);

    if (count == 0) {
        printf("Keine Scores vorhanden!\n");
        return;
    }

    // Sortiere die Scores in absteigender Reihenfolge
    qsort(scores, count, sizeof(ScoreEntry), compareScores);

    // Ausgabe der Top 10 Scores
    printf("\n===== TOP 10 SCORES =====\n");
    for (int i = 0; i < count && i < 10; i++) {
        printf("%d. %s - %d\n", i + 1, scores[i].name, scores[i].score);
    }
    printf("=========================\n");
}

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
        while ((ch = getch()) != 13) {if(ch =='q') return 0;}

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

        system("cls");
        deathScreen();
        printf("\nSCORE: %i                            \n", score);

        char input = getch();

        if(input == 'q') break;
        if(input == 's'){
            char username[MAX_LINE];
            printf("enter username\n");
            scanf("%s", username);
            safeScore(username,score);
        }
        if(input == 'h'){
            displayTopScores();
            input = getch();
            if(input == 'q') break;
            if(input == 's'){
                char username[MAX_LINE];
                printf("enter username\n");
                scanf("%s", username);
                safeScore(username,score);
            }
        }

        free(snake->body);
        free(snake);
    }
    return 0;
}
