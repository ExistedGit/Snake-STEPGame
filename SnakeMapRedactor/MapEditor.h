#pragma once
#include <iostream>
#include "../STEPGame/Menu.h"

#define SPACE ' '
#define WALL '#'
#define HEAD '+'

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

struct MapEditor {
    char** matrix = new char*[40];
    int width = 40, height = 40;
    
    
    MapEditor() {
        for (int i = 0; i < height; i++) {
            matrix[i] = new char[width];
            for (int j = 0; j < width; j++) {
                matrix[i][j] = WALL;
            }
        }
        
    }
    void draw() {
        for (int i = 0; i < height; i++) {
            for (int j = 0; j < width; j++) {
                SetColor(15, 0);
                
                cout << matrix[i][j];
                SetColor();
            }
            cout << endl;
        }
    }
    void displayMode(bool drawMode, bool pointMode) {
        
        SetColor();
        gotoxy(width / 2 - 10, height + 2);
        for (int i = 0; i < 30; i++) cout << " ";
        gotoxy(width / 2 - 10, height + 2);
        cout << "Режим: ";

        if (!drawMode) {
            cout << "Перемещение";
        }
        else if (drawMode && !pointMode) {

            cout << "Рисование";
        }
        else if (drawMode && pointMode) {
            cout << "Точечное рисование";
        }
        
        gotoxy(width + 2, height / 1.5);
        cout << "  ";
        if (!drawMode) cout << "+";
        else if (drawMode && !pointMode)cout << "*";
        else if (drawMode && pointMode)cout << "*.";
        
    }
   
    
    void start() {
        
        bool drawMode = false;// Чтобы процесс рисования был проще
        bool pointMode = true;
        char drawTile = SPACE;
        
        bool active = true;
        int posX=0, posY=0;
        char c;
        vector<int> oldPos = { 0, 1 };
        
        draw();
        displayMode(drawMode, pointMode);
        while (active) {

            gotoxy(oldPos[0], oldPos[1]);
            SetColor(15, 0);
            cout << matrix[oldPos[1]][oldPos[0]];
            SetColor();
            
            gotoxy(posX, posY);
            SetColor(0, 15);
            cout << matrix[posY][posX];



            c = _getch();
            oldPos = { posX, posY };
            switch (c) {
            case KEY_UP:
                if (posY > 0) posY--;
                break;
            case KEY_DOWN:
                if (posY < height-1) posY++;
                break;
            case KEY_RIGHT:
                if (posX < width - 1)posX++;
                break;
            case KEY_LEFT:
                if (posX >0)posX--;
                break;
            case 0x31:
                drawTile = SPACE;
                break;
            case 0x32:
                drawTile = WALL;
                break;
            case SPACE:
                if(!pointMode) drawMode = !drawMode;
                else {
                    drawMode = true;
                }
                displayMode(drawMode, pointMode);
                break;
            case 'z': case 'Z':
                pointMode = !pointMode;
                displayMode(drawMode, pointMode);
                break;
            case VK_ESCAPE:
                active = false;
                break;
            

                
            }
            
            if (drawMode) matrix[posY][posX] = drawTile;
            if (pointMode) drawMode = false;
            
        }
    }
};