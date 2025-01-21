#include <stdio.h>
#include <windows.h>
#include <wchar.h>

#ifndef TITLE_SCREEN_H
#define TITLE_SCREEN_H

void titleScreen() {
    SetConsoleOutputCP(65001); // UTF-8 aktivieren
    SetConsoleCP(65001);
    SetConsoleOutputCP(CP_UTF8);

    const wchar_t title[] = 
        L"################################################################################\n"
        L"#                                                                              #\n"
        L"#                                                                              #\n"
        L"#                                                                              #\n"
        L"#                                                                              #\n"
        L"#                   ███████╗███╗   ██╗ █████╗ ██╗  ██╗███████╗                 #\n"
        L"#                   ██╔════╝████╗  ██║██╔══██╗██║ ██╔╝██╔════╝                 #\n"
        L"#                   ███████╗██╔██╗ ██║███████║█████╔╝ █████╗                   #\n"
        L"#                   ╚════██║██║╚██╗██║██╔══██║██╔═██╗ ██╔══╝                   #\n"
        L"#                   ███████║██║ ╚████║██║  ██║██║  ██╗███████╗                 #\n"
        L"#                   ╚══════╝╚═╝  ╚═══╝╚═╝  ╚═╝╚═╝  ╚═╝╚══════╝                 #\n"
        L"#                                                                              #\n"
        L"#                                        ____                                  #\n"
        L"#                                       / . .\\                                 #\n"
        L"#                                       \\  ---<                                #\n"
        L"#                                        \\  /                                  #\n"
        L"#                              __________/ /                                   #\n"
        L"#                           -=:___________/                                    #\n"
        L"#                                                                              #\n"
        L"#                    Press ENTER to start the game                             #\n"
        L"#                                                                              #\n"
        L"#                    Use arrow keys to navigate the snake                      #\n"
        L"#                                                                              #\n"
        L"#                    Press q to quit                                           #\n"
        L"#                                                                              #\n"
        L"################################################################################\n";

    DWORD written;
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    WriteConsoleW(hConsole, title, wcslen(title), &written, NULL);
}


#endif
