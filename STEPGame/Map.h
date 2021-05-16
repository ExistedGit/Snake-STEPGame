#pragma once

#pragma comment(lib, "winmm.lib")

#include "../SnakeMapRedactor/MapEditor.h"
#include "Snake.h"
#include "Account.h"
#include <mmsystem.h>
#include<stdlib.h>
#include <filesystem>
//#include <thread>







enum Difficulties {
	HARD = 1,
	MIDDLE,
	EASY
};

using namespace std;
using std::filesystem::current_path;
const wstring dir = current_path().wstring();





void playBiteSound() {
	
	wstring _dir = dir;
	_dir.append(L"\\Resources\\bite.wav");
	PlaySound(_dir.c_str(), NULL, SND_ASYNC | SND_FILENAME);
}

void playGameOverSound() {

	wstring _dir = dir;
	_dir.append(L"\\Resources\\gameOver.wav");
	PlaySound(_dir.c_str(), NULL, SND_ASYNC | SND_FILENAME);
}
void playPortalSound() {
	wstring _dir = dir;
	_dir.append(L"\\Resources\\portal.wav");
	PlaySound(_dir.c_str(), NULL, SND_ASYNC | SND_FILENAME);
}
void playMusic() {
	wstring _dir = dir;
	_dir.append(L"\\Resources\\menuMusic.wav");
	PlaySound(_dir.c_str(), NULL,SND_SYNC | SND_FILENAME);
}
// ASYNC-версия
void _playMusic() {
	wstring _dir = dir;
	_dir.append(L"\\Resources\\menuMusic.wav");
	PlaySound(_dir.c_str(), NULL, SND_ASYNC | SND_FILENAME);
}


struct Map {
	// Ширина да высота карты
	int width = 20, height= 20;
	int score = 0;
	int difficulty=HARD;

	// Векторы векторов с координатами всякого. Да, я мог использовать класс COORD или соорудить свой, но различие минимально
	vector<vector<int>> food; 
	vector<vector<int>> walls;
	vector<Portal> portals;

	Account acc;

	bool isRunning = false;	
	
	Snake s = Snake(width/2, height/2, 2);
	
	

	void reset() {
		s = Snake(width / 2, height / 2, 2);
		food = {};
		walls = {};
		portals = {};
		acc = Account();
		score = 0;


		g_EE_EXISTED = false;
		g_EE_RainbowDash = false;
	}

	// Отрисовывает карту в первый раз
	void Draw(wstring map = L"") {
		
		if (map == L"") {
			wchar_t buff[MAX_PATH];
			GetModuleFileName(NULL, buff, MAX_PATH);
		}
		
		ifstream fin(map);
		char c;
		char buff[320];
		int l = 0;
		vector<int> snakePos = {};
		while (fin.getline(buff, 320)) { // Переработка файла в данные матрицы
			for (int i = 0; buff[i] != '\0'; i++) {
				if (buff[i] == '#') walls.push_back({ i,l });
				else if (buff[i] == '+') {
					snakePos = { i,l };
				}
				else if(hexIntMap.count(buff[i])){

					portals.push_back({ i, l, hexIntMap[buff[i]] });
				}
				
				width = strlen(buff);
			}
			l++;
		}
		height = l;
		
		for (int i = 0; i < walls.size(); i++) {
			gotoxy(walls[i][0], walls[i][1]);
			cout << "#";
		}

		for (int i = 0; i < portals.size(); i++) {
			gotoxy(portals[i].x, portals[i].y);
			SetColor(portals[i].color);
			cout << '0';
			SetColor();
		}

		if (snakePos.empty()) {
			snakePos = {width/2, height/2};
		}

		spawnSnake(snakePos[0], snakePos[1]);
		
		isRunning = true;
	}
	void snakeCheck() { // Проверяет, не столкнулась ли змейка с препятствием
		for (int i = 1; i < s.bodyMatrix.size(); i++) {
			if (s.bodyMatrix[0][0] == s.bodyMatrix[i][0] && s.bodyMatrix[0][1] == s.bodyMatrix[i][1]) isRunning = false;
		}

		for (int j = 0; j < walls.size(); j++) {
			if (s.bodyMatrix[0][0] == walls[j][0] && s.bodyMatrix[0][1] == walls[j][1]) isRunning = false;
		}

		for (int i = 0; i < portals.size(); i++) { // Обрабатываем портальные взаимодействия
			
			if (s.bodyMatrix[0][0] == portals[i].x && s.bodyMatrix[0][1] == portals[i].y) {
				Portal travelPortal = portals[i];
				for (int j = 0; j < portals.size(); j++) {
					if(j != i) if (portals[j].color == portals[i].color) travelPortal = portals[j];
				}

				switch (s.direction) {
				case UP:
					s.bodyMatrix[0][0] = travelPortal.x;
					s.bodyMatrix[0][1] = travelPortal.y - 1;
					break;
				case RIGHT:
					s.bodyMatrix[0][0] = travelPortal.x + 1;
					s.bodyMatrix[0][1] = travelPortal.y;
					break;
				case DOWN:
					s.bodyMatrix[0][0] = travelPortal.x;
					s.bodyMatrix[0][1] = travelPortal.y + 1;
					break;
				case LEFT:
					s.bodyMatrix[0][0] = travelPortal.x - 1;
					s.bodyMatrix[0][1] = travelPortal.y;
					break;
				}
				
				playPortalSound();

				for (int i = 0; i < portals.size(); i++) {
					gotoxy(portals[i].x, portals[i].y);
					SetColor(portals[i].color);
					cout << '0';
					SetColor();
				}
			}
		}
	}

