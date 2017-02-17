#include "stdafx.h"
#include "Users_categories.h"

using namespace std;

void Guest::Operation(string leitourgia) {
	if ((leitourgia.compare("H")==0)||(leitourgia.compare("Home")==0)) {
		
	}
	else if ((leitourgia.compare("T") == 0) || (leitourgia.compare("Toggle") == 0)) {

	}
	else if ((leitourgia.compare("X") == 0) || (leitourgia.compare("Exit") == 0)) {
		return ; //eksodos apo to sistima
	}
}

void Punter::Operation(string leitourgia) {
	if ((leitourgia.compare("H") == 0) || (leitourgia.compare("Home") == 0)) {

	}
	else if ((leitourgia.compare("T") == 0) || (leitourgia.compare("Toggle") == 0)) {

	}
	else if ((leitourgia.compare("A") == 0) || (leitourgia.compare("Account") == 0)) {

	}
	else if ((leitourgia.compare("X") == 0) || (leitourgia.compare("Exit") == 0)) {
		return; //eksodos apo to sistima
	}
}

void Trader::Operation(string leitourgia) {
	if ((leitourgia.compare("H") == 0) || (leitourgia.compare("Home") == 0)) {

	}
	else if ((leitourgia.compare("T") == 0) || (leitourgia.compare("Toggle") == 0)) {

	}
	else if ((leitourgia.compare("B") == 0) || (leitourgia.compare("Bets") == 0)) {

	}
	else if ((leitourgia.compare("F") == 0) || (leitourgia.compare("Freebets") == 0)) {

	}
	else if ((leitourgia.compare("X") == 0) || (leitourgia.compare("Exit") == 0)) {
		return; //eksodos apo to sistima
	}
}

void Director::Operation(string leitourgia) {
	if ((leitourgia.compare("H") == 0) || (leitourgia.compare("Home") == 0)) {

	}
	else if ((leitourgia.compare("T") == 0) || (leitourgia.compare("Toggle") == 0)) {

	}
	else if ((leitourgia.compare("B") == 0) || (leitourgia.compare("Bets") == 0)) {

	}
	else if ((leitourgia.compare("F") == 0) || (leitourgia.compare("Freebets") == 0)) {

	}
	else if ((leitourgia.compare("S") == 0) || (leitourgia.compare("Save") == 0)) {

	}
	else if ((leitourgia.compare("X") == 0) || (leitourgia.compare("Exit") == 0)) {
		return; //eksodos apo to sistima
	}
}

void Guest::Print_Operations() {
	cout << "Press the ID of the node you want to enter." << endl;
	cout << "H(Home), to return to home screen." << endl;
	cout << "T(Toggle), to toggle prices." << endl;
	cout << "X(Exit), to exit." << endl;
}

void Punter::Print_Operations() {
	cout << "Press the ID of the node you want to enter." << endl;
	cout << "H(Home), to return to home screen." << endl;
	cout << "T(Toggle), to toggle prices." << endl;
	cout << "A(Account), to change your account settings." << endl;
	cout << "X(Exit), to exit." << endl;
}

void Trader::Print_Operations() {
	cout << "Press the ID of the node you want to enter." << endl;
	cout << "H(Home), to return to home screen." << endl;
	cout << "T(Toggle), to toggle prices." << endl;
	cout << "B(Bets), to see the last 20 bets." << endl;
	cout << "F(Freebets), to give coupon to punter." << endl;
	cout << "X(Exit), to exit." << endl;
}

void Director::Print_Operations() {
	cout << "Press the ID of the node you want to enter." << endl;
	cout << "H(Home), to return to home screen." << endl;
	cout << "T(Toggle), to toggle prices." << endl;
	cout << "B(Bets), to see the last 20 bets." << endl;
	cout << "F(Freebets), to give coupon to punter." << endl;
	cout << "S(Save), to save current state and synchronize system files." << endl;
	cout << "X(Exit), to exit." << endl;
}

void Trader::Bets() {
	fstream myfile("bets.csv" ,std::fstream::app);
	string bet;
	if (myfile.is_open()) {
		getline(myfile, bet);
		while (!myfile.eof() && bet.empty()) {
			//cout << ta 20 teleutaia bets
		}
	}
	else {
		cout << "Error while loading file. ";
	}
}

void Director::Bets() {
	fstream myfile("bets.csv", std::fstream::app);
	string bet;
	if (myfile.is_open()) {
		getline(myfile, bet);
		while (!myfile.eof() && bet.empty()) {
			//cout << ta 20 teleutaia bets
		}
	}
	else {
		cout << "Error while loading file. ";
	}
}