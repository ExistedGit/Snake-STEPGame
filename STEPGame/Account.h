#pragma once
#include <fstream>
#include <iostream>
#include <string>
#include <vector>
#include "Achievements.h"
using namespace std;

struct Account {
	string name = "Default Name";
	int maxScore = 0, games = 0;
	vector<Achievement> ach = {

		{R"Ach(
%A ________ 
 /"       )
(:   \___/
 \___  \
  __/  \\ %c#1%a
 /" \   :)
(_______/ )Ach", "Первый раз", "Вы сыграли свою первую игру. Поздравляем, теперь вы один из нас!", false, 0, 1},

	{R"Ach(
%a  ________ 
 /"       )
(:   \___/
 \___  \
  __/  \\ %F#25%a
 /" \   :)
(_______/ )Ach", "Опять двадцать пять!", "Опытного игрока видно издалека. А вижу я отсюда только вас!", false, 0, 25},
	{R"Ach(
%a  ________ 
 /"       )
(:   \___/
 \___  \
  __/  \\ %E#50%a
 /" \   :)
(_______/ )Ach", "Гуру", "Вы в своём познании настолько преисполнились, что вы как будто бы уже 100 триллионов лет проживаете на триллионах и триллионах таких же планет, понимаете?..", false, 0, 50},
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
 %D@%2~~~~~~~~%D@ )Ach", "Путь в неизвестность", "Эти порталы должны были заменить текущую систему, используя механизм адресации вместо цветов. Технология была доделана лишь наполовину, но менеджеры посчитали демо-версию за готовую."},

{ R"Ach(

 %B/%B'''''''%B\
 |       |
 |%F##%3/-\%F##%B|
 |%F##%3|0|%F##%B|
 |%F##%3\-/%F##%B|
 |       |
 \%B.......%B/)Ach", "По ту сторону", "Зеркальные стены использовались корпорацией до изобретения порталов, но всё ещё являются надёжным методом быстрых перемещений(к более функциональным устройствам)." } };
};
Account mainAcc;

void loadAccount() {
	ifstream fin(dir +L"\\accInfo.txt");
	
	char name[80];
	
	if (fin.getline(name, 80)) {
		int maxScore, games;
		fin >> maxScore;
		mainAcc.maxScore = maxScore;
		fin >> games;
		mainAcc.games = games;
	}
	mainAcc.name = name;

	fin.close();
	fin.open(dir + L"\\achInfo.txt");
	vector<bool> achStates = {};
	bool achState;
	for (int i = 0; fin >> achState; i++) {
		achStates.push_back(achState);
	};
	for (int i = 0; i < achStates.size(); i++) {
		mainAcc.ach[i].completed = achStates[i];
	}

	for (int i = ACH_100PTS; i <= ACH_2000PTS; i++) {
		mainAcc.ach[i].progress = mainAcc.maxScore;
		if (mainAcc.ach[i].progress >= mainAcc.ach[i].maxProgress) {
			mainAcc.ach[i].completed = true;
			mainAcc.ach[i].progress = mainAcc.ach[i].maxProgress;
		}
	}

	for (int i = ACH_FIRSTGAME; i <= ACH_50GAMES; i++) {
		mainAcc.ach[i].progress = mainAcc.games;
		if (mainAcc.ach[i].progress >= mainAcc.ach[i].maxProgress) {
			mainAcc.ach[i].completed = true;
			mainAcc.ach[i].progress = mainAcc.ach[i].maxProgress;
		}
	}
	fin.close();

}

void saveAccount() {
	
	ofstream fout;
	fout.open(dir + L"\\accInfo.txt");
	if (fout.is_open()) {
		fout << mainAcc.name << endl << mainAcc.maxScore << endl << mainAcc.games;
		fout.close();
	}
	fout.open(dir + L"\\achInfo.txt");
	if (fout.is_open()) {
		for (int i = 0; i < mainAcc.ach.size(); i++) {
			fout << mainAcc.ach[i].completed << endl;
		}
		fout.close();
	}

}