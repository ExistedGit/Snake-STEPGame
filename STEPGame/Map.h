#pragma once
#include "Snake.h"

// магические числа это плохо.
//enum TileTypes {
//	SPACE = 0,
//	BODY,
//	HEAD,
//	WALL,
//	FOOD
//};
enum Difficulties {
	HARD = 1,
	MIDDLE,
	EASY

};
using namespace std;

struct Map {
	// Ширина да высота карты
	int width = 40, height= 40;
	
	int difficulty=HARD;
	vector<vector<int>> food;
	vector<vector<int>> walls;
	
	

	bool isRunning = false;
	
	Snake s = Snake(width/2, height/2);
	
	

	// Отрисовывает карту в первый раз
	void Draw(string map = "./Maps/Default.snakemap") {
		ifstream fin(map);
		char c;
		char buff[80];
		int l = 0;

		vector<int> snakePos = {0, 0};
		while (fin.getline(buff, 80)) {
			for (int i = 0; buff[i] != '\0'; i++) {
				if (buff[i] == '#') walls.push_back({i,l});
				else if (buff[i] == '+') {
					snakePos = { i,l };
				}
			}
			l++;
		}
		
		for (int i = 0; i < walls.size(); i++) {
			gotoxy(walls[i][0], walls[i][1]);
			cout << "#";
		}
		spawnSnake(snakePos[0], snakePos[1]);
		/*for (int i = 0; i < height; i++){
			cout << "#";
			for (int j = 1; j < width; j++) {
				if (i == 0 || i == height - 1) {
					cout << "#";
					
				}
				else {
					cout << " ";
					
				}
			}
			
			cout << "#";
			cout << endl;
		}*/
		isRunning = true;
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
		displayLength();
			
		while (isRunning) {
			ShowConsoleCursor(false);
			
			if (food.empty()) {
				generateFood();
			};
			
			if (_kbhit()) {
				int c; // Переменная, в которую засовывается направление
				c = _getch(); // Если кнопка была нажата, передаёт значение кнопки на проверку
				s.changeDirection(c);
				continue;
			}
			Sleep(150 * difficulty);
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
			
			for (int i = 1; i < s.bodyMatrix.size(); i++) {
				if (s.bodyMatrix[0][0] == s.bodyMatrix[i][0] && s.bodyMatrix[0][1] == s.bodyMatrix[i][1]) isRunning = false;
						
				;
			}

			for (int j = 0; j < walls.size(); j++) {
				if(s.bodyMatrix[0][0] == walls[j][0] && s.bodyMatrix[0][1] == walls[j][1]) isRunning = false;
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