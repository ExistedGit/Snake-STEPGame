#pragma once
#include <iostream>
#include "../STEPGame/Menu.h"

void printRaw(string raw, int x, int _y, int fg = 7, int bg = 0) { // Посимвольно копирует 
    int y = 0;
    SetColor(fg, bg);
    for (int i = 0; i < raw.size(); i++) {
        cout << raw[i];
        if (raw[i] == '\n') {
            y++;
            gotoxy(x, _y + y);
        }
    }
    SetColor();
}