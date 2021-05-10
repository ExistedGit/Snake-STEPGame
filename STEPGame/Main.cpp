#pragma once


#include <iomanip>
#include "Map.h"
#include "Menu.h"
#include "../SnakeMapRedactor/MapEditor.h";
#include "Account.h"




using namespace std;

void easterEggCheck(string name) {
	if (name == "EXISTED") {
		g_EE_EXISTED = true;
	}
	else if (name == "Rainbow Dash") {
		g_EE_RainbowDash = true;
	}
}

void showTable(vector<Account> acc) {
	const int tableWidth = 30; // ну а чё б и нет в принципе, так удобнее и понятнее, что это за 30
	
	gotoxy(90 + 7, 15);
	cout << "ТАБЛИЦА РЕКОРДОВ\n";
	gotoxy(90, 15+1);
	for (int i = 0; i < tableWidth; i++) cout << "=";
	cout << endl;

	for (int i = 0; i < acc.size(); i++) {
		for (int j = 0; j < acc.size(); j++) {
			if(acc[i].score > acc[j].score) swap(acc[i], acc[j]);
		}
	}

	for (int i = 0; i < acc.size(); i++) {
		gotoxy(90, 15 + 2 + i);
		cout << acc[i].name << setw((tableWidth- acc[i].name.size()) < 0 ? 0 : tableWidth - acc[i].name.size()) << acc[i].score << endl;
	}
	system("pause>nul");
}

int main() {
	setlocale(LC_ALL, "");

	
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);

	cout.setf(ios::boolalpha);
	ShowConsoleCursor(false);
	ShowWindow(GetConsoleWindow(), SW_MAXIMIZE);
	SetConsoleTitleW(TEXT("Игра \"Змейка\""));
	string logo = R"Main(
  ________   _____  ___         __       __   ___    _______  
 /"       ) (\"   \|"  \       /""\     |/"| /  ")  /"     "| 
(:   \___/  |.\\   \    |     /    \    (: |/   /  (: ______) 
 \___  \    |: \.   \\  |    /' /\  \   |    __/    \/    |   
  __/  \\   |.  \    \. |   //  __'  \  (// _  \    // ___)_  
 /" \   :)  |    \    \ |  /   /  \\  \ |: | \  \  (:      "| 
(_______/    \___|\____\) (___/    \___)(__|  \__)  \_______) )Main";
	vector<int> positions = { 0, 0, 0 }; // Выбранные настройки сохраняются здесь
	Map mainMap;
	wstring mapFile = L"C:\\Users\\paytv\\source\\repos\\STEPGame\\STEPGame\\Maps\\Default.snakemap";
	CenteredMenu mainMenu;
	vector<string> buttons = { "Новая игра", "Таблица рекордов", "Настройки", "Выход" };
	while (true) {
		printRaw(logo, 80, 2 + 10, LightGreen);
		
		vector<Account> acc = loadAccounts();
		int chooseMain = mainMenu.select_vertical(buttons, 105, 12 + 10) + 1;

		

		system("cls");
		switch (chooseMain) {
		case 1: {
			mainMap.reset();

			Account a;

			gotoxy(80, 20);
			char name[80];
			cout << "Введите своё имя: ";
			cin.getline(name, 80);

			easterEggCheck(name);

			bool accExists = false;
			int existingAccIndex = -1;
			for (int i = 0; i < acc.size(); i++) {// Проверяем, существует ли такая запись
				if (acc[i].name == (string)name) {
					mainMap.acc = acc[i];
					accExists = true;
					existingAccIndex = i;
				}
			}
			if (mainMap.acc.score == -1) { // Если стоит значение по умолчанию(которое не может являться счётом)
				mainMap.acc = { (string)name, 0 };
			}
			
			system("cls");
			gotoxy(90, 20);
			cout << "Импортировать карту?";
			int loadMap = mainMenu.select_vertical({ "Да", "Нет" }, 98, 21) + 1;
			if (loadMap == 1) mapFile = openfilename(L"SnakeMap\0*.snakemap\0");
			else mapFile = DEFAULT_MAP_FILE;
			system("cls");
			
			mainMap.Draw(mapFile);
			mainMap.Update();

			if (!accExists) acc.push_back(mainMap.acc); // Сохраняем в массив данные записи
			else acc[existingAccIndex] = mainMap.acc;
			saveAccounts(acc); // Сохраняем всё это в файл
			break;
		}
		case 2:
			showTable(acc);
			break;
		case 3: {
			vector<string> left = { "Сложность", "Длина змейки", "Длина за каждую еду" };
			vector<vector<string>> right = { {"Hard", "Middle", "Easy"}, {"+0", "+5", "+10"}, {"+1", "+2", "+3"} };

			SettingsMenu settings;
			map<int, int> choose = settings.startMenu(left, right, 90, 20, positions);

			mainMap.difficulty = choose[0] + 1;
			
			switch (choose[1]) {
			case 1:
				mainMap.s.length += 5;
				break;
			case 2:
				mainMap.s.length += 10;
				break;
			}
			
			
			positions = {};
			for (int i = 0; i < choose.size(); i++) {
				positions.push_back(choose[i]);
			}

			break;
		}
		case 4:
			exit(0);
			break;
		}
		/*vector<string> gameOver = {" _____   ___  ___  ___ _____      _____  _   _  _____ ______",
								   "|  __ \\ / _ \\ |  \\/  ||  ___|    |  _  || | | ||  ___|| ___ \\",
								   "| |  \\// /_\\ \\| .  . || |__      | | | || | | || |__  | |_/ /",
								   "| | __ |  _  || |\\/| ||  __|     | | | || | | ||  __| |    / ",
							   	   "| |_\\ \\| | | || |  | || |___     \\ \\_/ /\\ \\_/ /| |___ | |\\ \\ ",
		                           " \\____/\\_| |_/\\_|  |_/\\____/      \\___/  \\___/ \\____/ \\_| \\_|"};*/

		
	
		
		
		
		
		
		system("cls");
	
		
		
		
	}
}