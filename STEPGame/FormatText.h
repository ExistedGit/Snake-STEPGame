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



enum ConsoleColor
{
	Black = 0,
	Blue = 1,
	Green = 2, Cyan = 3, Red = 4, Magenta = 5, Brown = 6, LightGray = 7, DarkGray = 8,
	LightBlue = 9, LightGreen = 10, LightCyan = 11, LightRed = 12, LightMagenta = 13, Yellow = 14, White = 15
};

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
void printCentered(string s, int x, int y, int fg = 7, int bg = 0) {
	SetColor(fg, bg);
	gotoxy(x - s.size() / 2, y);
	cout << s;
	SetColor();
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


void printRaw(string raw, int x, int _y, int fg = 7, int bg = 0, bool centered=false) { // Посимвольно копирует 
	if (centered) {
		vector<string> strings;
		string currentString = "";
		for (int i = 0; raw[i] != '\0'; i++) {
			if (raw[i] == '\n') {
				strings.push_back(currentString);
				currentString = "";
			} else
				currentString.push_back(raw[i]);
		}
		
		for (int i = 0; i < strings.size(); i++) {
			gotoxy(x - (strings[i].size()/2), _y + i);
			cout << strings[i];
		}
	}
	else {
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
}

int formattedLength(string s) {
	int size = 0;
	for (int i = 0; i < s.size(); i++) {
		bool ifFG = false, ifBG = false;

		if (s[i] == '%') {
			if (hexIntMap.count(s[i+1])) {
				
				ifFG = true;
			}

			if (hexIntMap.count(s[i+2])) {
				ifBG = true;
			}
			i += ifFG + ifBG;
			continue;
		}

		size++;
	}
	return size;
}

void printRawF(string raw, int x, int _y, bool centered = false) { // Посимвольно копирует c форматированием
	if (centered) { 
		vector<string> strings; // Массив отдельных строк из raw
		string currentString = ""; // Буфер для отделения
		for (int i = 0; raw[i] != '\0'; i++) {
			if (raw[i] == '\n' || raw[i + 1] == '\0') {
				strings.push_back(currentString); // Если начинается новая строчка, текущую записываем в массив
				currentString = "";
			} else currentString.push_back(raw[i]); // Если нет, продолжаем запись в буфер
		}
	
		for (int i = 0; i < strings.size(); i++) { 
			gotoxy(x - (formattedLength(strings[i]) / 2), _y + i); // Переходим в x - полстроки, то есть выравниваем центрально
			for (int j = 0; j < strings[i].size(); j++) { // Посимвольная обработка строчки из массива, идентично fcout
				bool ifFG = false, ifBG = false;
				int fg = 7, bg = 0;
				if (strings[i][j] == '%') { // обрабатываем изменения цвета
					if (hexIntMap.count(strings[i][j+1])) {
						fg = hexIntMap[strings[i][j+1]];
						ifFG = true;
					}

					if (hexIntMap.count(strings[i][j+2])) {
						bg = hexIntMap[strings[i][j +2]];
						ifBG = true;
					}
					j +=  ifFG + ifBG; // Пропускаем и не печатает изменения цвета

					SetColor(fg, bg); 
				} else cout << strings[i][j]; // Если это обычный символ, выводим
			}
			SetColor();
		}
	}
	else {
		int y = 0; 
		for (int i = 0; i < raw.size(); i++) {
			bool ifFG = false, ifBG = false;
			int fg = 7, bg = 0;
			if (raw[i] == '%') {
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
}

void _printRawF(string raw, int x, int _y, bool centered = false, int color = 7) { // Выводит форматированный текст без форматировочных escape-sequencов
	SetColor(color);
	if (centered) {
		vector<string> strings; // Массив отдельных строк из raw
		string currentString = ""; // Буфер для отделения
		for (int i = 0; raw[i] != '\0'; i++) {
			if (raw[i] == '\n' || raw[i + 1] == '\0') {
				strings.push_back(currentString); // Если начинается новая строчка, текущую записываем в массив
				currentString = "";
			}
			else currentString.push_back(raw[i]); // Если нет, продолжаем запись в буфер
		}

		for (int i = 0; i < strings.size(); i++) {
			gotoxy(x - (formattedLength(strings[i]) / 2), _y + i); // Переходим в x - полстроки, то есть выравниваем центрально
			for (int j = 0; j < strings[i].size(); j++) { // Посимвольная обработка строчки из массива, идентично fcout
				bool ifFG = false, ifBG = false;
				//int fg = 7, bg = 0;
				if (strings[i][j] == '%') { // обрабатываем изменения цвета
					if (hexIntMap.count(strings[i][j + 1])) {
						//fg = hexIntMap[strings[i][j + 1]];
						ifFG = true;
					}

					if (hexIntMap.count(strings[i][j + 2])) {
						//bg = hexIntMap[strings[i][j + 2]];
						ifBG = true;
					}
					j += ifFG + ifBG; // Пропускаем и не печатает изменения цвета

					//SetColor(fg, bg);
				}
				else cout << strings[i][j]; // Если это обычный символ, выводим
			}
			SetColor();
		}
	}
	else {
		SetColor(color);
		int y = 0;
		for (int i = 0; i < raw.size(); i++) {
			bool ifFG = false, ifBG = false;
			//int fg = 7, bg = 0;
			if (raw[i] == '%') {
				if (hexIntMap.count(toupper(raw[i + 1]))) {
					//fg = hexIntMap[toupper(raw[i + 1])];
					ifFG = true;
				}

				if (hexIntMap.count(toupper(raw[i + 2]))) {
					//bg = hexIntMap[toupper(raw[i + 2])];
					ifBG = true;
				}
				//SetColor(fg, bg);
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
}


// улучшенный вариант с возможностью задержки вывода символов, форматирования по центру и чего-то ещё
void _printRaw(string raw, int x, int _y, int textСolor = 7, int backgroundСolor = 0, int centerFormatting = 0, int sleep = 0, int sizeHeight = 100)
{
	int y = 0, countChar = -1, symbolNow = 0;
	if (!(textСolor == 7 && backgroundСolor == 0)) SetColor(textСolor, backgroundСolor);

	for (int i = 0; i < raw.size(); i++) {
		if (_kbhit()) {
			int c = _getch();
			if (c == VK_SPACE) sleep = 0;
		}

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

void printFrame(int width = 159, int height = 79, int posX = 1, int posY = 1, int color = 7) //Рисовка рамки по заданым параметрам
{
	SetColor(color);
	for (int y = posY; y < posY + height; y++)
	{
		for (int x = posX; x < posX + width; x++)
		{
			gotoxy(x, y);
			bool angle = (x == posX && y == posY) || (x == posX && y == posY + height - 1) ||
				(y == posY && x == posX + width - 1) || (y == posY + height - 1 && x == posX + width - 1);
			if (angle)
				cout << "#";
			else if (y == posY || y == posY + height - 1)
				cout << "-";
			else if (x == posX || x == posX + width - 1)
				cout << "|";
		}
	}
	SetColor();
}

/// <summary>
/// Выводит текст с переносом слов при выходе за границу справа
/// </summary>
/// <param name="s">Текст</param>
/// <param name="x">Координата вывода</param>
/// <param name="y">Координата вывода</param>
/// <param name="border">Количество символов в пределах строки</param>
void printTextFrame(string s, int x, int y, int border) { 
	vector<string> words; // Массив слов для удобства переноса
	string currentWord;// Буфер для слов
	for (int i = 0; s[i] != '\0'; i++) {
		if (s[i] == ' ' || s[i+1] == '\0') {
			if (s[i + 1] == '\0') currentWord.push_back(s[i]);
			words.push_back(currentWord);
			currentWord = "";
		}
		else currentWord.push_back(s[i]);
	}
	 // Координата относительно начала текущей строчки. Используется для вычисления корреляции с границей
	int _x = 0;
	gotoxy(x, y);
	for (int i = 0; i < words.size(); i++) {
		
		
		if (_x + words[i].size() + 1 > border) {
			_x = 0;
			gotoxy(x, ++y);
		}
		cout << words[i] << ' ';
		_x += words[i].size() + 1;


	}
}