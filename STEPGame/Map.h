#pragma once
#pragma comment(lib, "winmm.lib")
#include "Snake.h"
#include "Account.h"
#include <thread>






enum Difficulties {
	HARD = 1,
	MIDDLE,
	EASY
};
using namespace std;



void playBiteSound() {
	PlaySound(TEXT("./Resources/bite.wav"), NULL, SND_ASYNC);
	//mciSendString(TEXT("./Resources/bite.wav"), NULL, 0, NULL);
}

struct Map {
	// Ширина да высота карты
	int width = 20, height= 20;
	int score = 0;
	int difficulty=HARD;

	// Векторы векторов с координатами всякого. Да, я мог использовать класс COORD или соорудить свой, но различие минимально
	vector<vector<int>> food; 
	vector<vector<int>> walls;
	
	Account acc;

	bool isRunning = false;	
	
	Snake s = Snake(width/2, height/2);
	
	

	// Отрисовывает карту в первый раз
	void Draw(string map = "./Maps/Default.snakemap") {
		ifstream fin(map);
		char c;
		char buff[80];
		int l = 0;
		vector<int> snakePos = {0, 0};
		while (fin.getline(buff, 80)) { // Переработка файла в данные матрицы
			for (int i = 0; buff[i] != '\0'; i++) {
				if (buff[i] == '#') walls.push_back({ i,l });
				else if (buff[i] == '+') {
					snakePos = { i,l };
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
	}
	

	// Ставит в нужную точку карты змейку
	void spawnSnake(int posX, int posY) {
		s = Snake(posX, posY);
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
		int posX = rand() % (width - 2) + 2;
		int posY = rand()%(height-3)+2;
		
		food.push_back({posX, posY});
		gotoxy(food[food.size()-1][0], food[food.size() - 1][1]);
		SetColor(LightRed);
		cout << "@";
		SetColor();
	}

	void Update() {
		thread stopSound;
		displayLength();
		displayScore();
		displayAcc();
		while (isRunning) {
			ShowConsoleCursor(false);
			
			if (food.empty()) {
				generateFood();
			};
			
			if (_kbhit()) {
				int c; // Переменная, в которую засовывается направление
				c = _getch(); // Если кнопка была нажата, передаёт значение кнопки на проверку
				if (c == VK_ESCAPE) isRunning = false; // Если нажат Escape, цикл останавливается
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
		}
		gotoxy(width / 2 - 4, height / 2);
		SetColor(Red);
		cout << "GAME OVER";
		PlaySound(TEXT("./Resources/gameOver.wav"), NULL, SND_ASYNC);
		SetColor();
		gotoxy(0, height+5);
		system("pause");
		system("cls");
		PlaySound(NULL, NULL, SND_ASYNC);
	}
};


