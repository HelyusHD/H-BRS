// 
// 

#include <stdio.h>
#include <conio.h>
#include <locale.h>
#include <stdbool.h>

int main()
{
    int p_max; 	                    // maximale Gesamtleistung [Watt Peak]
    int w;		                    // Wirkungsgrad [%]
    float a; 		                // Fläche [qm]
    // jetzt kommt Ihr Code...
    float flächenkosten;            // kosten pro m² [€/m²]
    float kosten;                   // kosten [€]
    float amortisationsdauer;       // Amortisationsdauer [anno]
    float einspeisevergütung;       // Verkaufspreis des Stromes [€]
    char eingabe;                   // Eingabeaufforderung des Nutzers
    bool volleinspeiser;            // 100% des Stromes wird verkauft

    int Pqm = 1000; // Strahlungsleistung der Sonne [W/m²]
    
    // Setze die locale auf die aktuelle Umgebung
    setlocale(LC_ALL, "");
    
    // 3.1
    printf("Die Maximallesitung wird auomatisch iteriert.\n");
    printf("pls enter the Wirkungsgrad [%%] of your pv modules\n");
    scanf("%i", &w);

    printf("Handelt es sich um eine Anlage mit Volleinspeisung? [y/n]: ");
    printf("\n");
    scanf(" %c", &eingabe);  // Beachte das Leerzeichen vor %c, um vorangehende Leerzeichen zu ignorieren
    switch (eingabe) {
        case 'y':
        case 'Y':
        volleinspeiser = true;
            break;
        case 'n':
        case 'N':
        volleinspeiser = false;
            break;
        default:
            printf("Ungültige Eingabe. Bitte nur 'y/Y' oder 'n/N' eingeben.\n");
            return 1;
    }

    for (p_max = 3000; p_max <= 12000; p_max += 1000) {
        printf("\nMaximallesitung: %i\n",p_max);
        a = p_max/(w/100.0 * Pqm); // pv area required to produce enough energy
        printf("Die notwendige Fläche beträgt %.2f m²\n",a);

        //3.2
        if(a<10){
            printf("Der Preis der Anlage liegt unterhalb der Mindestpreisgrenze!\n");
        }
        else if(a<20){
            flächenkosten = 430;
        }
        else if(a<30){
            flächenkosten = 360;   
        }
        else if(a<40){
            flächenkosten = 320;
        }
        else if(a<50){
            flächenkosten = 300;
        }
        else{
            flächenkosten = 290;
        }
        if(flächenkosten){
            kosten = flächenkosten * a;
            printf("Der Preis für eine Anlage dieser Größe beträgt %.2f €\n",kosten);
        }

        //3.3
        if(volleinspeiser) {
            if(p_max < 10000){
                einspeisevergütung = 0.134;
            }
            else{
                einspeisevergütung = 0.113;
            }
            amortisationsdauer = kosten/(p_max*0.95 * 1 * einspeisevergütung);
            printf("Die Anlage hat sich in %f Jahren amortisiert.\n",amortisationsdauer);
        }
        else{
            if(p_max < 10000){
                einspeisevergütung = 0.086;
            }
            else{
                einspeisevergütung = 0.075;
            }
            amortisationsdauer = kosten/(p_max*0.95 * 0.7 * einspeisevergütung + p_max*0.95 * 0.3 * 0.37);
            printf("Die Anlage hat sich in %f Jahren amortisiert.\n",amortisationsdauer);
        }
    }

    char ch;
    printf("Drücke 'q' zum Beenden.\n");
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
