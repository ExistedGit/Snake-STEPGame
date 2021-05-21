#pragma once
#include <string>
#include <iostream>
#include <Windows.h>
#include <vector>
#include <map>
#include <conio.h>
#include <fstream>
#include <filesystem>
#include "FormatText.h"

using namespace std;

using std::filesystem::current_path;
const wstring dir = current_path().wstring();

// Les константы
#define KEY_UP 72
#define KEY_DOWN 80
#define KEY_LEFT 75
#define KEY_RIGHT 77

//Easter Eggs flags
bool g_EE_EXISTED = false,
g_EE_RainbowDash = false;




void ShowConsoleCursor(bool showFlag)
{
	HANDLE out = GetStdHandle(STD_OUTPUT_HANDLE);

	CONSOLE_CURSOR_INFO     cursorInfo;

	GetConsoleCursorInfo(out, &cursorInfo);
	cursorInfo.bVisible = showFlag; // set the cursor visibility
	SetConsoleCursorInfo(out, &cursorInfo);
}






enum Directions {
	UP = 1,
	RIGHT,
	DOWN,
	LEFT
};

struct Snake {
	vector<vector<int>> bodyMatrix = {};
	
	//Длина змейки(включая голову)
	int length = 2;
	//Направление
	int direction = UP;
	// Конструктор шобы удобно было автоматически создавать змеюку любой длины

	void generateSnake(int x, int y, int len) {
		bodyMatrix = {};
		bodyMatrix.push_back(vector<int>{ x, y });
		for (int i = 1; i < len; i++) {
			bodyMatrix.push_back({ bodyMatrix[0][0], bodyMatrix[i - 1][1] + 1 });
		}
		length = len;
	}

