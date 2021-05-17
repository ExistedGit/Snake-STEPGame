#pragma once


#include <iomanip>
#include "Map.h"
#include "Menu.h"
//#include "../SnakeMapRedactor/MapEditor.h"
#include "Account.h"
#include <mmdeviceapi.h>
#include <endpointvolume.h>

using namespace std;

//bool ChangeVolume(double nVolume, bool bScalar)
//{
//
//	HRESULT hr = NULL;
//	bool decibels = false;
//	bool scalar = false;
//	double newVolume = nVolume;
//
//	CoInitialize(NULL);
//	IMMDeviceEnumerator* deviceEnumerator = NULL;
//	hr = CoCreateInstance(__uuidof(MMDeviceEnumerator), NULL, CLSCTX_INPROC_SERVER,
//		__uuidof(IMMDeviceEnumerator), (LPVOID*)&deviceEnumerator);
//	IMMDevice* defaultDevice = NULL;
//
//	hr = deviceEnumerator->GetDefaultAudioEndpoint(eRender, eConsole, &defaultDevice);
//	deviceEnumerator->Release();
//	deviceEnumerator = NULL;
//
//	IAudioEndpointVolume* endpointVolume = NULL;
//	hr = defaultDevice->Activate(__uuidof(IAudioEndpointVolume),
//		CLSCTX_INPROC_SERVER, NULL, (LPVOID*)&endpointVolume);
//	defaultDevice->Release();
//	defaultDevice = NULL;
//
//	// -------------------------
//	float currentVolume = 0;
//	endpointVolume->GetMasterVolumeLevel(&currentVolume);
//	//printf("Current volume in dB is: %f\n", currentVolume);
//
//	hr = endpointVolume->GetMasterVolumeLevelScalar(&currentVolume);
//	//CString strCur=L"";
//	//strCur.Format(L"%f",currentVolume);
//	//AfxMessageBox(strCur);
//
//	// printf("Current volume as a scalar is: %f\n", currentVolume);
//	if (bScalar == false)
//	{
//		hr = endpointVolume->SetMasterVolumeLevel((float)newVolume, NULL);
//	}
//	else if (bScalar == true)
//	{
//		hr = endpointVolume->SetMasterVolumeLevelScalar((float)newVolume, NULL);
//	}
//	endpointVolume->Release();
//
//	CoUninitialize();
//
//	return FALSE;
//}


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

	wstring defaultMapDir = dir;
	defaultMapDir.append(L"\\Maps\\Default.snakemap");
	wstring mapFile = defaultMapDir;
	CenteredMenu mainMenu;
	vector<string> buttons = { "Новая игра", "Обучение",  "Таблица рекордов", "Настройки", "Выход" };

	wstring musicFile = dir;
	musicFile.append(L"\\Resources\\menuMusic.wav");

	int snakeLengthModifier =0 ;

	bool firstLogoPrint = true,
		musicPaused = true;
	
	//thread musicThread;
	
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
		/*
		musicThread = thread([]() {
			playMusic();
			});*/
		//ChangeVolume(1, true);
		
		if (!firstLogoPrint && musicPaused) {
			mciSendStringW(L"play music from 0 repeat", NULL, 0, 0);
			musicPaused = false;
		}
		else firstLogoPrint = false;

		vector<Account> acc = loadAccounts();
		int chooseMain = mainMenu.select_vertical(buttons, 105, 12 + 10) + 1;

		//ChangeVolume(0, true);
		
		
		system("cls");
		switch (chooseMain) {
		case 1: {
			mainMap.reset();
			mainMap.s.length += snakeLengthModifier;

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
			mainMap.Update();

			if (!accExists) acc.push_back(mainMap.acc); // Сохраняем в массив данные записи
			else acc[existingAccIndex] = mainMap.acc;
			saveAccounts(acc); // Сохраняем всё это в файл
			break;
		}
		case 2:

			break;
		case 3:
			showTable(acc);
			break;
		case 4: {
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
				snakeLengthModifier=10;
				break;
			}
			
			
			positions = {};
			for (int i = 0; i < choose.size(); i++) {
				positions.push_back(choose[i]);
			}

			break;
		}
		case 5:
			//musicThread.detach();
			exit(0);
			break;
		}
		//musicThread.detach();
		system("cls");

	}
	
}