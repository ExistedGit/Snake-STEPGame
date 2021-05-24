#pragma once


#include <iomanip>
#include "Map.h"
#include "Menu.h"
#include "SlideShow.h"

#include <mmdeviceapi.h>

using namespace std;

#define MAX_WARNING_STRSIZE 40

bool aboutAuthor() { // Возвращает false, если выбран вариант "Назад"
	string raw = R"Au(%4Об авторе

Я %2Осипов Дмитрий Максимович%7, также известный как Джим Керри, DarkL1ght и Existed, мне %3014 лет%7.
Как вы уже заметили, это учебный проект, созданный в качестве экзаменационной работы для %6КА "ШАГ"%7.
Сюда я попал достаточно давно, так как у меня была диагностирована неизлечимая тяга к созданию ПО.
Эту игру я создал для переосмысления глобального концепта змейки. Эта Змейка не такая, как остальные. Она %Aнавороченная%7.
При создании игры я помогал и мне помогал %2Алекс-Тейлор%7, также известный как dankozz1t.
Рекомендую посетить его %6GitHub%7-репозиторий и ознакомиться с Крысой.)Au";
	printRawF(raw, 115,20, true);
	vector<string> buttons = {"Перейти на GitHub Змейки", "Перейти на GitHub Крысы", "Назад"};


	CenteredMenu menu;
	int choose = menu.select_vertical(buttons, 100, 30) + 1;
	if (choose == 1) system("start https://github.com/ExistedGit/Snake-STEPGame");
	else if (choose == 2) system("start https://github.com/dankozz1t/RatSimulator");
	
	return choose != 3; // Таким вот образом мы избегаем множественных точек выхода
}
// Run SnakeMapEditor
void runSME() { 
	SHELLEXECUTEINFO ShExecInfo = { 0 };
	ShExecInfo.cbSize = sizeof(SHELLEXECUTEINFO);
	ShExecInfo.fMask = SEE_MASK_NOCLOSEPROCESS;
	ShExecInfo.hwnd = NULL;
	ShExecInfo.lpVerb = _T("open");
	if (!fileExists(dir + L"\\SnakeMapEditor.exe")) ShExecInfo.lpFile = _T("SnakeMapEditor");
	else ShExecInfo.lpFile = _T("SnakeMapEditor.exe");
	ShExecInfo.lpDirectory = dir.c_str();
	ShExecInfo.nShow = SW_SHOW;
	ShExecInfo.hInstApp = NULL;
	ShellExecuteEx(&ShExecInfo);
}


void easterEggCheck(string name) {
	if (name == "EXISTED") {
		g_EE_EXISTED = true;
	}
	else if (name == "Rainbow Dash") {
		g_EE_RainbowDash = true;
	}
}

COORD GetConsoleCursorPosition(HANDLE hConsoleOutput = GetStdHandle(STD_OUTPUT_HANDLE))
{
	CONSOLE_SCREEN_BUFFER_INFO cbsi;
	if (GetConsoleScreenBufferInfo(hConsoleOutput, &cbsi))
	{
		return cbsi.dwCursorPosition;
	}
	else
	{
		// The function failed. Call GetLastError() for details.
		COORD invalid = { 0, 0 };
		return invalid;
	}
}


void mciSend(wstring ws) {
	mciSendStringW(ws.c_str(), NULL, 0, 0);
}

