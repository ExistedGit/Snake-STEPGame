#pragma once
#pragma comment(lib, "winmm.lib")
#include "MapEditor.h"
#include <windows.h>
#include <thread>

int main() {
    setlocale(LC_ALL, "");
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);
	ShowWindow(GetConsoleWindow(), SW_MAXIMIZE);
    string logo = R"MAP(
           __  __          _____          
          |  \/  |   /\   |  __ \         
          | \  / |  /  \  | |__) |        
          | |\/| | / /\ \ |  ___/         
          | |  | |/ ____ \| |             
          |_|  |_/_/    \_\_|             
  ______ _____ _____ _______ ____  _____  
 |  ____|  __ \_   _|__   __/ __ \|  __ \ 
 | |__  | |  | || |    | | | |  | | |__) |
 |  __| | |  | || |    | | | |  | |  _  / 
 | |____| |__| || |_   | | | |__| | | \ \ 
 |______|_____/_____|  |_|  \____/|_|  \_\
)MAP";
    
    CenteredMenu mainMenu;
    vector<string> buttons = {"������� �����", "������� �����", "�����"};
    MapEditor mpedit;
    while (true) {
        printRaw(logo, 90, 12, Cyan);
        int choose = mainMenu.select_vertical(buttons, 105, 27) + 1; // ������� ������ �� ����������� ����� ��� ��������� � ���-�� ��� ��� � ��������
        system("cls");
        switch (choose) {
        case 1:
            mpedit.resizeMenu();
            system("cls");
            mpedit.start();
            break;
        case 2:
            if(mpedit.load()) mpedit.start();
            break;
        case 3:
            exit(0);
            break;
        }

        system("cls");
    }
}