// snake_logic.h
#include <stdlib.h> // für malloc und free
#include <stdbool.h> // Für den bool-Typ
#ifndef SNAKE_LOGIC_H
#define SNAKE_LOGIC_H

// Richtungen, in die die Schlange sich bewegen kann
typedef enum {
    UP, 
    DOWN, 
    LEFT, 
    RIGHT
}
Direction;

// Position eines Segments der Schlange
typedef struct {
    int x;
    int y;
} Position;

// Definition der Schlange
typedef struct {
    Position* body;   // Array von Segmenten (Positionen)
    int size;         // Größe der Schlange (Anzahl der Segmente)
    Direction dir;    // Aktuelle Richtung
} Snake;

//Funktion zur Addition von Positionen
Position add_position(Position a, Position b){
    Position pos;
    pos.x = a.x + b.x;
    pos.y = a.y + b.y;
    return pos;
}
//kontrolliert ob zwei Positionen identisch sind
bool same_position(Position a, Position b){
    return (a.x==b.x && a.y==b.y);
}


// Funktionen zur Erstellung der Schlange
// Kopf liegt bei body[0]
Snake* snake_create(int initial_size, Direction initial_dir, Position initial_pos){
    Snake* snake = (Snake*)malloc(sizeof(Snake));
    snake->size = initial_size;
    snake->dir = initial_dir;
    snake->body = (Position*)malloc(initial_size * sizeof(Position));
    Position iterationDirection = {0, 0};
    switch(initial_dir){
        case UP :
            iterationDirection.y = -1;
            break;
        case DOWN:
            iterationDirection.y = 1;
            break;
        case LEFT:
            iterationDirection.x = -1;
            break;
        case RIGHT:
            iterationDirection.x = 1;
            break;
    }

    snake->body[initial_size-1] = initial_pos;
    for(int i = initial_size-2; i >= 0; i--){
        snake->body[i] = add_position(snake->body[i+1], iterationDirection);
    }

    return snake;
}
//changes the position of the snake
void snake_move(Snake *snake, Direction dir){
    Position direction = {0, 0};
    switch(dir){
        case UP :
            direction.y = -1;
            break;
        case DOWN:
            direction.y = 1;
            break;
        case LEFT:
            direction.x = -1;
            break;
        case RIGHT:
            direction.x = 1;
            break;
    }
    // shifting positions of segments
    for(int i=snake->size-1; i >= 1; i--){
        snake->body[i] = snake->body[i-1];
    }
    // moving head of snake
    snake->body[0] = add_position(snake->body[0], direction);
}
#endif // SNAKE_LOGIC_H