	Snake(int x, int y, int len) {
		generateSnake(x, y, len);
	}
	void growTail() {
		length++;
		if (bodyMatrix[bodyMatrix.size() - 2][0] > bodyMatrix[bodyMatrix.size() - 1][0]) {
			bodyMatrix.push_back({ bodyMatrix[bodyMatrix.size() - 1][0] -1, bodyMatrix[bodyMatrix.size() - 1][1]});
		}
		else if(bodyMatrix[bodyMatrix.size() - 2][0] < bodyMatrix[bodyMatrix.size() - 1][0]) {
			bodyMatrix.push_back({ bodyMatrix[bodyMatrix.size() - 1][0] + 1, bodyMatrix[bodyMatrix.size() - 1][1] });
		}
		else if (bodyMatrix[bodyMatrix.size() - 2][1] < bodyMatrix[bodyMatrix.size() - 1][1]) {
			bodyMatrix.push_back({ bodyMatrix[bodyMatrix.size() - 1][0], bodyMatrix[bodyMatrix.size() - 1][1]+1 });
		}
		else if (bodyMatrix[bodyMatrix.size() - 2][1] > bodyMatrix[bodyMatrix.size() - 1][1]) {
			bodyMatrix.push_back({ bodyMatrix[bodyMatrix.size() - 1][0], bodyMatrix[bodyMatrix.size() - 1][1] - 1 });
		}

	}
	// Обновление местоположения змейки
	void Update() {
		//Тут описано движение в разных направлениях
		switch (direction) {
		case UP: // Осторожно: сложные эвристические алгоритмы с применением ИИ
			gotoxy(bodyMatrix[bodyMatrix.size() - 1][0], bodyMatrix[bodyMatrix.size() - 1][1] ); // Тут везде просто двигается голова в нужном направлении и удаляется последний элемент
			cout << " ";
			bodyMatrix.pop_back();
			bodyMatrix.insert(bodyMatrix.begin(), { bodyMatrix[0][0], bodyMatrix[0][1] - 1 });
			break;
		case RIGHT:
			gotoxy(bodyMatrix[bodyMatrix.size() - 1][0] , bodyMatrix[bodyMatrix.size() - 1][1]);
			cout << " ";
			bodyMatrix.pop_back();
			bodyMatrix.insert(bodyMatrix.begin(), { bodyMatrix[0][0]+1, bodyMatrix[0][1]});
			break;
		case LEFT:
			gotoxy(bodyMatrix[bodyMatrix.size() - 1][0] , bodyMatrix[bodyMatrix.size() - 1][1]);
			cout << " ";
			bodyMatrix.pop_back();
			bodyMatrix.insert(bodyMatrix.begin(), { bodyMatrix[0][0] - 1, bodyMatrix[0][1] });
			break;
		case DOWN:
			gotoxy(bodyMatrix[bodyMatrix.size()-1][0], bodyMatrix[bodyMatrix.size()-1][1]);
			cout << " ";
			bodyMatrix.pop_back();
			bodyMatrix.insert(bodyMatrix.begin(), { bodyMatrix[0][0], bodyMatrix[0][1] + 1 });
			break;
		}
	}
	void drawSnake() {
		for (int i = 0; i < length; i++) {
			gotoxy(bodyMatrix[i][0], bodyMatrix[i][1]);
			if (i == 0) {
				
				SetColor(LightMagenta);
				
				cout << "+";
				SetColor();
			}
			else if (i == length - 1) {
				
				SetColor(Green);
				cout << ".";
				SetColor();
			}
			else {
				if (g_EE_EXISTED) SetColor(rand() % 15 + 1); // Пасхалочки
				else if (g_EE_RainbowDash) {
					int rainbow[] = { Red, Brown, Yellow, LightGreen, Cyan, Blue, Magenta };
					SetColor(rainbow[(i-1)%7], 0);
				} else 
					SetColor(LightGreen);
				
				if (bodyMatrix[i + 1][1] > bodyMatrix[i][1]) {
					if (bodyMatrix[i - 1][0] > bodyMatrix[i][0]) {
						cout << "/";
					}
					else if(bodyMatrix[i - 1][0] < bodyMatrix[i][0]){
						cout << "\\";
					}
					else cout << ":";
				}
				else if(bodyMatrix[i + 1][1] < bodyMatrix[i][1]) {
					if (bodyMatrix[i - 1][0] > bodyMatrix[i][0]) {
						cout << "\\";
					}
					else if (bodyMatrix[i - 1][0] < bodyMatrix[i][0]) {
						cout << "/";
					}
					else cout << ":";
				} else if (bodyMatrix[i - 1][1] > bodyMatrix[i][1]) {
						if (bodyMatrix[i + 1][0] > bodyMatrix[i][0]) {
							cout << "/";
						}
						else if (bodyMatrix[i + 1][0] < bodyMatrix[i][0]) {
							cout << "\\";
						}
						else cout << ":";
				} else if (bodyMatrix[i - 1][1] < bodyMatrix[i][1]) {
					if (bodyMatrix[i + 1][0] > bodyMatrix[i][0]) {
						cout << "\\";
					}
					else if (bodyMatrix[i + 1][0] < bodyMatrix[i][0]) {
						cout << "/";
					}
					else cout << ":";
				} else {
					cout << "~";
				}

				SetColor();
			}
		}
	}

	

	

	// Меняет направление движения
	void changeDirection(int c) {
		
		//map, ибо не гоже царской особе switch() использовать
		map<int, int> key_direction = { {KEY_UP, UP}, {KEY_DOWN, DOWN}, {KEY_LEFT, LEFT}, {KEY_RIGHT, RIGHT} }; // Просто карта соответствия направлений и кнопочек
		map<int, int> keyCompatibility = { {KEY_UP, DOWN}, {KEY_DOWN, UP}, {KEY_LEFT, RIGHT}, {KEY_RIGHT, LEFT} }; // Карта несовместимых перенаправлений(e. g. если змейка двигается вправо, то сразу влево повернуть нельзя)
		

		
		if (direction != keyCompatibility[c]) {
			if (key_direction[c]) { // Если передана стрелочка, то направление меняется
				if (direction != key_direction[c]) {
					
					direction = key_direction[c];
					Update();
					drawSnake();
					Sleep(50);
				}
			}
		}
	}

};



