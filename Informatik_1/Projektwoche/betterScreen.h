#include <stdlib.h> // für malloc und free

#ifndef BETTER_SCREEN
typedef struct{
    const char* red;
    const char* green;
}Collors;

typedef struct {
    char** stringBuffer;
    Collors collorTable;
}BetterScreen;



// creates a screen with the dimmensions size_x size_y 
BetterScreen screenCreate(int size_x, int size_y){
    BetterScreen screen;

    screen.stringBuffer = (char**)malloc(sizeof(char*) * size_x * 2);
    for (int i = 0; i < size_x * 2; ++i) {
        screen.stringBuffer[i] = (char*)malloc(sizeof(char) * size_y);
    }
    screen.collorTable = {
        .red = "\033[31m",
        .green = "\033[32m"
    };

    return screen;
}

void changeScreen(char* screenPosition, char str, const char* color){
    *(screenPosition - 1) = '\0';
    *screenPosition = str;
}
#endif