	void foodCheck() { // Проверяет, была ли съедена еда
		for (int i = 0; i < food.size(); i++) {
			if (s.bodyMatrix[0][0] == food[i][0] && s.bodyMatrix[0][1] == food[i][1]) {
				food.pop_back();
				s.growTail();
				score += 10;
				displayLength();
				displayScore();

				if (score > acc.score) acc.score = score;

				displayAcc();


				playBiteSound();

			}
		}
		for (int i = 1; i < s.bodyMatrix.size(); i++) {
			for (int j = 0; j < food.size(); j++) {
				if (s.bodyMatrix[i][0] == food[j][0] && s.bodyMatrix[i][1] == food[j][1]) {
					food.pop_back();
				}
			}
		}
		if (!food.empty()) {
			for (int i = 0; i < food.size(); i++) {
				for (int j = 0; j < walls.size(); j++) {
					if (food[i][0] == walls[j][0] && food[i][1] == walls[j][1])
					{
						gotoxy(food[i][0], food[i][1]);
						cout << '#';
						food.pop_back();
						break;
					}
				}
			}
		}
	}
	
	

	// Ставит в нужную точку карты змейку
	void spawnSnake(int posX, int posY) {
		s = Snake(posX, posY, s.length);
	}

	void displayLength() {
		gotoxy(width+3, height/2);
		SetColor(15);
		cout << "Длина: "<< s.length;
		SetColor();
	}

	void displayScore() {
		gotoxy(width + 3, height / 2 - 2);
		SetColor(15);
		cout << "Счёт: " << score;
		SetColor();
	}

	void displayAcc() {
		gotoxy(width + 3, height / 2 - 4);
		cout << acc.name;
		gotoxy(width + 3, height / 2 - 3);
		cout << "Рекорд: " << acc.score;
	}
	

	void generateFood() {
		int posX =rand() % (width - 2) + 2;
		int posY = rand()%(height-3)+2;
		
		for (int i = 0; i < walls.size(); i++) {
			if ((walls[i][0] == posX && walls[i][1] == posY)) {
				generateFood();
				return;
			}
		}

		for (int i = 0; i < portals.size(); i++) {
			if (portals[i].x == posX && portals[i].y == posY) {
				generateFood();
				return;
			}
		}

		food.push_back({posX, posY});
		gotoxy(food[food.size()-1][0], food[food.size() - 1][1]);
		SetColor(LightRed);
		cout << "@";
		SetColor();
	}

	void Update() {
		displayLength();
		displayScore();
		displayAcc();
		while (isRunning) {
			ShowConsoleCursor(false);
			
			
			
			if (_kbhit()) {
				int c; // Переменная, в которую засовывается направление
				c = _getch(); // Если кнопка была нажата, передаёт значение кнопки на проверку
				if (c == VK_ESCAPE) { // Если нажат Escape, цикл останавливается
					isRunning = false;
					break;
				}
				s.changeDirection(c);
				snakeCheck();
				foodCheck();
				continue;
			}
			Sleep(150 * difficulty);
			s.Update();
			s.drawSnake();
			
			gotoxy(0, height);
			foodCheck();
			snakeCheck();
			
			
			gotoxy(0, height+1);
			if (food.empty()) {
				generateFood();
			};
		}
		gotoxy(width / 2 - 4, height / 2);
		SetColor(Red);
		cout << "GAME OVER";
		playGameOverSound();
		SetColor();
		gotoxy(0, height+5);
		system("pause>nul");
		system("cls");
		PlaySound(NULL, NULL, SND_ASYNC);
	}
};


