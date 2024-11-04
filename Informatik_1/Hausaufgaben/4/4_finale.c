
#define KARTENBREITE //Breite der Karte
#define KARTENHÖHE   // Höhe der Karte
#define SCHRITTGRÖßE //Iterationsschrittgröße der Abtastung

typedef struct {
    int x;
    int y;
}Haus;


int main(){
    Haus haeuser[] = {
        { .x = 10, .y = 10 },
        { .x = 20, .y = 10 },
        { .x = 30, .y = 10 },
        { .x = 40, .y = 10 },
        { .x = 50, .y = 10 }
    };
    return 0;
}