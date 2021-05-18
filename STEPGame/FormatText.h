#pragma once

#include <iostream>
#include <string>
#include <map>

using namespace std;

// Я понимаю, что эти глобальные переменные могут быть изменены, но по моему плану они изменяться не будут

map<char, int> hexIntMap = { {'0', 0}, {'1', 1}, {'2', 2}, {'3', 3}, {'4', 4}, {'5', 5}, {'6', 6}, {'7', 7}, {'8', 8}, {'9', 9},
			{'A', 10}, {'B', 11}, {'C', 12}, {'D', 13}, {'E', 14}, {'F', 15} };
map<int, char> intHexMap = { {0, '0'}, {1, '1'}, {2, '2'}, {3, '3'}, {4, '4'}, {5, '5'}, {6, '6'}, {7, '7'}, {8, '8'}, {9, '9'},
			{10, 'A'}, {11, 'B'}, {12, 'C'}, {13, 'D'}, {14, 'E'}, {15, 'F'} };


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

// Тоже улучшенный метод
void _gotoxy(int x, int y, int sizeLen = 0, int sizeHeight = 100) //При наличии размера строки выполняется форматирование по центру
{
	if (sizeLen)
		x = (x + sizeHeight - sizeLen) / 2;

	COORD coord;
	coord.X = x;
	coord.Y = y;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}

class fostream;

void operator<<(fostream& fos, string text);


// Класс форматированного потока вывода текста.
// Для задания цвета вписываете в строку %, после чего два шестнадцатеричных значения цветов переднего и заднего плана. Пример: "%A0Змейка"
class fostream {
	private: 
	void print(string text) {

		
			
		for (int i = 0; i < text.size(); i++) {
			if (text[i] == '%') {
				int fg = 7, bg = 0; 

				bool ifFG=false, ifBG=false; // Есть ли после % символы, отвечающие за цвета?

				if (hexIntMap.count(toupper(text[i + 1]))) {
					fg = hexIntMap[toupper(text[i + 1])];
					ifFG = true;
				}

				if (hexIntMap.count(toupper(text[i + 2]))) {
					bg = hexIntMap[toupper(text[i + 2])];
					ifBG = true;
				}
				SetColor(fg, bg);
				i += 1 + ifFG + ifBG; // Если цвета не найдены, переход осуществляется правильно
			}
			cout << text[i];
		}
		SetColor();
}
	friend void operator<<(fostream& fos, string text);
};

void operator<<(fostream& fos, string text) {
	fos.print(text);
}

fostream fcout; // Объект форматированного потока fostream по умолчанию


void printRaw(string raw, int x, int _y, int fg = 7, int bg = 0) { // Посимвольно копирует 
	int y = 0;
	SetColor(fg, bg);
	for (int i = 0; i < raw.size(); i++) {
		cout << raw[i];
		if (raw[i] == '\n') {
			y++;
			gotoxy(x, _y + y);
		}
	}
	SetColor();
}
void printRawF(string raw, int x, int _y) { // Посимвольно копирует c форматированием
	int y = 0;
	
	for (int i = 0; i < raw.size(); i++) {
		bool ifFG = false, ifBG = false;
		int fg = 7, bg = 0;
		if(raw[i] == '%'){
			if (hexIntMap.count(toupper(raw[i + 1]))) {
				fg = hexIntMap[toupper(raw[i + 1])];
				ifFG = true;
			}

			if (hexIntMap.count(toupper(raw[i + 2]))) {
				bg = hexIntMap[toupper(raw[i + 2])];
				ifBG = true;
			}
			SetColor(fg, bg);
			i += ifFG + ifBG;
		}
		else {
			cout << raw[i];
			if (raw[i] == '\n') {
				y++;
				gotoxy(x, _y + y);
			}
		}
	}
	SetColor();
}

// улучшенный вариант с возможностью задержки вывода символов, форматирования по центру и чего-то ещё
void _printRaw(string raw, int x, int _y, int textСolor = 7, int backgroundСolor = 0, int centerFormatting = 0, int sleep = 0, int sizeHeight = 100)
{
	int y = 0, countChar = -1, symbolNow = 0;
	if (!(textСolor == 7 && backgroundСolor == 0)) SetColor(textСolor, backgroundСolor);

	for (int i = 0; i < raw.size(); i++) {

		cout << raw[i];
		if (sleep)
			Sleep(sleep);
		if (raw[i] == '\n') {
			if (centerFormatting)
			{
				while (symbolNow < raw.size())
				{
					countChar++;
					symbolNow++;
					if (raw[symbolNow] == '\n')
					{
						centerFormatting = countChar;
						countChar = -1;
						break;
					}
				}
			}
			y++;
			_gotoxy(x, _y + y, centerFormatting, sizeHeight);
			countChar++;
		}
	}
	SetColor();
}
