#pragma once

#include <iostream>
#include <vector>
#include "FormatText.h"
#include "Menu.h"

using namespace std;


struct Slide {
	vector<string> images;
	string title, desc;

};
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
struct SlideShow {
	vector<Slide> slides = { {} };

	SlideShow(vector<Slide> _slides) {
		slides = _slides;
	}

	

	
	int printSlide(int slidePos, Slide slide, int sleepTime = 500) {
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
				gotoxy(40 + 1, 3);
				cout << slide.title;
				printRawF(slides[slidePos].images[i], 40 + 1, 3 + 1);
				if (slidePos > 0) {
					gotoxy(5, 40);
					cout << "<-";
				}
				if (slidePos < slides.size() - 1) {
					gotoxy(75, 40);
					cout << "->";
				}
				i++;
				i %= slides[slidePos].images.size();
				Sleep(sleepTime);
			}
			
		}
	}

	void start() {
		while (true) {
			int direction = printSlide(0, slides[0]);
			break;
		}
	}
};

struct SlideMenu {
	vector<SlideShow> slideshows;
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
					//SetColor(fgactive, bgactive);
					gotoxy(posX, posY + i);
					for (int i = 0; i < findMaxString(menu); i++) cout << " ";
					gotoxy(posX, posY + i);
					cout << menu[i] << endl;
					//SetColor(fgdefault, bgdefault);
				}
				else
				{
					//SetColor(fgdefault, bgdefault);
					gotoxy(posX, posY + i);
					for (int i = 0; i < findMaxString(menu); i++) cout << " ";
					int len = menu[i].length();
					gotoxy(posX, posY + i);
					cout << menu[i] << endl;
					//SetColor(fgactive, bgactive);
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

	void start() {
		printFrame();
		printFrame(20, 79);
		

	}
};