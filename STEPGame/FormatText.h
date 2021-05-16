#pragma once

#include <iostream>
#include <string>
#include <map>

using namespace std;

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

class fostream;

void operator<<(fostream& fos, string text);

class fostream {
	private: 
	void print(string text) {

		map<char, int> hexMap = { {'0', 0}, {'1', 1}, {'2', 2}, {'3', 3}, {'4', 4}, {'5', 5}, {'6', 6}, {'7', 7}, {'8', 8}, {'9', 9},
			{'A', 10}, {'B', 11}, {'C', 12}, {'D', 13}, {'E', 14}, {'F', 15} };

		for (int i = 0; i < text.size(); i++) {
			if (text[i] == '%') {
				int fg = 7, bg = 0; 

				bool ifFG=false, ifBG=false; // Есть ли после % символы, отвечающие за цвета?

				if (hexMap.count(toupper(text[i + 1]))) {
					fg = hexMap[toupper(text[i + 1])];
					ifFG = true;
				}

				if (hexMap.count(toupper(text[i + 2]))) {
					bg = hexMap[toupper(text[i + 2])];
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