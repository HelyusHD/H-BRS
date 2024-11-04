#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define KARTENBREITE 100  // Breite der Karte also x
#define KARTENHÖHE 100    // Höhe der Karte
#define SCHRITTGRÖSSE 50  // Iterationsschrittgröße der Abtastung

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
        { .x = 10, .y = 10 },
        { .x = 20, .y = 10 },
        { .x = 30, .y = 10 },
        { .x = 40, .y = 10 },
        { .x = 50, .y = 10 }
    };
    int num_haeuser = sizeof(haeuser) / sizeof(haeuser[0]);

    // Iteriere über die Karte in Schritten von SCHRITTGRÖSSE
    for (pos.x = 0; pos.x <= KARTENBREITE; pos.x += SCHRITTGRÖSSE) {
        for (pos.y = 0; pos.y <= KARTENHÖHE; pos.y += SCHRITTGRÖSSE) {

            // Sortiere die Häuser basierend auf der Distanz zur aktuellen Position `pos`
            qsort(haeuser, num_haeuser, sizeof(Vector2), compare_distance);

            // Ausgabe der sortierten Häuser
            printf("Sortierte Häuser von Position (%d, %d):\n", pos.x, pos.y);
            for (int i = 0; i < num_haeuser; i++) {
                printf("Haus %d: x = %d, y = %d, Distanz = %.2f\n",
                       i, haeuser[i].x, haeuser[i].y, distance(pos, haeuser[i]));
            }
            printf("\n");
        }
    }

    return 0;
}
