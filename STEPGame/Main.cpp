#pragma once

#include "Map.h"
#include "Menu.h"
#include "../SnakeMapRedactor/MapEditor.h";

using namespace std;




int main() {
	setlocale(LC_ALL, "");
	cout.setf(ios::boolalpha);
	ShowConsoleCursor(false);
	ShowWindow(GetConsoleWindow(), SW_MAXIMIZE);

	string logo = R"Main(
  ________   _____  ___         __       __   ___    _______  
 /"       ) (\"   \|"  \       /""\     |/"| /  ")  /"     "| 
(:   \___/  |.\\   \    |     /    \    (: |/   /  (: ______) 
 \___  \    |: \.   \\  |    /' /\  \   |    __/    \/    |   
  __/  \\   |.  \    \. |   //  __'  \  (// _  \    // ___)_  
 /" \   :)  |    \    \ |  /   /  \\  \ |: | \  \  (:      "| 
(_______/    \___|\____\) (___/    \___)(__|  \__)  \_______) )Main";
	
	while (true) {
		printRaw(logo, 80, 2, LightGreen);
		Map mainMap;
		CenteredMenu mainMenu;
		vector<string> buttons = { "Новая игра", "Настройки", "Выход" };
		int chooseMain = mainMenu.select_vertical(buttons, 108, 12) + 1;
		system("cls");
		switch (chooseMain) {
		case 1:
			mainMap.Draw();
			mainMap.Update();
			break;
		case 2:
			vector<string> left = { "Сложность", "Длина змейки", "Длина за каждую еду" };
			vector<vector<string>> right = { {"Easy", "Middle", "Hard"}, {"+0", "+5", "+10"}, {"+1", "+2", "+3"} };

			SettingsMenu settings;
			map<int, int> choose = settings.startMenu(left, right);
			
			mainMap.difficulty = 4 - choose[0] - 1;
			
			break;
		}
		/*vector<string> gameOver = {" _____   ___  ___  ___ _____      _____  _   _  _____ ______",
								   "|  __ \\ / _ \\ |  \\/  ||  ___|    |  _  || | | ||  ___|| ___ \\",
								   "| |  \\// /_\\ \\| .  . || |__      | | | || | | || |__  | |_/ /",
								   "| | __ |  _  || |\\/| ||  __|     | | | || | | ||  __| |    / ",
							   	   "| |_\\ \\| | | || |  | || |___     \\ \\_/ /\\ \\_/ /| |___ | |\\ \\ ",
		                           " \\____/\\_| |_/\\_|  |_/\\____/      \\___/  \\___/ \\____/ \\_| \\_|"};*/

		
	
		
		
		
		system("pause");
		
		system("cls");
	
		
		
		
	}
}