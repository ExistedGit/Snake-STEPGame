#pragma once
#include <iostream>
#include <Windows.h>
#include <vector>
#include <map>
#include <conio.h>
#include <fstream>
using namespace std;


// Les константы
#define KEY_UP 72
#define KEY_DOWN 80
#define KEY_LEFT 75
#define KEY_RIGHT 77



enum ConsoleColor
{
	Black = 0,
	Blue = 1,
	Green = 2, Cyan = 3, Red = 4, Magenta = 5, Brown = 6, LightGray = 7, DarkGray = 8,
	LightBlue = 9, LightGreen = 10, LightCyan = 11, LightRed = 12, LightMagenta = 13, Yellow = 14, White = 15
};

void ShowConsoleCursor(bool showFlag)
{
	HANDLE out = GetStdHandle(STD_OUTPUT_HANDLE);

	CONSOLE_CURSOR_INFO     cursorInfo;

	GetConsoleCursorInfo(out, &cursorInfo);
	cursorInfo.bVisible = showFlag; // set the cursor visibility
	SetConsoleCursorInfo(out, &cursorInfo);
}


void SetColor(int text = 7, int background = 0) {
	HANDLE hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(hStdOut, (WORD)((background << 4) | text));
};

void gotoxy(int x, int y)
{
	COORD coord;
	coord.X = x;
	coord.Y = y;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}

template <class T>
void addElement(T*& a, int& n, T elem, int index = -1) {
	if (index == -1) index = n-1;
	if (n < index) return;
	n++;
	T* p = new T[n];
	int shift = 0;
	for (size_t i = 0; i < n; i++)
	{
		if (i == index)
		{
			p[i] = elem;
			shift = 1;
			continue;
		}
		p[i] = a[i - shift];
	}

	a = p;
}

template <class T>
void removeElement(T*& a, int& n, int index = -1) {
	if (index == -1) index = n;
	if (n < index) return;

	T* p = new T[n - 1];
	for (int i = 0; i < index; i++) {
		p[i] = a[i];
	}
	for (int i = index + 1; i < n; i++) {
		p[i - 1] = a[i];
	}
	delete[]a;
	n--;
	a = p;	
}

// Показывает на экран матрицу а.
template <class T>
void showMatrix(T** a, int row, int col) {
	for (int i = 0; i < row; i++) {
		for (int j = 0; j < col; j++) {
			cout << a[i][j] << " ";
		}
		cout << endl;
	}
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
	int length = 15;
	//Направление
	int direction = UP;
	// Конструктор шобы удобно было автоматически создавать змеюку любой длины
	Snake(int x, int y) {
		bodyMatrix.push_back(vector<int>{ x,y });
		for (int i = 1; i < length; i++) {
			bodyMatrix.push_back({bodyMatrix[0][0], bodyMatrix[i-1][1] +1});
		}
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
				SetColor(ConsoleColor::LightMagenta);
				cout << "+";
				SetColor();
			}
			else if (i == length - 1) {
				SetColor(Green);
				cout << ".";
				SetColor();
			}
			else {
				SetColor(LightGreen);
				cout << "~";
				SetColor();
			}
		}
	}

	

	

	// Меняет направление движения
	void changeDirection(int c) {
		
		//map, ибо не гоже царской особе switch() использовать
		map<int, int> key_direction = { {KEY_UP, UP}, {KEY_DOWN, DOWN}, {KEY_LEFT, LEFT}, {KEY_RIGHT, RIGHT} };
		map<int, int> keyCompatibility = { {KEY_UP, DOWN}, {KEY_DOWN, UP}, {KEY_LEFT, RIGHT}, {KEY_RIGHT, LEFT} };
		

		// Ладно, me.trick() вернул значение true, вы были наглым образом обмануты


		if (direction != keyCompatibility[c]) {
			if (key_direction[c]) {// Если передана стрелочка, то направление меняется
				if (direction != key_direction[c]) {
					
					direction = key_direction[c];
					Update();
					drawSnake();
					Sleep(100);
				}
			}
		}
	}

};



