#include "stdafx.h"
#include "Users_categories.h"

using namespace std;

void Guest::Operation(char leitourgia) {
	if (leitourgia == 'c') {

	}
	else if (leitourgia == 't') {

	}
	else if (leitourgia == 'x') {
		return ; //eksodos apo to sistima
	}
}

void Punter::Operation(char leitourgia) {
	if (leitourgia == 'c') {

	}
	else if (leitourgia == 't') {

	}
	else if (leitourgia == 'a') {

	}
	else if (leitourgia == 'x') {
		return; //eksodos apo to sistima
	}
}

void Trader::Operation(char leitourgia) {
	if (leitourgia == 'c') {

	}
	else if (leitourgia == 't') {

	}
	else if (leitourgia == 'b') {

	}
	else if (leitourgia == 'f') {

	}
	else if (leitourgia == 'x') {
		return; //eksodos apo to sistima
	}
}

void Director::Operation(char leitourgia) {
	if (leitourgia == 'c') {

	}
	else if (leitourgia == 't') {

	}
	else if (leitourgia == 's') {

	}
	else if (leitourgia == 'x') {
		return; //eksodos apo to sistima
	}
}

void Trader::Bets() {
	fstream myfile("user_logs.txt");
	if (myfile.is_open()) {
		while (!myfile.eof()) {
			//cout << ta 20 teleutaia bets
		}
	}
	else {
		cout << "Error while loading file. ";
	}
}

void Director::Bets() {
	fstream myfile("user_logs.txt");
	if (myfile.is_open()) {
		while (!myfile.eof()) {
			//cout << ta 20 teleutaia bets
		}
	}
	else {
		cout << "Error while loading file. ";
	}
}