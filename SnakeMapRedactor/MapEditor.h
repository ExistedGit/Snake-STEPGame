#pragma once
#include <iostream>
#include "../STEPGame/Menu.h"
#include "../STEPGame/FormatText.h"
#include <shobjidl_core.h> 
#include <tchar.h>
#include <stdio.h>
#include <shlobj_core.h>


#define SPACE ' '
#define WALL '#'
#define SPAWN '+'
#define PORTAL '0'

enum DrawModes {
    MOVE = 0,
    DRAW,
    POINTDRAW,
};

// Узрите же вершину моего развития, великолепные окна открытия файлов!

// Если открытие отменено, возвращает L""
wstring openfilename(const wchar_t* filter = L"All Files (*.*)\0*.*\0", HWND owner = NULL) {

    OPENFILENAME ofn;
    wchar_t fileName[MAX_PATH] = L"";
    ZeroMemory(&ofn, sizeof(ofn));

    

    ofn.lStructSize = sizeof(OPENFILENAME);
    ofn.hwndOwner = owner;
    ofn.lpstrFilter = filter;
    ofn.lpstrFile = (LPWSTR)fileName;
    ofn.lpstrTitle = L"Открыть карту Змейки...";
    ofn.lpstrInitialDir = L"C:\\Users\\paytv\\source\\repos\\STEPGame\\STEPGame\\Maps";
    ofn.nMaxFile = MAX_PATH;
    ofn.Flags = OFN_EXPLORER | OFN_FILEMUSTEXIST | OFN_HIDEREADONLY;
    ofn.lpstrDefExt = L"";

    wstring fileNameStr;
    if (GetOpenFileName(&ofn))
        fileNameStr = fileName;

    return fileNameStr;
}

