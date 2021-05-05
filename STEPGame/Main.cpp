#pragma once
#include "Map.h"
#include "Menu.h"

using namespace std;


class CFoo {
public:
	int m_i = 0;
	void bar() {
		++m_i;
	}
};

int main() {
	setlocale(LC_ALL, "");
	cout.setf(ios::boolalpha);
	ShowConsoleCursor(false);
	ShowWindow(GetConsoleWindow(), SW_MAXIMIZE);

	//CFoo foo;
	//thread t1(&CFoo::bar, &foo);
	//t1.join();
	//std::cout << foo.m_i << std::endl;
	while (true) {
		CenteredMenu mainMenu;

		/*vector<string> gameOver = {" _____   ___  ___  ___ _____      _____  _   _  _____ ______",
								   "|  __ \\ / _ \\ |  \\/  ||  ___|    |  _  || | | ||  ___|| ___ \\",
								   "| |  \\// /_\\ \\| .  . || |__      | | | || | | || |__  | |_/ /",
								   "| | __ |  _  || |\\/| ||  __|     | | | || | | ||  __| |    / ",
							   	   "| |_\\ \\| | | || |  | || |___     \\ \\_/ /\\ \\_/ /| |___ | |\\ \\ ",
		                           " \\____/\\_| |_/\\_|  |_/\\____/      \\___/  \\___/ \\____/ \\_| \\_|"};*/

		
		vector<string> buttons = { "Новая игра", "Настройки", "Выход" };
		vector<string> left = { "Сложность", "Длина змейки", "Длина за каждую еду" };
		vector<vector<string>> right = { {"Easy", "Middle", "Hard"}, {"+0", "+5", "+10"}, {"+1", "+2", "+3"} };
		
		SettingsMenu settings;
		SettingsMenuCoord choose = settings.startMenu(left, right);
		choose.left++;
		choose.right++;
		int difficulty = HARD;
		switch (choose.left) {
		case 1:
			difficulty = 4 - choose.right;
			break;
		}
		system("pause");
		
		//int choose = mainMenu.select_vertical(buttons) + 1;

		switch (true) {
		case 1:
			system("cls");
			Map mainMap;
			mainMap.difficulty = difficulty;
			mainMap.Draw();
			mainMap.spawnSnake();


			thread valera(&Map::keyPress, &mainMap);
			mainMap.Update();
			valera.detach();
			break;
		}

		system("pause");
		system("cls");
	}
}