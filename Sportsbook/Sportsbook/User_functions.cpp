#include "stdafx.h"
#include "BetAtzis.h"
#include "Users_categories.h"

using namespace std;

bool Guest::Operation(string leitourgia, BetAtzis& interface) {
	if ((leitourgia.compare("H")==0)||(leitourgia.compare("Home")==0) || (leitourgia.compare("h") == 0) || (leitourgia.compare("home") == 0)) {
		interface.return_home();
		return 1;
	}
	else if ((leitourgia.compare("T") == 0) || (leitourgia.compare("Toggle") == 0) || (leitourgia.compare("t") == 0) || (leitourgia.compare("toggle") == 0)) {
		return 1;
	}
	else if ((leitourgia.compare("X") == 0) || (leitourgia.compare("Exit") == 0) || (leitourgia.compare("x") == 0) || (leitourgia.compare("exit") == 0)) {
		cout << "Exiting the program..." << endl;
		return 0; //eksodos apo to sistima
	}
	else {
		cout << "WRONG INPUT" << endl;
		return 1;
	}
}

bool Punter::Operation(string leitourgia, BetAtzis& interface) {
	if ((leitourgia.compare("H") == 0) || (leitourgia.compare("Home") == 0) || (leitourgia.compare("h") == 0) || (leitourgia.compare("home") == 0)) {
		interface.return_home();
		return 1;
	}
	else if ((leitourgia.compare("T") == 0) || (leitourgia.compare("Toggle") == 0) || (leitourgia.compare("t") == 0) || (leitourgia.compare("toggle") == 0)) {
		return 1;
	}
	else if ((leitourgia.compare("A") == 0) || (leitourgia.compare("Account") == 0) || (leitourgia.compare("a") == 0) || (leitourgia.compare("account") == 0)) {
		User* user = interface.get_user();
		cout << endl << "Username: ";
		user->print_username();
		cout << endl << "Balance: ";
		user->print_balance();
		cout << endl << "Freebets: ";
		user->print_freebets();
		cout << endl;
		cout << "(R)Rename, to change your username." << endl;
		cout << "(P)Password, to change your password." << endl;
		cout << "(B)Bets, to see your bets." << endl;
		cout << "(D)Deposit, to change your balance." << endl;
		string option;
		cin >> option;

		return 1;
	}
	else if ((leitourgia.compare("X") == 0) || (leitourgia.compare("Exit") == 0) || (leitourgia.compare("x") == 0) || (leitourgia.compare("exit") == 0)) {
		cout << "Exiting the program..." << endl;
		return 0; //eksodos apo to sistima
	}
	else {
		cout << "WRONG INPUT" << endl;
		return 1;
	}
}
	

bool Trader::Operation(string leitourgia, BetAtzis& interface) {
	if ((leitourgia.compare("H") == 0) || (leitourgia.compare("Home") == 0) || (leitourgia.compare("h") == 0) || (leitourgia.compare("home") == 0)) {
		interface.return_home();
		return 1;
	}
	else if ((leitourgia.compare("T") == 0) || (leitourgia.compare("Toggle") == 0) || (leitourgia.compare("t") == 0) || (leitourgia.compare("toggle") == 0)) {
		return 1;
	}
	else if ((leitourgia.compare("B") == 0) || (leitourgia.compare("Bets") == 0) || leitourgia.compare("b") || (leitourgia.compare("bets") == 0)) {
		return 1;
	}
	else if ((leitourgia.compare("F") == 0) || (leitourgia.compare("Freebets") == 0) || (leitourgia.compare("f") == 0) || (leitourgia.compare("freebets") == 0)) {
		return 1;
	}
	else if ((leitourgia.compare("X") == 0) || (leitourgia.compare("Exit") == 0) || (leitourgia.compare("x") == 0) || (leitourgia.compare("exit") == 0)) {
		cout << "Exiting the program..." << endl;
		return 0; //eksodos apo to sistima
	}
	else {
		cout << "WRONG INPUT" << endl;
		return 1;
	}
}

bool Director::Operation(string leitourgia, BetAtzis& interface) {
	if ((leitourgia.compare("H") == 0) || (leitourgia.compare("Home") == 0) || (leitourgia.compare("h") == 0) || (leitourgia.compare("home") == 0)) {
		interface.return_home();
		return 1;
	}
	else if ((leitourgia.compare("T") == 0) || (leitourgia.compare("Toggle") == 0) || (leitourgia.compare("t") == 0) || (leitourgia.compare("toggle") == 0)) {
		return 1;
	}
	else if ((leitourgia.compare("B") == 0) || (leitourgia.compare("Bets") == 0) || leitourgia.compare("b") || (leitourgia.compare("bets") == 0)) {
		return 1;
	}
	else if ((leitourgia.compare("F") == 0) || (leitourgia.compare("Freebets") == 0) || (leitourgia.compare("f") == 0) || (leitourgia.compare("freebets") == 0)) {
		return 1;
	}
	else if ((leitourgia.compare("S") == 0) || (leitourgia.compare("Save") == 0) || (leitourgia.compare("s") == 0) || (leitourgia.compare("save") == 0)) {
		return 1;
	}
	else if ((leitourgia.compare("X") == 0) || (leitourgia.compare("Exit") == 0) || (leitourgia.compare("x") == 0) || (leitourgia.compare("exit") == 0)) {
		cout << "Exiting the program..." << endl;
		return 0; //eksodos apo to sistima
	}
	else {
		cout << "WRONG INPUT" << endl;
		return 1;
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