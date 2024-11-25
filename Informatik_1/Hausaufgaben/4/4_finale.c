/*[ 
    calculates a heat map woith the size SCHRITTGROESSE * (KARTENSCHRITTBREITE | KARTENSCHRITTHOEHE)
    The heat map represents the max hight of a wind turbine depending on the positions of houses.
]*/
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <conio.h>

#define SCHRITTGROESSE 10  // Iterationsschrittgröße der Abtastung
#define KARTENSCHRITTBREITE 25  // Breite der Karte in Schritten also x
#define KARTENSCHRITTHOEHE 25    // Höhe der Karte in Schritten

#define MIN(a, b) ((a) < (b) ? (a) : (b))

typedef struct {
    int x;
    int y;
} Vector2;

// Distanz zwischen zwei Vector2-Punkten berechnen
float distance(Vector2 a, Vector2 b) {
    return sqrt((a.x - b.x) * (a.x - b.x) + (a.y - b.y) * (a.y - b.y));
}

// Globale Variable für die Vergleichsposition
Vector2 pos;

// Vergleichsfunktion für `qsort` basierend auf der Distanz zu `pos`
int compare_distance(const void *a, const void *b) {
    const Vector2 *haus_a = (const Vector2 *)a;
    const Vector2 *haus_b = (const Vector2 *)b;

    float dist_a = distance(*haus_a, pos);
    float dist_b = distance(*haus_b, pos);

    if (dist_a < dist_b) return -1;
    if (dist_a > dist_b) return 1;
    return 0;
}


char* colorMapping(int num){
    char* collored;

switch (num) {
    case 0:
        collored = "\033[34m"; // Blau (kalt)
        break;
    case 1:
        collored = "\033[36m"; // Cyan
        break;
    case 2:
        collored = "\033[32m"; // Grün
        break;
    case 3:
        collored = "\033[92m"; // Hell-Grün
        break;
    case 4:
        collored = "\033[33m"; // Gelb
        break;
    case 5:
        collored = "\033[93m"; // Hell-Gelb
        break;
    case 6:
        collored = "\033[35m"; // Magenta
        break;
    case 7:
        collored = "\033[95m"; // Hell-Magenta
        break;
    case 8:
        collored = "\033[31m"; // Rot (heißer)
        break;
    case 9:
        collored = "\033[91m"; // Hell-Rot (am heißesten)
        break;
    default:
        collored = "\033[37m"; // Weiß (neutral)
        break;
}


    return collored;
}

int main() {
    Vector2 haeuser[] = {
        { .x = 50, .y = 50 },
        { .x = 70, .y = 120 },
        { .x = 150, .y = 200 },
        { .x = 200, .y = 75 }
    };
    int haeuserCount = 4;

    int num_haeuser = sizeof(haeuser) / sizeof(haeuser[0]);
    int heatMap[KARTENSCHRITTBREITE+1][KARTENSCHRITTHOEHE+1];

    // Iteriere über die Karte in Schritten von SCHRITTGROESSE
    for (int xStep = 0; xStep <= KARTENSCHRITTBREITE; xStep++) {
        pos.x = xStep * SCHRITTGROESSE;
        for (int yStep = 0; yStep <= KARTENSCHRITTHOEHE; yStep++) {
            pos.y = yStep * SCHRITTGROESSE;
            // Sortiere die Häuser basierend auf der Distanz zur aktuellen Position `pos`
            int closestHaus = 0;
            for(int i=1; i < haeuserCount; i++){
                if(distance(haeuser[i], pos) < distance(haeuser[closestHaus], pos)){
                    closestHaus = i;
                }
            }
            // quick-sort is inefficient since it sorts more than the smallest element
            //qsort(haeuser, num_haeuser, sizeof(Vector2), compare_distance);
            heatMap[xStep][yStep] = MIN(
                (int)floor(
                    //distance(pos, haeuser[0]) / 10
                    distance(pos, haeuser[closestHaus]) / 10
                )   ,9
            );
        }
    }
    for (int xStep = 0; xStep <= KARTENSCHRITTBREITE; xStep ++) {
        for (int yStep = 0; yStep <= KARTENSCHRITTHOEHE; yStep ++) {
            (heatMap[xStep][yStep] <= 9 ?  printf("%s%i\033[0m ",colorMapping(heatMap[xStep][yStep]), heatMap[xStep][yStep]) :  printf("# "));
        }
        printf("\n");
    }

    char ch;
    printf("Druecke 'q' zum Beenden.\n");
    // Endlosschleife, bis 'q' gedrückt wird
    while (1) {
        ch = getch(); // Wartet auf einen Tastendruck
        if (ch == 'q' || ch == 'Q') {
            break; // Schleife beenden, wenn 'q' oder 'Q' gedrückt wurde
        }
    }
    printf("Programm beendet.\n");

    return 0;
}
