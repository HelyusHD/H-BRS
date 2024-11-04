// 
// 
// Loesung 1. Aufgabe 'von Hand': 

#include <stdio.h>
#include <math.h>
#include <conio.h>

int main()
{
    float g_x, g_y;  // Koordinaten Gebaeude
    float w_x, w_y;  // Koordinaten Windkraftanlage
    float maxHight;

    printf(
        "Berechnung der maximalen Hoehe eines Windrades"
        ""
        "Druecke eine beliebige Taste\n"
    );
    getch();

    printf("Koordinaten des Gebaeudes [km], Schema: x y\n");
    if(scanf("%f %f", &g_x, &g_y)!=2){
        printf("ungültige Eingabe\n");
    }else{
        printf("\nKoordinaten des Windrades [km], Schema: x y\n");
        if(scanf("%f %f", &w_x, &w_y)!=2){
            printf("ungültige Eingabe\n");
        }else{

            maxHight = sqrt((g_x - w_x)*(g_x - w_x) + (g_y - w_y)*(g_y - w_y) *100);
            printf("Die maximale Hoehe fuer das Windrad betraegt: %.2fm\n", maxHight);
        }
    }

    char ch;
    printf("\nDruecke 'q' zum Beenden.\n");
    // Endlosschleife, bis 'q' gedrückt wird
    while (1) {
        ch = getch(); // Wartet auf einen Tastendruck
        if (ch == 'q' || ch == 'Q') {
            break; // Schleife beenden, wenn 'q' oder 'Q' gedrückt wurde
        }
    }

    return 0;
}