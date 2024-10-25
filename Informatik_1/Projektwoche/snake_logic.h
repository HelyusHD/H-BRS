// snake_logic.h
#ifndef SNAKE_LOGIC_H
#define SNAKE_LOGIC_H

// Richtungen, in die die Schlange sich bewegen kann
typedef enum { UP, DOWN, LEFT, RIGHT } Direction;

// Position eines Segments der Schlange
typedef struct {
    int x;
    int y;
} Position;

// Definition der Schlange
typedef struct {
    Position *body;   // Array von Segmenten (Positionen)
    int size;         // Größe der Schlange (Anzahl der Segmente)
    Direction dir;    // Aktuelle Richtung
} Snake;

// Funktionen zur Verwaltung der Schlange
Snake *snake_create(int startX, int startY, int initial_size, Direction initial_dir);
void snake_destroy(Snake *snake);
void snake_move(Snake *snake);
void snake_change_direction(Snake *snake, Direction new_dir);

#endif // SNAKE_LOGIC_H

