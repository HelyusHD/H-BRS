#include <windows.h>
#include <stdio.h>
#include <stdlib.h> // um den terminal zu leeren
#include <conio.h>
#include <time.h>
#include <unistd.h>
#include <locale.h>
#include "snakeLib.h"
#include "titleScreen.h"

#define MAX_X 80
#define MAX_Y 25

#define EMPTYSPACE '.'
#define FOODSPACE 'O'
#define SNAKESPACE 'S'

HANDLE h;
COORD coord;
Position food;
char screen[MAX_Y][MAX_X];


void initScreen(Snake* snake)
{
    for(int y = 0; y < MAX_Y; y++){
        for(int x = 0; x < MAX_X; x++){
            for(int i=0; i <= snake->size-1; i++){
                Position snakePos = snake->body[i];
                screen[y][x] = EMPTYSPACE;
            }
        }
        screen[y][MAX_X-1] = '\n';
    }
    screen[MAX_Y-1][MAX_X] = '\0';
    for(int i = 0; i < snake->size; i++){
        screen[snake->body[i].y][snake->body[i].x] = SNAKESPACE;
    }
}

void spawnFood(Snake* snake){
    bool foodInsideSnake;
    do{
    foodInsideSnake = false;
    food.x = rand() % (MAX_X-1);
    food.y = rand() % (MAX_Y-1);
    for(int i=0; i < snake->size; i++){
        if(same_position(snake->body[i],food)){
            foodInsideSnake = true;
            break;
        }
    }
    }while(foodInsideSnake);
    screen[food.y][food.x] = FOODSPACE;
}



bool gameTick(Snake *snake, Direction dir){
    //calculating new snake head position
    Position direction = {0, 0};
    switch(dir){
        case UP :
            if(snake->dir != DOWN){direction.y = -1;}
            break;
        case DOWN:
            if(snake->dir != UP){direction.y = 1;}
            break;
        case LEFT:
            if(snake->dir != RIGHT){direction.x = -1;}
            break;
        case RIGHT:
            if(snake->dir != LEFT){direction.x = 1;}
            break;
    }
    Position snakeHead = add_position(snake->body[0], direction);
    if(snakeHead.x < 0 || snakeHead.y < 0 || snakeHead.x > MAX_X-1 || snakeHead.y > MAX_Y-1){return true;} // death by wall

    // setting new position of snake
    screen[snakeHead.y][snakeHead.x] = SNAKESPACE;

    // shifting positions of segments
    Position tailBuffer = snake->body[snake->size-1]; // if we grow we copy the tail back into existence
    bool collisionWithSnake = false;
    for(int i=snake->size-1; i >= 1; i--){
        // death by self eating
        if(same_position(snake->body[i], snakeHead)){
            collisionWithSnake = true;
        }
        snake->body[i] = snake->body[i-1];
    }
    // moving head of snake
    snake->body[0] = snakeHead;

    // eating food
    if(same_position(snakeHead, food)){
        snake->body[snake->size] = tailBuffer;
        snake->size++;
        spawnFood(snake);
    }else{
        screen[tailBuffer.y][tailBuffer.x] = EMPTYSPACE;
    }

    // blinking death animation for death by self collision
    if(collisionWithSnake){
        for(int i = snake->size-1; i >= 0; i--){
            screen[snake->body[0].y][snake->body[0].x] = SNAKESPACE;
            screen[snake->body[i].y][snake->body[i].x] = EMPTYSPACE;
            SetConsoleCursorPosition(h, coord);
            printf(screen[0]);
            Sleep(50);
            screen[snake->body[0].y][snake->body[0].x] = 'X';
            SetConsoleCursorPosition(h, coord);
            printf(screen[0]);
            Sleep(50);
        }
        return true;
    }
    return false;
}


int main(){
    STARTAGAIN:
    // Codepage 437 aktivieren
    system("chcp 437 > nul");
    srand (time(NULL));
    h = GetStdHandle ( STD_OUTPUT_HANDLE );
    coord.X = 0;
    coord.Y = 0;
    int taste;
    int game_over = 0;
    clock_t start_time;
    char ch;


    Position startPos = {10, 13}; // {x|y}
    int initial_size = 8;
    Direction initial_direction = RIGHT;
    Snake* snake = snake_create(initial_size, initial_direction, startPos, MAX_X * MAX_Y);

    setlocale(LC_ALL, ""); // Setze die Locale für UTF-8
    SetConsoleCursorPosition(h, coord);
    titleScreen();
    printf("\033[31mDies ist roter Text.\n");
    while ((ch = getch()) != 13) {}
    system("cls"); // Terminal leeren (nur Windows)

    initScreen(snake);
    spawnFood(snake);

    // ticke-clock
    do {
        start_time = clock();
        game_over = gameTick(snake, snake -> dir);
        SetConsoleCursorPosition(h, coord);
        printf(screen[0]);
        //while((clock() - start_time) / (float)CLOCKS_PER_SEC <= 0.25){
        if(1) {
            Sleep(50); // 50 ms Pause
            if(kbhit()){
                taste = getch();
                if (taste == 224) { // Sondertasten starten mit 224
                    taste = getch(); // zweiten Wert lesen
                    
                    // Verarbeitung der Pfeiltasten
                    switch (taste) {
                        case 72: // Pfeiltaste nach oben
                            snake -> dir = UP;
                        break;
                        case 80: // Pfeiltaste nach unten
                             snake -> dir = DOWN;
                        break;
                        case 75: // Pfeiltaste nach links
                             snake -> dir = LEFT;
                        break;
                        case 77: // Pfeiltaste nach rechts
                             snake -> dir = RIGHT;
                        break;
                    }
                }
            }
        }
    } 
    while(!game_over);

    printf("\n'q' to quit.\n");
    printf("\nPress ENTER to start the game\n");
    // Endlosschleife, bis 'q' gedrückt wird
    while (1) {
        ch = getch(); // Wartet auf einen Tastendruck
        if (ch == 13){
            goto STARTAGAIN;
        }
        if (ch == 'q' || ch == 'Q') {
            break; // Schleife beenden, wenn 'q' oder 'Q' gedrückt wurde
        }
    }
    printf("Programm beendet.\n");
    
    free(snake->body);
    free(snake);
    return 0;
}