int main() {
	setlocale(LC_ALL, "");




	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);


	cout.setf(ios::boolalpha);
	ShowConsoleCursor(false);
	ShowWindow(GetConsoleWindow(), SW_MAXIMIZE);
	SetConsoleTitleW(TEXT("Игра \"Змейка\""));



	Slide slides = { {R"Slide(
########################################
#                                      #
#      %2.~~~~~~%D+%7                        #
#                                      #
########################################
)Slide", R"Slide(
########################################
#                                      #
#       %2.~~~~~~%D+%7                       #
#                                      #
########################################
)Slide", R"Slide(
########################################
#                                      #
#        %2.~~~~~~%D+%7                      #
#                                      #
########################################
)Slide"}, "Передвижение", "Важнейшим аспектом \"Змейки\" является передвижение." };




	/*SlideShow movement(slides);

	SlideMenu slidemenu;
	slidemenu.select_vertical({movement});*/


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

	loadAccount();
	atexit(saveAccount);

	wstring defaultMapDir = dir;
	defaultMapDir.append(L"\\Maps\\Default.snakemap");
	wstring mapFile = defaultMapDir;
	OrbitedCenteredMenu mainMenu;
	vector<string> buttons = { "Новая игра", "Обучение",  "Достижения", "Настройки", "Редактор карт", "Об авторе", "Выход" };

	wstring musicFile = dir;
	musicFile.append(L"\\Resources\\menuMusic.wav");

	int snakeLengthModifier = 0;

	bool firstLogoPrint = true,
		musicPaused = true;


	mciSendStringW(L"open \"Resources/menuMusic.mp3\" type mpegvideo alias music", NULL, 0, 0);
	while (true) {

		if (firstLogoPrint) {
			_printRaw(logo, 80, 2 + 10, LightGreen, 0, 0, 5);



			gotoxy(80 + 10, 25);

			cout << "Нажмите любую кнопку, чтобы продолжить...";
			mciSendStringW(L"play music from 0 repeat", NULL, 0, 0);
			musicPaused = false;
			system("pause>nul");

			system("cls");
		}
		printRaw(logo, 80, 2 + 10, LightGreen);


		if (!firstLogoPrint && musicPaused) {
			mciSendStringW(L"play music from 0 repeat", NULL, 0, 0);
			musicPaused = false;
		}
		else firstLogoPrint = false;

		gotoxy(90 - mainAcc.name.length() - 2, 23);
		SetColor();
		for (int i = 0; i < mainAcc.name.length()*2 + 3; i++) cout << " ";
		printCentered(mainAcc.name, 90, 23);


		printCentered("Рекорд: " + to_string(mainAcc.maxScore), 90, 23 + 1);
		printCentered("Сыграно игр: " + to_string(mainAcc.games), 90, 23 + 2);

		int chooseMain = mainMenu.select_vertical(buttons, 105, 12 + 10) + 1;



		SetColor();

		switch (chooseMain) {
		case 0: { // Редактирование ника
			
			printRaw("[ENTER] - Изменить имя\n[-> | ESC] - Вернуться", 90 - mainAcc.name.size() / 2 - 5, 27, 15);

			OrbitedCenteredMenu nickEditMenu;
			int editChoose = nickEditMenu.select_vertical({ mainAcc.name }, 90 - mainAcc.name.length() / 2, 23);
			if (editChoose == OMP_RIGHT) {
				printRaw("                      \n                      ", 90 - mainAcc.name.size() / 2 - 5, 27, 15);
				continue;
			}
			if (editChoose != OMP_ESC && editChoose != OMP_LEFT) {
				system("cls");
				gotoxy(30, 32);
				cout << "[ESC] - Выйти	[ENTER] - Сохранить это имя";
				gotoxy(30, 29);
				cout << "Старое имя: " << mainAcc.name;
				gotoxy(30, 30);
				string baseString = "Введите новое имя: ";
				cout << baseString;
				// Авторский метод ввода текста.
				string nickString = "";
				bool escPressed = false;
				while (!escPressed) {
					
					
					char nickChar = _getch();

					gotoxy(30 + baseString.size(), 30 - 2);
					for (int i = 0; i < MAX_WARNING_STRSIZE; i++) cout << " ";
					gotoxy(30 + baseString.size() + nickString.size(), 30);

					if (nickChar == VK_ESCAPE) {
						escPressed = true;
						break;
					}
					else if (nickChar == VK_BACK) {

						if (!nickString.empty()) {
							COORD cursorPos = GetConsoleCursorPosition();
							gotoxy(cursorPos.X - 1, cursorPos.Y);
							cout << " ";
							gotoxy(cursorPos.X - 1, cursorPos.Y);
							nickString.pop_back();
						}
					}
					else if (nickChar == VK_RETURN) {
						if (!nickString.empty()) {
							if (nickString.size() > 20) {
								COORD cursorPos = GetConsoleCursorPosition();
								gotoxy(cursorPos.X - nickString.size(), cursorPos.Y - 2);
								SetColor(Red);
								cout << "Имя не должно быть длиннее 20 символов!";
								SetColor();
							} else break;
						}
						else {
							COORD cursorPos = GetConsoleCursorPosition();
							gotoxy(cursorPos.X - nickString.size(), cursorPos.Y - 2);
							SetColor(Red);
							cout << "Имя не должно быть пустым!";
							SetColor();
						}
					}
					else if (isgraph(nickChar) || isspace(nickChar)) {
						cout << nickChar;
						nickString.push_back(nickChar);
					}
				}
				if (!escPressed) mainAcc.name = nickString;
			}
			break;
		}
		case 1: {
			system("cls");

			mainMap.reset();
			mainMap.s.length += snakeLengthModifier;

			easterEggCheck(mainAcc.name);

			system("cls");
			gotoxy(90, 20);
			cout << "Импортировать карту?";
			int loadMap = mainMenu.select_vertical({ "Да", "Нет" }, 98, 21) + 1;
			if (loadMap == 1)
			{
				mapFile = openfilename(L"SnakeMap\0*.snakemap\0");
				if (mapFile == L"") mapFile = defaultMapDir;
			}
			else mapFile = defaultMapDir;
			system("cls");

			mciSendStringW(L"stop music", NULL, 0, 0); // музыка останавливается перед началом змейки
			musicPaused = true;

			mainMap.Draw(mapFile);
			if (!mainAcc.ach[ACH_FIRSTGAME].completed) {
				mainMap.displayAchievement(mainAcc.ach[ACH_FIRSTGAME].title);
				mainAcc.ach[ACH_FIRSTGAME].completed = true;
			}
			mainMap.Update();

			break;
		}
		case 2:

			break;
		case 3: {
			system("cls");
			AchievementMenu achMenu;
			achMenu.start(mainAcc.ach);
			break;
		}
		case 4: {
			system("cls");

			vector<string> left = { "Сложность", "Длина змейки", "Длина за каждую еду" };
			vector<vector<string>> right = { {"Hard", "Middle", "Easy"}, {"+0", "+5", "+10"}, {"+1", "+2", "+3"} };

			SettingsMenu settings;
			map<int, int> choose = settings.startMenu(left, right, 90, 20, positions);

			mainMap.difficulty = choose[0] + 1;

			switch (choose[1]) {
			case 1:
				snakeLengthModifier = 5;
				break;
			case 2:
				snakeLengthModifier = 10;
				break;
			}


			positions = {};
			for (int i = 0; i < choose.size(); i++) {
				positions.push_back(choose[i]);
			}

			break;
		}
		case 5:
			runSME();
			break;
		case 6: {
			system("cls");

			bool ifReturn = true;
			while (ifReturn) {
				ifReturn = aboutAuthor();
			};
			break;
		}
		case 7:
			exit(0);
			break;
		}

			  system("cls");
			  saveAccount();
		}

	}