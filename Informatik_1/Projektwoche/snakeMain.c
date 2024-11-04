#include <windows.h>
#include <stdio.h>
#include <stdlib.h> // um den terminal zu leeren
#include <conio.h>
#include <time.h>
#include <unistd.h>
#include <locale.h>
#include "snakeLib.h"
#include "titleScreen.h"

int max_x, max_y;
HANDLE h;
COORD coord; 



void printScreen(Snake* snake)
{
    char screen[max_y][max_x];
    for(int y = 0; y<= max_y-1; y++){
        for(int x = 0; x<= max_x-2; x++){
            int foundSnake = 0;
            for(int i=0; i <= snake->size-1; i++){
                Position snakePos = snake->body[i];
                if(snakePos.x == x && snakePos.y == y){
                    foundSnake = 1;
                }
                if(foundSnake == 1){
                    screen[y][x] = 'S';
                }
                else{
                    screen[y][x] = '.';
                }
            }
        }
        screen[y][max_x-1] = '\n';
    }
    screen[max_y-1][max_x-1] = '\0';
    //system("cls"); // Terminal leeren (nur Windows)
    SetConsoleCursorPosition(h, coord);
    printf(screen[0]);
}



int main(){
    max_x=80+1;
    max_y=25;
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
    Snake* snake = snake_create(initial_size, initial_direction, startPos);

    setlocale(LC_ALL, ""); // Setze die Locale für UTF-8
    titleScreen();
    while ((ch = getch()) != 13) {}
    system("cls"); // Terminal leeren (nur Windows)

    // ticke-clock
    do {
        start_time = clock();
        snake_move(snake, snake -> dir);
        printScreen(snake);
//        while((clock() - start_time) / (float)CLOCKS_PER_SEC <= 0.25){
        if(1) {
            //usleep(10000); // 10 ms Pause
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

    printf("\nq' zum Beenden.\n");
    // Endlosschleife, bis 'q' gedrückt wird
    while (1) {
        ch = getch(); // Wartet auf einen Tastendruck
        if (ch == 'q' || ch == 'Q') {
            break; // Schleife beenden, wenn 'q' oder 'Q' gedrückt wurde
        }
    }
    printf("Programm beendet.\n");
    
    free(snake->body);
    free(snake);
    return 0;
}