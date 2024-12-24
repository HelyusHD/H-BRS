#include <stdio.h>
#include <math.h>
#include <conio.h> // Für die Verwendung von getch()

// ANSI-Farbcodes definieren
#define COLOR_RESET "\033[0m"
#define COLOR_0 "\033[38;5;196m"      // Rot
#define COLOR_1 "\033[38;5;202m"      // Orange
#define COLOR_2 "\033[38;5;226m"      // Gelb
#define COLOR_3 "\033[38;5;118m"      // Hellgrün
#define COLOR_4 "\033[38;5;46m"       // Grün
#define COLOR_5 "\033[38;5;39m"       // Hellblau
#define COLOR_6 "\033[38;5;27m"       // Blau
#define COLOR_7 "\033[38;5;93m"       // Lila
#define COLOR_8 "\033[38;5;201m"      // Magenta
#define COLOR_9 "\033[38;5;129m"      // Pink

#define NUM_BUILDINGS 5  // Anzahl der Gebäude
#define ROWS 25          // Anzahl der Zeilen im Raster
#define COLS 50          // Anzahl der Spalten im Raster
#define MAP_SIZE 10000   // Größe der Karte in Metern

// Funktion zum Ausgeben einer Zahl mit der entsprechenden Farbe (wird nun nicht mehr benötigt)
void print_colored(int value) {
    switch (value) {
        case 0: printf(COLOR_0 "0" COLOR_RESET); break;
        case 1: printf(COLOR_1 "1" COLOR_RESET); break;
        case 2: printf(COLOR_2 "2" COLOR_RESET); break;
        case 3: printf(COLOR_3 "3" COLOR_RESET); break;
        case 4: printf(COLOR_4 "4" COLOR_RESET); break;
        case 5: printf(COLOR_5 "5" COLOR_RESET); break;
        case 6: printf(COLOR_6 "6" COLOR_RESET); break;
        case 7: printf(COLOR_7 "7" COLOR_RESET); break;
        case 8: printf(COLOR_8 "8" COLOR_RESET); break;
        case 9: printf(COLOR_9 "9" COLOR_RESET); break;
        default: printf("%d", value); break;  // Fallback für unerwartete Werte
    }
}

int main() {
    // Initialisierung der Koordinaten der fünf Gebäude
    float building_x[NUM_BUILDINGS] = {1000, 3000, 5000, 9000, 9000};  // X-Koordinaten
    float building_y[NUM_BUILDINGS] = {2000, 8000, 10000, 9000, 1000};  // Y-Koordinaten
    char ch;

    // CSV-Datei zum Speichern der Ausgabe öffnen
    FILE *file = fopen("output.csv", "w");
    if (file == NULL) {
        printf("Fehler beim Öffnen der Datei.\n");
        return 1;
    }

    // Raster über die Karte erstellen und maximale Höhe pro Zelle berechnen
    for (int y = 0; y < ROWS; y++) {
        for (int x = 0; x < COLS; x++) {
            // Berechnen der aktuellen Position im Raster (Skalierung von Kartenkoordinaten)
            float w_x = (x * MAP_SIZE) / COLS;
            float w_y = (y * MAP_SIZE) / ROWS;

            // Initialisierung des minimalen Abstands für die aktuelle Position
            float min_distance = -1;

            // Berechnung des Abstands zur nächsten Gebäude
            for (int i = 0; i < NUM_BUILDINGS; i++) {
                float distance = sqrt(pow(w_x - building_x[i], 2) + pow(w_y - building_y[i], 2));
                if (min_distance == -1 || distance < min_distance) {
                    min_distance = distance;
                }
            }

            // Berechnung der maximalen Höhe nach der 10H-Regel
            float max_height = min_distance / 10;
            int display_height = (int)(max_height / 100); // Umwandlung in einstellige Zahl

            // Schreiben der berechneten Höhe in die CSV-Datei
            fprintf(file, "%d", display_height);

            // Trennung der Werte in der CSV-Datei
            if (x < COLS - 1) {
                fprintf(file, ",");  // Komma für Trennung der Spalten
            }
        }
        // Neue Zeile nach jeder Zeile im Raster in der CSV-Datei
        fprintf(file, "\n");
    }

    // Datei schließen
    fclose(file);

    printf("Ergebnis wurde in '4.3 mit Farben.csv' gespeichert.\n");
    return 0;

    // Auf Eingabe warten, um das Programm zu beenden
    printf("Druecken Sie 'q' zum Beenden.\n");
    while (1) {
        ch = getch(); // Wartet auf Tastendruck
        if (ch == 'q' || ch == 'Q') {
            break; // Schleife beenden, wenn 'q' oder 'Q' gedrückt wurde
        }
    }

     printf("Programm beendet.\n");
    
    return 0;
}
