#pragma once
#include "Snake.h"
#include <conio.h>
#include <WinUser.h> // нужны же мне в конце концов удобные литералы с номерами кнопок в _гетче()


int findMaxString(vector<string> a) { // Возвращает длину самой длинной строчки в массиве
	int max = a[0].length();
	for (int i = 1; i < a.size(); i++) {
		if (a[i].length() > max) max = a[i].length();
	}
	return max;
}
struct Menu {
	int fgdefault, bgdefault,
		fgactive, bgactive;
	Menu(int fgd = 15, int bgd = 0, int fga = 0, int bga = 15) {
		ShowConsoleCursor(false);
		fgdefault = fgd;
		bgdefault = bgd;
		fgactive = fga;
		bgactive = bga;
	}
	int select_vertical(vector <string> menu, int posX = 1, int posY = 0)
	{
		char c;
		int pos = 0;

		do
		{
			for (int i = 0; i < menu.size(); i++)
			{
				if (i == pos)
				{
					SetColor(fgactive, bgactive);
					gotoxy(posX, posY + i);
					for (int i = 0; i < findMaxString(menu); i++) cout << " ";
					gotoxy(posX, posY + i);
					cout << menu[i] << endl;
					SetColor(fgdefault, bgdefault);
				}
				else
				{
					SetColor(fgdefault, bgdefault);
					gotoxy(posX, posY + i);
					for (int i = 0; i < findMaxString(menu); i++) cout << " ";
					int len = menu[i].length();
					gotoxy(posX, posY + i);
					cout << menu[i] << endl;
					SetColor(fgactive, bgactive);
				}

			}
			c = _getch();
			switch (c)
			{
			case 72:
				if (pos > 0)
					pos--;
				else {
					pos = menu.size() - 1;
				}
				break;
			case 80:
				if (pos < menu.size() - 1)
					pos++;
				else {
					pos = 0;
				}
				break;
			case 13:
				break;
			default:
				break;
			}
		} while (c != 13);
		SetColor(7, 0);
		return pos;
	}
};

struct CenteredMenu : Menu {
	int select_vertical(vector <string> menu, int posX = 1, int posY = 0)
	{
		char c;
		int pos = 0;
		int max = findMaxString(menu);

		do
		{
			for (int i = 0; i < menu.size(); i++)
			{
				if (i == pos)
				{
					SetColor(fgactive, bgactive);
					gotoxy(posX-1, posY + i);
					cout << " ";
					if (max - menu[i].size() == 1) cout << " ";
					for (int i = 0; i < max; i++) cout << " "; // Более-менее красивое выравнивание получается так
					if (max - menu[i].size() != 1) cout << " ";
					gotoxy(posX+ (max - menu[i].size() == 1) + (max - menu[i].size()) / 2, posY + i);
					cout << menu[i];
					
					SetColor(fgdefault, bgdefault);
				}
				else
				{
					SetColor(fgdefault, bgdefault);
					gotoxy(posX-1, posY + i);
					cout << " ";
					if (max - menu[i].size() == 1) cout << " ";
					for (int i = 0; i < max; i++) cout << " ";
					if (max - menu[i].size() != 1) cout << " ";
					gotoxy(posX + (max - menu[i].size() == 1) + (max - menu[i].size()) / 2, posY + i);
					cout << menu[i];
					SetColor(fgactive, bgactive);
				}

			}
			c = _getch();
			switch (c)
			{
			case 72:
				if (pos > 0)
					pos--;
				else {
					pos = menu.size() - 1;
				}
				break;
			case 80:
				if (pos < menu.size() - 1)
					pos++;
				else {
					pos = 0;
				}
				break;
			case 13:
				break;
			default:
				break;
			}
		} while (c != 13);
		SetColor(7, 0);
		return pos;
	}
};



struct SettingsMenu {
	

	map<int, int> startMenu(vector<string> left, vector<vector<string>> right, int posX = 1, int posY = 0, vector<int> positions = {}) {
		if (positions.empty()) {  // Массив, где каждый элемент представляет собой значение поля кнопки слева(соответствуют по индексу)
			for (int i = 0; i < left.size(); i++) positions.push_back(0);
		}

		map<int, int> returnMap; // Возвращаемая map индексов полей к их значениям
		char c; // Ввод

		int posLeft = 0; // Позиция слева
		 
		do{
			
			int max = findMaxString(left);
			int maxRight = 0;
			for (int k = 0; k < right.size(); k++) {
				for (int kj = 0; kj < right[k].size(); kj++) {
					if (right[k][kj].size() > maxRight) maxRight = right[k][kj].size();
				}
			}
			for (int i = 0; i < left.size(); i++)
			{
				if (i == posLeft) {
				

					gotoxy(posX, posY + i);
					SetColor();
					cout << "                                              ";
					gotoxy(posX, posY + i);
					SetColor(0, 15);
					cout << left[i];
					for (int k = 0; k < max - left[i].size(); k++) cout << " "; // Выравнивание слева
					for (int k = 0; k < 5; k++) cout << " ";

					// Если можно пролистнуть влево и/или вправо, ставим стрелочки
					if (positions[i] != 0) cout << "< ";
					else cout << "  ";

					cout << right[i][positions[i]];
					for (int k = 0; k < maxRight - right[i][positions[i]].size(); k++) cout << " ";// Выравнивание справа
					if (positions[i] != right[i].size() - 1) cout << " >";
					else cout << "  ";
					SetColor();
				}
				else {
					gotoxy(posX, posY + i);
					SetColor();
					cout << "                                              ";
					gotoxy(posX, posY + i);
					SetColor(15, 0);
					cout << left[i];
					for (int k = 0; k < max - left[i].size(); k++) cout << " ";
					for (int k = 0; k < 5; k++) cout << " ";

					

					if (positions[i] != 0) cout << "< ";
					else cout << "  ";
					cout << right[i][positions[i]];
					for (int k = 0; k < maxRight - right[i][positions[i]].size(); k++) cout << " ";
					if (positions[i] != right[i].size() - 1) cout << " >";
					else cout << "  ";
					SetColor();
				}
			}
			c = _getch();
			switch (c)
			{
			case KEY_UP:
				if (posLeft > 0)
					posLeft--;
				else {
					posLeft = left.size() - 1;
				}
				break;
			case KEY_DOWN:
				if (posLeft < left.size() - 1)
					posLeft++;
				else {
					posLeft = 0;
				}
				break;
			case KEY_RIGHT:
				if (positions[posLeft] < right[posLeft].size() - 1) positions[posLeft]++;
				break;
			case KEY_LEFT:
				if (positions[posLeft] > 0 ) positions[posLeft]--;
				break;
			case VK_ESCAPE:
				break;
			default:
				break;
			}
		} while (c != VK_ESCAPE);
		for (int i = 0; i < left.size(); i++) {
			returnMap[i] = positions[i];
		}
		return returnMap;
	}
}; 