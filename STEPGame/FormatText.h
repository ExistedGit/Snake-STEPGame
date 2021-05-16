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

class fostream;

void operator<<(fostream& fos, string text);


// Класс форматированного потока вывода текста.
// Для задания цвета вписываете в строку %, после чего два шестнадцатеричных значения цветов переднего и заднего плана. Пример: "%F0Змейка"
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