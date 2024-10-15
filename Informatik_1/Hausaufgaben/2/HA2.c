// Bei einer Eingabe von 80 Jahren passiert ein "overflow" des Speichers für Sekunden, da ein i bzw. d nur 32bit groß ist. 
// Ich habe das Problem allerdings behoben.
//
// Was passiert bei einem Alter von 80?
// Antwort: 
// 

#include <stdio.h>
#include <conio.h>

int main() 
{
   int jahre, tage, stunden, minuten;
   // ich defineire "sekunden" als lld um den overflow zu verhindern
   long long int sekunden;
   
   printf("Wieviel Jahre alt bist Du? ");
   // %i definiert die Formatierung der Eingabe als int
   // &jahre ist der pointer auf den Speicherbereich der Variable "jahre"
   scanf("%d", &jahre);
   
       // Berechnungen
    tage = jahre * 365; // Annahme: 1 Jahr = 365 Tage
    stunden = tage * 24;
    minuten = stunden * 60;
    // das Ergebnis wird als lld interpretiert
    sekunden = (long long int) minuten * 60;
    
    // Ausgabe der Ergebnisse
    // printf() füllt die Formatierungsplatzhalter ("%") der Reihe nach mit den folgenden parametern
    printf("\nIhr Alter in verschiedenen Einheiten:\n");
    printf("Tage: %d\n", tage);
    printf("Stunden: %d\n", stunden);
    printf("Minuten: %d\n", minuten);
    printf("Sekunden: %lld\n", sekunden);


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
