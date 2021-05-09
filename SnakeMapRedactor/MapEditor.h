#pragma once
#include <iostream>
#include "../STEPGame/Menu.h"
#include <shobjidl.h> 
#include <tchar.h>
#include <stdio.h>
#include <strsafe.h>

#define SPACE ' '
#define WALL '#'
#define HEAD '+'

#define BUFFERSIZE 4000
DWORD g_BytesTransferred = 0;


VOID CALLBACK FileIOCompletionRoutine(
    __in  DWORD dwErrorCode,
    __in  DWORD dwNumberOfBytesTransfered,
    __in  LPOVERLAPPED lpOverlapped)
{
    _tprintf(TEXT("Error code:\t%x\n"), dwErrorCode);
    _tprintf(TEXT("Number of bytes:\t%x\n"), dwNumberOfBytesTransfered);
    g_BytesTransferred = dwNumberOfBytesTransfered;
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
    void load() {
        system("cls");
        OPENFILENAME ofn;       // common dialog box structure
        char szFile[BUFFERSIZE];   // buffer for file name
        DWORD  dwBytesRead = 0;
        HWND hwnd = GetConsoleWindow();              // owner window
        HANDLE hf = NULL;              // file handle
        OVERLAPPED ol = { 0 };
        // Initialize OPENFILENAME
        ZeroMemory(&ofn, sizeof(ofn));
        ofn.lStructSize = sizeof(ofn);
        ofn.hwndOwner = hwnd;
        ofn.lpstrFile = LPWSTR(szFile);
        // Set lpstrFile[0] to '\0' so that GetOpenFileName does not 
        // use the contents of szFile to initialize itself.
        ofn.lpstrFile[0] = '\0';
        ofn.nMaxFile = sizeof(szFile);
        ofn.lpstrFilter = TEXT("SnakeMap\0*.SNAKEMAP\0");
        ofn.nFilterIndex = 1;
        ofn.lpstrFileTitle = NULL;
        ofn.nMaxFileTitle = 0;
        ofn.lpstrInitialDir = NULL;
        ofn.Flags = OFN_PATHMUSTEXIST | OFN_FILEMUSTEXIST;

        // Display the Open dialog box. 

        if (GetOpenFileName(&ofn) == TRUE)
            hf = CreateFile(ofn.lpstrFile,
                GENERIC_READ,
                FILE_SHARE_READ,
                (LPSECURITY_ATTRIBUTES)NULL,
                OPEN_EXISTING,
                FILE_ATTRIBUTE_NORMAL | FILE_FLAG_OVERLAPPED,
                (HANDLE)NULL);
        BOOL bErrorFlag = FALSE;
        // Read one character less than the buffer size to save room for
 // the terminating NULL character. 
        
        if (FALSE == ReadFileEx(hf, szFile, BUFFERSIZE - 1, &ol, FileIOCompletionRoutine))
        {
            
            printf("Terminal failure: Unable to read from file.\n GetLastError=%08x\n", GetLastError());
            CloseHandle(hf);
            return;
        
        }

        SleepEx(5000, TRUE);
        dwBytesRead = g_BytesTransferred;
        if (dwBytesRead > 0 && dwBytesRead <= BUFFERSIZE - 1)
        {
            szFile[dwBytesRead] = '\0'; // NULL character

            cout<<"Data read from %s (%d bytes): \n" << dwBytesRead << endl;
            printf("%s\n", szFile);
        }
        else if (dwBytesRead == 0)
        {
            cout << "no data\n";
        }
        else
        {
            printf("\n ** Unexpected value for dwBytesRead ** \n");
        }

        vector<int> lengthes;

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