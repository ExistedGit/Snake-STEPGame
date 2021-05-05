#pragma once
#include "Map.h"
#include "Menu.h"

using namespace std;




int main() {
	setlocale(LC_ALL, "");
	cout.setf(ios::boolalpha);
	ShowConsoleCursor(false);
	ShowWindow(GetConsoleWindow(), SW_MAXIMIZE);

	
	while (true) {
		Map mainMap;
		CenteredMenu mainMenu;
		vector<string> buttons = { "Новая игра", "Настройки", "Выход" };
		int chooseMain = mainMenu.select_vertical(buttons) + 1;
		system("cls");
		switch (chooseMain) {
		case 1:
			mainMap.Draw();
			mainMap.spawnSnake();
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