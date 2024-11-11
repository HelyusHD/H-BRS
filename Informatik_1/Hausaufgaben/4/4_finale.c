#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <conio.h>

#define SCHRITTGROESSE 10  // Iterationsschrittgröße der Abtastung
#define KARTENSCHRITTBREITE 10  // Breite der Karte in Schritten also x
#define KARTENSCHRITTHOEHE 10    // Höhe der Karte in Schritten

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

int main() {
    Vector2 haeuser[] = {
        { .x =  0, .y =  0 },
        { .x = 10, .y = 10 },
        { .x = 20, .y = 20 },
        { .x = 30, .y = 30 }
    };
    int num_haeuser = sizeof(haeuser) / sizeof(haeuser[0]);
    int heatMap[KARTENSCHRITTBREITE+1][KARTENSCHRITTHOEHE+1];

    // Iteriere über die Karte in Schritten von SCHRITTGROESSE
    for (int xStep = 0; xStep <= KARTENSCHRITTBREITE; xStep++) {
        pos.x = xStep * SCHRITTGROESSE;
        for (int yStep = 0; yStep <= KARTENSCHRITTHOEHE; yStep++) {
            pos.y = yStep * SCHRITTGROESSE;
            // Sortiere die Häuser basierend auf der Distanz zur aktuellen Position `pos`
            qsort(haeuser, num_haeuser, sizeof(Vector2), compare_distance);
            heatMap[xStep][yStep] = MIN(
                (int)floor(
                        distance(pos, haeuser[0]) / 10
                ),9
            );
        }
    }
    for (int xStep = 0; xStep <= KARTENSCHRITTBREITE; xStep++) {
        for (int yStep = 0; yStep <= KARTENSCHRITTHOEHE; yStep++) {
            (heatMap[xStep][yStep] <= 9 ?  printf("%i ",heatMap[xStep][yStep]) :  printf("# "));
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
