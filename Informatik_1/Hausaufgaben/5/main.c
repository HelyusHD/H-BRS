#include <math.h>
#include <stdio.h>

float volumeDerivative(float hight, float area){
    return area*sqrt(2*9.81*hight);
}

float power(float hight, float area){
    return volumeDerivative(hight, area)*9.81*hight*0.85;
}

int main(){


    FILE *file = fopen("data.txt", "w"); // Datei öffnen zum Schreiben
    if (file == NULL) {
        perror("Fehler beim Öffnen der Datei");
        return 1;
    }

    for(float hight; hight<200; hight = hight + 1){
        float p = power(hight,4);
        //printf("%.0f\t%.2f\n",hight,p);
        fprintf(file, "%.2f %.2f %.2f\n", hight, p, volumeDerivative(hight, 4)); // In Datei schreiben
    }

    fclose(file); // Datei schließen

    return 0;
}