#pragma once
#include "Snake.h"

// магические числа это плохо.
enum TileTypes {
	SPACE = 0,
	BODY,
	HEAD,
	WALL,
	FOOD
};
enum Difficulties {
	HARD = 1,
	MIDDLE,
	EASY

};
using namespace std;

struct Map {
	// Ширина да высота карты
	int width = 40, height= 40;
	// Матрица, представляющая карту
	int** matrix = new int*[height];
	int difficulty=HARD;
	vector<vector<int>> food;
	bool isRunning = false;
	
	Snake s = Snake(width/2, height/2);
	
	

	// Отрисовывает карту в первый раз
	void Draw() {
		
		for (int i = 0; i < height; i++){
			cout << "#";
			matrix[i] = new int[width];
			matrix[i][0]=WALL;
			for (int j = 1; j < width; j++) {
				if (i == 0 || i == height - 1) {
					cout << "#";
					matrix[i][j] = WALL;
				}
				else {
					cout << " ";
					matrix[i][j] = SPACE;
				}
			}
			matrix[i][width - 1] = WALL;
			cout << "#";
			cout << endl;
		}
		isRunning = true;
	}

	

	// Ставит в нужную точку карты змейку
	void spawnSnake(int posX = 0, int posY = 0) {
		if (posX == 0) posX = width/2;   //Не, ну а шо оно не позволяет мне засунуть высоту и ширину как дефолтные аргументы
		if (posY == 0) posY = height / 2; //Приходится вот такое городить, дай Бог сработает.

		matrix[posY][posX] = HEAD;
		s.bodyMatrix[0] = {posX, posY};

	}

	void displayLength() {
		gotoxy(width+3, height/2);
		SetColor(15);
		cout << "Длина: "<< s.length;
		SetColor();
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

	static void printSomething(Map m) {
		for (int i = 0; i < 100; i++) {
			gotoxy(m.width + 3, (m.height / 2) + 4);
			SetColor(15);
			cout << i;
			SetColor();
			Sleep(500);
		}
	}
	
	void keyPress() {
		while (true) {
			if (_kbhit()) {
				int c; // Переменная, в которую засовывается направление
				c = _getch(); // Если кнопка была нажата, передаёт значение кнопки на проверку
				s.changeDirection(c);
			}
		}
	}


	void Update() {
		displayLength();
			
		while (isRunning) {
			ShowConsoleCursor(false);
			if (food.empty()) {
				generateFood();
			};
			

			Sleep(200 * difficulty);
			s.Update();
			s.drawSnake();
			
			gotoxy(0, height);
			for (int i = 0; i < food.size(); i++) {
				if (s.bodyMatrix[0][0] == food[i][0] && s.bodyMatrix[0][1] == food[i][1]) {
					food.pop_back();
					s.growTail();
					displayLength();
				}
			}
			for (int i = 1; i < s.bodyMatrix.size();i++) {
				for (int j = 0; j < food.size(); j++) {
					if (s.bodyMatrix[i][0] == food[j][0] && s.bodyMatrix[i][1] == food[j][1]) {
						food.pop_back();
					}
				}
			}
			if (s.bodyMatrix[0][0] > width -1|| s.bodyMatrix[0][0] <=0) isRunning = false;
			if (s.bodyMatrix[0][1] > height -2|| s.bodyMatrix[0][1] <= 0) isRunning = false;
			for (int i = 1; i < s.bodyMatrix.size(); i++) {
				if (s.bodyMatrix[0][0] == s.bodyMatrix[i][0] && s.bodyMatrix[0][1] == s.bodyMatrix[i][1]) isRunning = false;
			}
			gotoxy(0, height+1);
		}
		gotoxy(width / 2 - 4, height / 2);
		SetColor(Red);
		cout << "GAME OVER";
		SetColor();
		gotoxy(0, height+5);
		system("pause");
		system("cls");
	}
};