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
    vector<string> buttons = {"Создать карту", "Открыть карту", "Выйти"};
    MapEditor mpedit;
    while (true) {
        printRaw(logo, 80, 2, Cyan);
        int choose = mainMenu.select_vertical(buttons, 95, 17) + 1; // Менюшка кароче на координатах прямо под логотипом и где-то как раз в середине
        system("cls");
        switch (choose) {
        case 1:
            
            mpedit.start();
            break;
        case 2:
            if(mpedit.load()) mpedit.start();
            break;
        case 3:
            exit(0);
            break;
        }
    }
}