#pragma once
#pragma comment(lib, "winmm.lib")
#include "Snake.h"
#include "Account.h"
#include <thread>






enum Difficulties {
	HARD = 1,
	MIDDLE,
	EASY
};
using namespace std;



void playBiteSound() {
	PlaySound(TEXT("./Resources/bite.wav"), NULL, SND_ASYNC);
	//mciSendString(TEXT("./Resources/bite.wav"), NULL, 0, NULL);
}

struct Map {
	// ������ �� ������ �����
	int width = 20, height= 20;
	int score = 0;
	int difficulty=HARD;

	// ������� �������� � ������������ �������. ��, � ��� ������������ ����� COORD ��� ��������� ����, �� �������� ����������
	vector<vector<int>> food; 
	vector<vector<int>> walls;
	
	Account acc;

	bool isRunning = false;	
	
	Snake s = Snake(width/2, height/2);
	
	

	// ������������ ����� � ������ ���
	void Draw(string map = "./Maps/Default.snakemap") {
		ifstream fin(map);
		char c;
		char buff[80];
		int l = 0;
		vector<int> snakePos = {0, 0};
		while (fin.getline(buff, 80)) { // ����������� ����� � ������ �������
			for (int i = 0; buff[i] != '\0'; i++) {
				if (buff[i] == '#') walls.push_back({ i,l });
				else if (buff[i] == '+') {
					snakePos = { i,l };
				}
				
				
				width = strlen(buff);
			}
			l++;
		}
		height = l;
		
		for (int i = 0; i < walls.size(); i++) {
			gotoxy(walls[i][0], walls[i][1]);
			cout << "#";
		}
		spawnSnake(snakePos[0], snakePos[1]);
		
		isRunning = true;
	}
	void snakeCheck() { // ���������, �� ����������� �� ������ � ������������
		for (int i = 1; i < s.bodyMatrix.size(); i++) {
			if (s.bodyMatrix[0][0] == s.bodyMatrix[i][0] && s.bodyMatrix[0][1] == s.bodyMatrix[i][1]) isRunning = false;

			
		}

		for (int j = 0; j < walls.size(); j++) {
			if (s.bodyMatrix[0][0] == walls[j][0] && s.bodyMatrix[0][1] == walls[j][1]) isRunning = false;
		}
	}

	void foodCheck() { // ���������, ���� �� ������� ���
		for (int i = 0; i < food.size(); i++) {
			if (s.bodyMatrix[0][0] == food[i][0] && s.bodyMatrix[0][1] == food[i][1]) {
				food.pop_back();
				s.growTail();
				score += 10;
				displayLength();
				displayScore();

				if (score > acc.score) acc.score = score;

				displayAcc();


				playBiteSound();

			}
		}
		for (int i = 1; i < s.bodyMatrix.size(); i++) {
			for (int j = 0; j < food.size(); j++) {
				if (s.bodyMatrix[i][0] == food[j][0] && s.bodyMatrix[i][1] == food[j][1]) {
					food.pop_back();
				}
			}
		}
	}
	

	// ������ � ������ ����� ����� ������
	void spawnSnake(int posX, int posY) {
		s = Snake(posX, posY);
	}

	void displayLength() {
		gotoxy(width+3, height/2);
		SetColor(15);
		cout << "�����: "<< s.length;
		SetColor();
	}

	void displayScore() {
		gotoxy(width + 3, height / 2 - 2);
		SetColor(15);
		cout << "����: " << score;
		SetColor();
	}

	void displayAcc() {
		gotoxy(width + 3, height / 2 - 4);
		cout << acc.name;
		gotoxy(width + 3, height / 2 - 3);
		cout << "������: " << acc.score;
	}
	

	void generateFood() {
		int posX = rand() % (width - 2) + 2;
		int posY = rand()%(height-3)+2;
		
		food.push_back({posX, posY});
		gotoxy(food[food.size()-1][0], food[food.size() - 1][1]);
		SetColor(LightRed);
		cout << "@";
		SetColor();
	}

	void Update() {
		thread stopSound;
		displayLength();
		displayScore();
		displayAcc();
		while (isRunning) {
			ShowConsoleCursor(false);
			
			if (food.empty()) {
				generateFood();
			};
			
			if (_kbhit()) {
				int c; // ����������, � ������� ������������ �����������
				c = _getch(); // ���� ������ ���� ������, ������� �������� ������ �� ��������
				if (c == VK_ESCAPE) isRunning = false; // ���� ����� Escape, ���� ���������������
				s.changeDirection(c);
				snakeCheck();
				foodCheck();
				continue;
			}
			Sleep(150 * difficulty);
			s.Update();
			s.drawSnake();
			
			gotoxy(0, height);
			foodCheck();
			snakeCheck();
			
			

			gotoxy(0, height+1);
		}
		gotoxy(width / 2 - 4, height / 2);
		SetColor(Red);
		cout << "GAME OVER";
		PlaySound(TEXT("./Resources/gameOver.wav"), NULL, SND_ASYNC);
		SetColor();
		gotoxy(0, height+5);
		system("pause");
		system("cls");
		PlaySound(NULL, NULL, SND_ASYNC);
	}
};


