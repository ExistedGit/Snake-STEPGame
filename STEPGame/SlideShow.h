#pragma once

#include <iostream>
#include <vector>
#include "FormatText.h"

using namespace std;


struct Slide {
	vector<string> images;
	string title, desc;

};

struct SlideShow {
	vector<Slide> slides = { {} };

	SlideShow(vector<Slide> _slides) {
		slides = _slides;
	}

	void printFrame( int width = 80, int height = 25, int posX = 10, int posY = 5) //Рисовка рамки по заданым параметрам
	{
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