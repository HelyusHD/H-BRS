// 
// 

#include <stdio.h>
#include <conio.h>

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

    int Pqm = 1000; // Strahlungsleistung der Sonne [W/m²]
    
    
    // 3.1
    printf("pls enter required Maximalleistung [Watt Peak]\n");
    scanf("%i", &p_max);
    printf("pls enter the Wirkungsgrad [%%] of your pv modules\n");
    scanf("%i", &w);
    
    a = p_max/(w/100.0 * Pqm); // pv area required to produce enough energy
    printf("Die notwendige Fläsche beträgt %.2f m²\n",a);

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
    char eingabe;
    printf("Handelt es sich um eine Anlage mit Volleinspeisung? [y/n]: ");
    printf("\n");
    scanf(" %c", &eingabe);  // Beachte das Leerzeichen vor %c, um vorangehende Leerzeichen zu ignorieren

    switch (eingabe) {
        case 'y':
        case 'Y':
            if(p_max < 10000){
                einspeisevergütung = 0.134;
            }
            else{
                einspeisevergütung = 0.113;
            }
            amortisationsdauer = kosten/(p_max*0.95 * 1 * einspeisevergütung);
            printf("Die Anlage hat sich in %d Jahren amortisiert.\n",amortisationsdauer);
            break;
        case 'n':
        case 'N':
            if(p_max < 10000){
                einspeisevergütung = 0.086;
            }
            else{
                einspeisevergütung = 0.075;
            }
            amortisationsdauer = kosten/(p_max*0.95 * 0.7 * einspeisevergütung + p_max*0.95 * 0.3 * 0.37);
            printf("Die Anlage hat sich in %d Jahren amortisiert.\n",amortisationsdauer);
            break;
        default:
            printf("Ungültige Eingabe. Bitte nur 'y/Y' oder 'n/N' eingeben.\n");
            return 1;
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