// Если открытие отменено, возвращает L""
wstring savefilename(const wchar_t* filter = L"All Files (*.*)\0*.*\0", HWND owner = NULL) {

    OPENFILENAME ofn;
    wchar_t fileName[MAX_PATH] = L"C:\\Users\\paytv\\source\\repos\\STEPGame\\STEPGame\\Maps\\Untitled.snakemap";
    ZeroMemory(&ofn, sizeof(ofn));



    ofn.lStructSize = sizeof(OPENFILENAME);
    ofn.hwndOwner = owner;
    ofn.lpstrFilter = filter;
    ofn.lpstrFile = (LPWSTR)fileName;
    ofn.lpstrTitle = L"Сохранить карту Змейки...";
    ofn.nMaxFile = MAX_PATH;
    ofn.Flags = OFN_EXPLORER | OFN_HIDEREADONLY;
    ofn.lpstrDefExt = L"";
    ofn.lpstrInitialDir = L"C:\\Users\\paytv\\source\\repos\\STEPGame\\STEPGame\\Maps";
    wstring fileNameStr;
    if (GetSaveFileName(&ofn))
        fileNameStr = fileName;

    return fileNameStr;
}
bool fileExists(const wstring name) {
    ifstream f(name.c_str());
    return f.good();
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

void RegSet(HKEY hkeyHive, const wchar_t* pszVar, const wchar_t* pszValue) { // Удобная функция записи в регистр

    HKEY hkey;

    wchar_t szValueCurrent[1000];
    DWORD dwType;
    DWORD dwSize = sizeof(szValueCurrent);

    int iRC = RegGetValue(hkeyHive, pszVar, NULL, RRF_RT_ANY, &dwType, szValueCurrent, &dwSize);

    bool bDidntExist = iRC == ERROR_FILE_NOT_FOUND;

    if (!bDidntExist) return;

    DWORD dwDisposition;
    iRC = RegCreateKeyEx(hkeyHive, pszVar, 0, 0, 0, KEY_ALL_ACCESS, NULL, &hkey, &dwDisposition);

    iRC = RegSetValueEx(hkey, L"", 0, REG_SZ, (BYTE*)pszValue, (lstrlenW(pszValue) + 1) * sizeof(wchar_t));

    RegCloseKey(hkey);
}

void SetUpRegistry() { // Записывает редактор в регистр как программу для открытия снейкмепов

    wchar_t pszValue[MAX_PATH] = L"\"";
    wchar_t buff[MAX_PATH];
    GetModuleFileName(NULL, buff, MAX_PATH);
    lstrcat(pszValue, buff);

    wchar_t buff2[MAX_PATH] = L"\" \"%1\"";
    lstrcat(pszValue, buff2);

    wchar_t value[255];
    DWORD BufferSize = 8192;
    wstring regFilePath = L"";
    if (ERROR_SUCCESS != RegGetValueW(HKEY_CLASSES_ROOT, L"SystemFileAssociations\\.snakemap\\Shell\\Открыть редактором карт\\Command", L"", RRF_RT_ANY, NULL, (PVOID)&value, &BufferSize)) {


        
            int quoteCount = 0;
            for (int i = 0; value[i] != '\0'; i++) {
                if (value[i] != L'\"') regFilePath.push_back(value[i]);
                else {
                    quoteCount++;
                }
                if (quoteCount == 2) {
                    regFilePath.push_back('\0');
                    break;
                };
            }
    }
    if (!fileExists(regFilePath)) {
        RegSet(HKEY_CLASSES_ROOT, L"SystemFileAssociations\\.snakemap\\Shell\\Открыть редактором карт\\Command", pszValue);

        SHChangeNotify(SHCNE_ASSOCCHANGED, SHCNF_IDLIST, NULL, NULL);
    }
    
}

struct Portal {
    int x, y;
    int color;
};

struct MapEditor {
    int width = 40, height = 40;
    vector<vector<char>> matrix;
    vector<Portal> portals; // Порталы должны работать не так. Но я уже не хочу переделывать и так рабочую архитектуру

    int portalColor = 1;

    void generateMap() {
        matrix = {};
        for (int i = 0; i < height; i++) {
            matrix.push_back({});
            if (0 == i || i == height - 1) {
                for (int j = 0; j < width; j++) {
                    matrix[i].push_back(WALL);
                }
            }
            else {
                matrix[i].push_back(WALL);
                for (int j = 1; j < width - 1; j++) {
                    matrix[i].push_back(SPACE);
                }
                matrix[i].push_back(WALL);
            }
        }
    }
    
    MapEditor() {
        generateMap();
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
    bool loadWithContext(char* fileName) {
        matrix = {};
        ifstream fin(fileName);
        char buff[320];
        int i = 0;
        while (fin.getline(buff, 320)) { // Тоже парсер файла
            width = strlen(buff);
            matrix.push_back({});
            for (int j = 0; buff[j] != '\0'; j++) {
                if (hexIntMap.count(buff[j])) {
                    portals.push_back({ j, i, hexIntMap[buff[j]] });
                    matrix[i].push_back(SPACE);
                }
                else matrix[i].push_back(buff[j]);
            }
            i++;
        }
        height = i;
        return i > 0;
    }

    bool load() {
        wstring fileName = openfilename(L"SnakeMap\0*.snakemap\0");
        if (fileName != L"") {
            matrix = {};
            ifstream fin(fileName);
            char buff[320];
            int i = 0;
            while (fin.getline(buff, 320)) { // Парсер файла
                width = strlen(buff);
                matrix.push_back({});
                for (int j = 0; buff[j] != '\0'; j++) {
                    
                    if (hexIntMap.count(buff[j])) {
                        portals.push_back({ j, i, hexIntMap[buff[j]] });
                        matrix[i].push_back(SPACE);
                    } else matrix[i].push_back(buff[j]);
                    
                }
                i++;
            }
            height = i;
        }
        return fileName != L"";
    }

    void save() {
        wstring fileName = savefilename(L"SnakeMap(*.snakemap)\0*.snakemap\0Text(*.txt)\0*.txt\0");
        
        if (fileExists(fileName))
        {
            if (MessageBox(GetConsoleWindow(), L"Этот файл уже существует. Вы точно хотите его перезаписать?", L"Внимание!", MB_ICONWARNING | MB_YESNO) != IDNO) {
                ofstream fout(fileName);
                for (int i = 0; i < height; i++) {
                    for (int j = 0; j < width; j++) {
                        
                        bool isPortal = false;
                        for (int k = 0; k < portals.size(); k++) {
                            if (portals[k].x == j && portals[k].y == i) {
                                fout << intHexMap[portals[k].color];
                                isPortal = true;
                            }
                        }

                        if(!isPortal) fout << matrix[i][j];
                        
                    }
                    fout << endl;
                }
                fout.close();
            }
            else return;
        }
        else {
            ofstream fout(fileName);
            for (int i = 0; i < height; i++) {
                for (int j = 0; j < width; j++) {
                    fout << matrix[i][j];
                }
                fout << endl;
            }
            fout.close();
        }
        
    }

    
    void displayMode(int drawMode) {
        
        SetColor();
        vector<string> drawModes = { "Z - Перемещение", "X - Рисование перемещением", "C - Точечное рисование" };
        
        for (int i = 0; i < drawModes.size(); i++) {
            gotoxy(width + 2, height / 2 - 3 + i);
            if (drawMode == i) SetColor(0, 15);
            cout << drawModes[i];
            SetColor();
        }
        
    }
   
    void displayTile(char tile) {
        SetColor();
        vector<string> tileNames = { "1 - Пробел", "2 - Стена", "3 - Точка спавна", "4 - Портал"};
        vector<char> tileTypes = {SPACE, WALL, SPAWN, PORTAL};
        
        for (int i = 0; i < tileTypes.size(); i++) {
            gotoxy(width + 2, height / 2 + 2 + i);
            if (tile == tileTypes[i]) {
                SetColor(0, 15);
            }
            cout << tileNames[i];
            if (i == 3) {
                SetColor();
                cout << "(Цвет: ";
                SetColor(portalColor, portalColor);
                cout << " ";
                SetColor();
                cout << ")";
            }
            SetColor();
        }
    }
    
    void resizeMenu() {
        SettingsMenu resizeMenu;
        vector<string> left = { "Ширина", "Высота" };
        vector<vector<string>> right = { {}, {} };
        for (int i = 5; i <= 160; i++) {
            right[0].push_back(to_string(i));
        }
        for (int i = 5; i <= 60; i++) {
            right[1].push_back(to_string(i));
        }
        map<int, int> choose = resizeMenu.startMenu(left, right, 90, 20, {80-5, 40-5});
        
        width = choose[0] + 5;
        height = choose[1] + 5;
        generateMap();
    }

    void start() {
        
        int drawMode = MOVE;

        bool spawnExists= false;
        char drawTile = SPACE;
        


        bool active = true;
        int posX = 0, posY = 0;
        char c;
        vector<int> oldPos = { 0, 1 };


        draw();
        displayMode(drawMode);
        while (active) {
            displayMode(drawMode);
            displayTile(drawTile);

            gotoxy(oldPos[0], oldPos[1]);
            SetColor(15, 0);
            
            cout << matrix[oldPos[1]][oldPos[0]];

            SetColor();
            gotoxy(posX, posY);
            SetColor(0, 15);
            cout << matrix[posY][posX];

            for (int i = 0; i < portals.size(); i++) {
                gotoxy(portals[i].x, portals[i].y);
                SetColor(portals[i].color, (posX == portals[i].x && posY == portals[i].y ? 15 : 0));
                
                cout << '0';
            }

            
            



            c = _getch();
            oldPos = { posX, posY };
            switch (c) {
            case KEY_UP:
                if (posY > 0) posY--;
                break;
            case KEY_DOWN:
                if (posY < height - 1) posY++;
                break;
            case KEY_RIGHT:
                if (posX < width - 1)posX++;
                break;
            case KEY_LEFT:
                if (posX > 0)posX--;
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
            case 0x34:
                if (drawTile == PORTAL) {
                    portalColor++;
                    portalColor %= 16;
                    if (portalColor == 0)portalColor++;
                } else drawTile = PORTAL;
                break;
            case 'z': case 'Z':
                drawMode = MOVE;
                break;
            case 'x': case 'X':
                drawMode = DRAW;
                break;
            case 'c': case 'C':
                drawMode = POINTDRAW;
                break;
            case VK_SPACE:
                if (drawMode == POINTDRAW) {
                    if (drawTile == PORTAL) {
                        int sameColorPortals = 0;
                        for (int i = 0; i<portals.size(); i++) { // Смотрим массив порталов
                            if (portals[i].color == portalColor) { // Если цвет портала i равен текущему,
                                if(sameColorPortals < 1)sameColorPortals++; // мы проверяем, был ли он больше, чем вторым
                                else { // Если да, то удаляем последний из порталов этого цвета 
                                    gotoxy(portals[i].x, portals[i].y);
                                    SetColor(15, 0);
                                    cout << SPACE;
                                    portals.erase(portals.begin() + i);
                                }
                            }
                        }

                        for (int i = 0; i < portals.size(); i++) { // удаляем порталы, которые стоят на месте курсора
                            if (portals[i].x == posX && portals[i].y == posY) portals.erase(portals.begin() + i);
                        }
                        
                        portals.push_back({ posX, posY, portalColor });
                        gotoxy(posX, posY);
                        SetColor(portalColor);
                        cout << '0';
                        
                    }
                    else {
                        if (drawTile != SPAWN) matrix[posY][posX] = drawTile;
                        else {
                            for (int i = 0; i < height; i++) {
                                for (int j = 0; j < width; j++) {
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
                        for (int i = 0; i < portals.size(); i++) {
                            if (portals[i].x == posX && portals[i].y == posY) portals.erase(portals.begin() + i);
                        }
                    }
                    
                }
                break;
            case 's': case 'S':
                save();
                break;
            
            case VK_ESCAPE:
                active = false;
                break;
            }
            
            if (drawMode == DRAW) {
                if (drawTile == PORTAL) {
                    int sameColorPortals = 0;
                    for (int i = 0; i < portals.size(); i++) { // Смотрим массив порталов
                        if (portals[i].color == portalColor) { // Если цвет портала i равен текущему,
                            if (sameColorPortals < 1)sameColorPortals++; // мы проверяем, был ли он больше, чем вторым
                            else { // Если да, то удаляем последний из порталов этого цвета 
                                gotoxy(portals[i].x, portals[i].y);
                                SetColor(15, 0);
                                cout << SPACE;
                                portals.erase(portals.begin() + i);
                            }
                        }
                    }
                    for (int i = 0; i < portals.size(); i++) { // удаляем порталы, которые стоят на месте курсора
                        if (portals[i].x == posX && portals[i].y == posY) portals.erase(portals.begin() + i);
                    }


                    portals.push_back({ posX, posY, portalColor });
                    gotoxy(posX, posY);
                    SetColor(portalColor);
                    cout << '0';
                }
                else {
                    if (drawTile != SPAWN) matrix[posY][posX] = drawTile;
                    else {
                        for (int i = 0; i < height; i++) {
                            for (int j = 0; j < width; j++) {
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
                    for (int i = 0; i < portals.size(); i++) {
                        if (portals[i].x == posX && portals[i].y == posY) portals.erase(portals.begin() + i);
                    }
                }
                
            }
            
            
        }
    }
};