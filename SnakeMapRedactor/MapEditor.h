#pragma once
#include <iostream>
#include "../STEPGame/Menu.h"
#include <shobjidl.h> 
#include <tchar.h>
#include <stdio.h>
#include <strsafe.h>

#define SPACE ' '
#define WALL '#'
#define SPAWN '+'

#define BUFFERSIZE 4000
DWORD g_BytesTransferred = 0;



// Returns an empty string if dialog is canceled
wstring openfilename(const wchar_t* filter = L"All Files (*.*)\0*.*\0", HWND owner = NULL) {

    OPENFILENAME ofn;
    wchar_t fileName[MAX_PATH] = L"";
    ZeroMemory(&ofn, sizeof(ofn));

    

    ofn.lStructSize = sizeof(OPENFILENAME);
    ofn.hwndOwner = owner;
    ofn.lpstrFilter = filter;
    ofn.lpstrFile = (LPWSTR)fileName;
    ofn.lpstrTitle = L"Открыть карту Змейки...";
    ofn.nMaxFile = MAX_PATH;
    ofn.Flags = OFN_EXPLORER | OFN_FILEMUSTEXIST | OFN_HIDEREADONLY;
    ofn.lpstrDefExt = L"";

    wstring fileNameStr;
    if (GetOpenFileName(&ofn))
        fileNameStr = fileName;

    return fileNameStr;
}

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
    int width = 40, height = 40;
    vector<vector<char>> matrix;
    
    
    
    
    MapEditor() {
        for (int i = 0; i < height; i++) {
            matrix.push_back({});
            for (int j = 0; j < width; j++) {
                matrix[i].push_back(WALL);
            }
        }
        
    }
    void draw() {
        for (int i = 0; i < height; i++) {
            for (int j = 0; j <= width; j++) {
                SetColor(15, 0);
                
                cout << matrix[i][j];
                SetColor();
            }
            cout << endl;
        }
    }
    bool load() {
        wstring fileName = openfilename(L"SnakeMap\0*.snakemap");
        if (fileName != L"") {
            matrix = {};
            ifstream fin(fileName);
            char buff[80];
            int i = 0;
            while (fin.getline(buff, 80)) {
                matrix.push_back({});
                for (int j = 0; buff[j] != '\0'; j++) {
                    matrix[i].push_back(buff[j]);
                }
                i++;
            }
        }
        return fileName != L"";
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
   
    void displayTile(char tile) {

    }
    
    void start() {
        
        bool drawMode = false;// Чтобы процесс рисования был проще
        bool pointMode = true;

        bool spawnExists= false;
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
            case 0x33:
                drawTile = SPAWN;
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
            
            if (drawMode) {
                if (drawTile != SPAWN) matrix[posY][posX] = drawTile;
                else {
                    for (int i = 0; i < height; i++) {
                        for (int j = 0; j <= width; j++) {
                            if (matrix[i][j] == SPAWN) {
                                SetColor();
                                gotoxy(j, i);
                                matrix[i][j] = SPACE;
                                cout << SPACE;
                                break;
                            }
                        }
                    }
                    matrix[posY][posX] = drawTile;
                }
            }
            ;
            if (pointMode) drawMode = false;
            
        }
    }
};