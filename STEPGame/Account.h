#pragma once
#include <fstream>
#include <iostream>
#include <string>
#include <vector>
using namespace std;

struct Account {
	string name;
	int score = -1;
};

vector<Account> loadAccounts() {
	ifstream fin("./scores.txt");
	vector<Account> acc;
	char name[80];
	int score;
	while (fin.getline(name, 80)) {
		fin >> score;
		fin.ignore();
		acc.push_back(Account {(string)name, score});
	}
	fin.close();
	return acc;
}

void saveAccounts(vector<Account> acc) {
	ofstream fout("./scores.txt");
	for (int i = 0; i < acc.size(); i++) {
		fout << acc[i].name << endl << acc[i].score << endl;
	}
	fout.close();
}