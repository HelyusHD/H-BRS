#include <windows.h>
#include <stdio.h>
#include <stdlib.h> // um den terminal zu leeren
#include <conio.h>
#include "my_own_snakeHeader.h"

int max_x, max_y;
HANDLE h;


int printScreen(Snake* snake)
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
    screen[max_y][max_x] = '\0';
    system("cls"); // Terminal leeren (nur Windows)
    printf(screen[0]);

    return 0;
}



int main(){
    printf("start\n");
    int error;
    max_x=120+1;
    max_y=60;
    h = GetStdHandle ( STD_OUTPUT_HANDLE );


    Position startPos = {10, 13}; // {x|y}
    int initial_size = 4;
    Direction initial_direction = RIGHT;
    Snake* snake = snake_create(initial_size, initial_direction, startPos);

    char ch;
    printf("\ns' zum Starten.\n");
    // Endlosschleife, bis 'q' gedrückt wird
    while (1) {
        ch = getch(); // Wartet auf einen Tastendruck
        if (ch == 's' || ch == 'S') {
            break; // Schleife beenden, wenn 'q' oder 'Q' gedrückt wurde
        }
    }
    
    int c = 0;
    while(c <= 10){
        error = printScreen(snake);
        snake_move(snake, UP);
        c++;
        Sleep(200); // sleeping time in ms
    }

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
    return error;
}