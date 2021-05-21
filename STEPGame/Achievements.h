#pragma once
#include <iostream>
#include <string>
#include <vector>
#include "FormatText.h"
using namespace std;


struct Achievement {
	string image = R"Ach(
  ________ 
 /"       )
(:   \___/
 \___  \
  __/  \\
 /" \   :)
(_______/ )Ach";
	string title = "Достижение", desc = "Описание достижения";
	bool completed = false;
	int progress = -1; // -1 прогресс быть не может, поэтому в таком случае он и не выводится
	int maxProgress = -1; // тоже

	//Achievement() {
	//	if (progress >= maxProgress) completed = true;
	//}
};



struct AchievementMenu {
	
	//void displayScrollBar() {
	//	
	//}

	void start(vector<Achievement> ach) {
		int completedAch = 0;
		for (auto i : ach) {
			completedAch += i.completed;
		}
		int scrollPos = 0;
		int oldScrollPos = -1;
		while (true) {
			
			ShowConsoleCursor(false);
			if (scrollPos != oldScrollPos) {
				for (int i = scrollPos; i < scrollPos + 5 && i < ach.size(); i++) {

					printFrame(60, 10, 30 + 30, 2 + (i - scrollPos) * 11, ach[i].completed ? Green : Red);
					gotoxy(30 + 30, 2 + (i - scrollPos) * 11);
					cout << i+1;
					if (ach[i].completed) printRawF(ach[i].image, 32 + 30, 2 + (i - scrollPos) * 11);
					else _printRawF(ach[i].image, 32 + 30, 2 + (i - scrollPos) * 11);

					

					printCentered(ach[i].title, 60 + 30, 2 + (i - scrollPos) * 11, ach[i].completed ? LightCyan : LightGray);
					if (ach[i].progress != -1) {
						string progString = to_string(ach[i].progress); 
						progString.append("/");
						progString.append(to_string(ach[i].maxProgress));
						printCentered(progString, 60 + 30, 10 + 1 + (i - scrollPos) * 11, (ach[i].progress == ach[i].maxProgress ? LightGreen : 7));
					}
					// gotoxy(45, 2 + 2 + (i*11));
					SetColor(ach[i].completed ? Yellow : 7);
					printTextFrame(ach[i].desc, 45 + 30, 2 + 2 + (i - scrollPos) * 11, 44);
					SetColor();
				}
			}
			gotoxy(45 + 30 + 60, 30);
			cout << "Достижения " << completedAch << "/" << ach.size();
			
			if (scrollPos > 0) {
				gotoxy(45 + 30 + 50, 2);
				cout << "/\\";
			}
			if (scrollPos < ach.size() - 1) {
				gotoxy(45 + 30 + 50, 55);
				cout << "\\/";
			}

			oldScrollPos = scrollPos;
			char c = _getch();
			switch (c) {
			case KEY_UP:
				if (scrollPos > 0) {
					scrollPos--;
					system("cls");
				}
				break;
			case KEY_DOWN:
				
				if (scrollPos < ach.size() - 1) {
					scrollPos++;
					system("cls");
				}
				break;
			case VK_ESCAPE:
				return;
				break;
			}
			
		}
		
	}
};

enum achievementID {
	ACH_FIRSTGAME,
	ACH_100PTS,
	ACH_500PTS,
	ACH_2000PTS,
	ACH_WALLDEATH,
	ACH_PORTALUSE,
	ACH_ENTPORTALUSE
};

// Массив всех возможных достижений
vector<Achievement> ach = { {R"Ach(
%a  ________ 
 /"       )
(:   \___/
 \___  \
  __/  \\ #1
 /" \   :)
(_______/ )Ach", "Первый раз", "Вы сыграли свою первую игру. Поздравляем, теперь вы один из нас!"},

{R"Ach(

 %6  _____
 (|     |)
  | %C0100%6 |
   \   /
    \ /
    _|_)Ach", "Змейка-новичок", "Вы получили 100 очков. Круто.", false, 0, 100},

{R"Ach(

 %6  _____
 (|     |)
  | %F0500%6 |
   \   /
    \ /
    _|_)Ach", "На пути к славе", "Вы получили 500 очков. Чего-то да вы стоите!", false, 0, 500},
{R"Ach(

 %6  ______
 /|      |\
 \| %e03000%6 |/
   \    /
    \  /
    _||_)Ach", "Змеиный Олимп", "НЕВЕРОЯТНО! Вы получили 3000 очков.", false, 0, 3000},

{R"Ach(

 
 
    %C0GAME 
    OVER 
 
             )Ach", "Несъедобно", "Впечатались в стену? Не беда, начните снова."},

{R"Ach(

 %300 %5+%2~~~\
       :
       :
       :
       :
 %600%2~~~~~/)Ach", "Хвала науке!", "Вы воспользовались передовой разработкой SNAKE Tech - порталом."},

{R"Ach(

   %2/~~%D@%2
   :  :
   \~~/
 %5+%2
 :		
 %D@%2~~~~~~~~%D@ )Ach", "Путь в неизвестность", "Эти порталы должны были заменить текущую систему, используя механизм адресации вместо цветов. Технология была доделана лишь наполовину, но менеджеры посчитали демо-версию за готовую."} };

