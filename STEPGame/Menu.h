#pragma once
#include "Snake.h"
#include <conio.h>
#include <WinUser.h>


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

	/*int select_horizontal(vector <string> menu, int posX = 1, int posY = 0) {
		char c;
		int pos = 0;
		int j = 0;
		do
		{
			for (int i = 0; i < menu.size(); i++)
			{

				if (i == pos)
				{
					SetColor(fgactive, bgactive);


					gotoxy(posX + j + 1, posY);
					cout << menu[i];
					SetColor(fgdefault, bgdefault);
					cout << " ";
					j += menu[i].size();
				}
				else
				{
					SetColor(fgdefault, bgdefault);
					gotoxy(posX + j + 1, posY);
					cout << menu[i];
					SetColor(fgactive, bgactive);
					cout << " ";
					j += menu[i].size();
				}

			}
			c = _getch();
			switch (c)
			{
			case 75:
				if (pos > 0)
					pos--;
				else {
					pos = menu.size() - 1;
				}
				break;
			case 77:
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
			j = 0;
		} while (c != 13);
		SetColor(7, 0);
		return pos;
	}*/

	/*void select_settings(map<string, vector<string>> menu, int& line, int& col, int posX = 1, int posY = 0) {
		char c;
		int posLine = 0, posCol = 0;

		do
		{

			for (int i = 0; i < menu.size(); i++)
			{
				if (i == posLine)
				{
					SetColor(fgactive, bgactive);
					gotoxy(posX, posY + i);
					cout << "                      ";
					gotoxy(posX, posY + i);
					cout << menu[i] << endl;
					SetColor(fgdefault, bgdefault);
				}
				else
				{
					SetColor(fgdefault, bgdefault);
					gotoxy(posX, posY + i);
					cout << "                      ";
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
				if (posLine > 0)
					posLine--;
				else {
					posLine = menu.size() - 1;
				}
				break;
			case 80:
				if (posLine < menu.size() - 1)
					posLine;
				else {
					posLine = 0;
				}
				break;
			case 75:
				if (posCol > 0)
					posCol--;
				else {
					posCol = menu.size() - 1;
				}
				break;
			case 77:
				if (posCol < menu.size() - 1)
					posCol;
				else {
					posCol= 0;
				}
				break;
			case 13:
				break;
			default:
				break;
			}
		} while (c != 13);
		SetColor(7, 0);
	}*/
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
					gotoxy(posX, posY + i);
					for (int i = 0; i < max; i++) cout << " ";

					gotoxy(posX + (max - menu[i].size()) / 2, posY + i);
					cout << menu[i] << endl;
					SetColor(fgdefault, bgdefault);
				}
				else
				{
					SetColor(fgdefault, bgdefault);
					gotoxy(posX, posY + i);
					for (int i = 0; i < max; i++) cout << " ";
					gotoxy(posX + (max - menu[i].size()) / 2, posY + i);
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



struct SettingsMenu {
	

	map<int, int> startMenu(vector<string> left, vector<vector<string>> right, int posX = 1, int posY = 0) {
		map<int, int> returnMap;
		char c;

		int posLeft = 0;
		vector<int> posRight = {};
		do{
			for (int i = 0; i < left.size(); i++) posRight.push_back(0);
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
					SetColor(0, 15);
					cout << left[i];
					for (int k = 0; k < max - left[i].size(); k++) cout << " ";
					for (int k = 0; k < 5; k++) cout << " ";


					if (posRight[i] != 0) cout << "< ";
					else cout << "  ";

					cout << right[i][posRight[i]];
					for (int k = 0; k < maxRight - right[i][posRight[i]].size(); k++) cout << " ";
					if (posRight[i] != right[i].size() - 1) cout << " >";
					else cout << "  ";
					SetColor();
				}
				else {
					gotoxy(posX, posY + i);
					SetColor(15, 0);
					cout << left[i];
					for (int k = 0; k < max - left[i].size(); k++) cout << " ";
					for (int k = 0; k < 5; k++) cout << " ";


					if (posRight[i] != 0) cout << "< ";
					else cout << "  ";
					cout << right[i][posRight[i]];
					for (int k = 0; k < maxRight - right[i][posRight[i]].size(); k++) cout << " ";
					if (posRight[i] != right[i].size() - 1) cout << " >";
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
				if (posRight[posLeft] < right[posLeft].size() - 1) posRight[posLeft]++;
				break;
			case KEY_LEFT:
				if (posRight[posLeft] > 0 ) posRight[posLeft]--;
				break;
			case VK_ESCAPE:
				break;
			default:
				break;
			}
			system("cls");
		} while (c != VK_ESCAPE);
		for (int i = 0; i < left.size(); i++) {
			returnMap[i] = posRight[i];
		}
		return returnMap;
	}
}; 