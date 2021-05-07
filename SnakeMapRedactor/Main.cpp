#pragma once
#pragma comment(lib, "winmm.lib")
#include "MapEditor.h"
#include <windows.h>
#include <thread>

int main() {
    setlocale(LC_ALL, "");
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
    printRaw(logo, 80, 2, Cyan);
    CenteredMenu mainMenu;
    vector<string> buttons = {"������� �����", "������� �����", "�����"};
    MapEditor mpedit;
    int choose = mainMenu.select_vertical(buttons, 95, 17)+1; // ������� ������ �� ����������� ����� ��� ��������� � ���-�� ��� ��� � ��������
    switch (choose) {
    case 1:
        system("cls");
        mpedit.start();
        break;
    case 3:
        exit(0);
        break;
    }
}