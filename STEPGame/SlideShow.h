#pragma once

#include <iostream>
#include <vector>
#include "FormatText.h"
#include "Menu.h"

using namespace std;


struct Slide {
	vector<string> images = {};
	string title = "Имя шаблона", desc = "Описание шаблона";
	int print(int slidePos, int x, int y, int sleepTime = 500) {
		int i = 0;
		while (true) {
			if (_kbhit()) {
				char c = _getch();
				if (c == VK_ESCAPE ||
					c == LEFT ||
					c == RIGHT) return c;
			}
			else {
				ShowConsoleCursor(false);
				//printFrame(, 40, 40, 3);
				gotoxy(x, y);
				cout << title;
				printRawF(images[i], x, y + 1);
				i++;
				i %= images.size();
				Sleep(sleepTime);
			}

		}
	}
};


//
//struct SlideMenu {
//	
//	int select_vertical(vector<SlideShow> menu , int posX = 1, int posY = 0)
//	{
//		//char c;
//		//int pos = 0;
//
//		//vector<string> menuStrings;
//		//for (int i = 0; i < menu.size(); i++) {
//		//	menuStrings.push_back(menu[i].title);
//		//}
//
//		//do
//		//{
//		//	for (int i = 0; i < menu.size(); i++)
//		//	{
//		//		if (i == pos)
//		//		{
//		//			//SetColor(fgactive, bgactive);
//		//			gotoxy(posX, posY + i);
//		//			for (int i = 0; i < findMaxString(menu); i++) cout << " ";
//		//			gotoxy(posX, posY + i);
//		//			cout << menu[i] << endl;
//		//			//SetColor(fgdefault, bgdefault);
//		//		}
//		//		else
//		//		{
//		//			//SetColor(fgdefault, bgdefault);
//		//			gotoxy(posX, posY + i);
//		//			for (int i = 0; i < findMaxString(menu); i++) cout << " ";
//		//			int len = menu[i].length();
//		//			gotoxy(posX, posY + i);
//		//			cout << menu[i] << endl;
//		//			//SetColor(fgactive, bgactive);
//		//		}
//
//		//	}
//		//	c = _getch();
//		//	switch (c)
//		//	{
//		//	case 72:
//		//		if (pos > 0)
//		//			pos--;
//		//		else {
//		//			pos = menu.size() - 1;
//		//		}
//		//		break;
//		//	case 80:
//		//		if (pos < menu.size() - 1)
//		//			pos++;
//		//		else {
//		//			pos = 0;
//		//		}
//		//		break;
//		//	case 13:
//		//		break;
//		//	default:
//		//		break;
//		//	}
//		//} while (c != 13);
//		//SetColor(7, 0);
//		return pos;
//	}
//
//	void start() {
//		printFrame();
//		printFrame(20, 79);
//		
//
//	}
//};