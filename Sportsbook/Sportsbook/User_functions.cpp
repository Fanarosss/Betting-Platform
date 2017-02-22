#include "stdafx.h"
#include "BetAtzis.h"
#include "Main_functions.h"
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
		cout << "(D)Deposit, to change your account balance." << endl;
		string option;
		cin >> option;
		if ((option == "R") || (option == "Rename")) {
			cout << endl << "Please enter your new username:" << endl;
			string nusername;	//new username
			string ousername = user->get_username();	//old username
			string appuser;
			bool flag;
			do {
				cin >> nusername;
				flag = true;
				fstream file("users.csv", std::fstream::in);
				if ((file.is_open())&&(flag==true)) {
					getline(file, appuser); //this takes the line and put it to string appuser
					while (!appuser.empty() && !file.eof()) {
						size_t pos1, pos2;
						pos1 = appuser.find("|");
						appuser = appuser.substr(pos1 + 1);
						pos2 = appuser.find("|");
						appuser = appuser.erase(pos2);
						if ((appuser.compare(nusername) == 0)) { //this takes the line and check if there is a word in there mathcing to the given username
							cout << "This username is already taken!" << endl;
							flag = false;
							file.close();
							break;
						}
						getline(file, appuser);
					}
					file.close();
					if (flag == true) {
						interface.set_new_username(ousername, nusername);
						cout << "Your username has changed successfully!" << endl;
					}
				}
			} while (flag == false);
			//eisagw to kainourgio username sto arxeio
		}
		else if ((option == "P") || (option == "Password")) {
			string name = user->get_username();
			string pw1, pw2;
			cout << endl << "Please enter your new password:" << endl;
			cin >> pw1;
			cout << "One more time:" << endl;
			cin >> pw2;
			if (pw1 == pw2) {
				interface.set_new_password(name, pw1);
				cout << "Your password has changed successfully!" << endl;
				//eisagw ton kainoyrgio kwdiko sto arxeio
			}
			else {
				cout << "Your passwords don't match!" << endl;
			}
		}
		else if ((option == "B") || (option == "Bets")) {

		}
		else if ((option == "D") || (option == "Deposit")) {
			string name = user->get_username();
			double add;
			cout << endl << "Please enter the amount you want to add to your balance:" << endl;
			cin >> add;
			interface.set_new_balance(name, add);
			cout << "Your balance has changed successfully!" << endl;
			double nbalance = user->get_balance();
			cout << "Your new balance is: " << nbalance << endl;
			//eisagw to upoloipo sto arxeio
		}
		else {
			cout << "WRONG INPUT" << endl;
		}
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
		print_lastbets();
		return 1;
	}
	else if ((leitourgia.compare("F") == 0) || (leitourgia.compare("Freebets") == 0) || (leitourgia.compare("f") == 0) || (leitourgia.compare("freebets") == 0)) {
		string user;
		double amount;
		cout << endl << "Enter the name of the user." << endl;
		cin >> user;
		cout << endl << "Enter the amount to be given." << endl;
		cin >> amount;
		//eisagw sto arxeio to freebet;
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

//saving vector to file

string Punter::conversion(int id) {
	string sid, sbalance, appuser;
	stringstream converter(id+1);
	converter >> sid;
	stringstream converter2(this->get_balance());
	converter2 >> sbalance;
	if (sbalance.empty()) sbalance = "-";
	appuser = sid + "|" + this->get_username() + "|" + this->get_fullname() + "|" + this->get_password() + "|1|" + this->get_Status() + "|" + sbalance + "|" + this->get_free_bets() + "|";
	return appuser;
}

string Trader::conversion(int id) {
	string sid, sbalance, appuser;
	stringstream converter(id);
	converter >> sid;
	stringstream converter2(this->get_balance());
	converter2 >> sbalance;
	appuser = sid + "|" + this->get_username() + "|" + this->get_fullname() + "|" + this->get_password() + "|2| | | |";
	return appuser;
}

string Director::conversion(int id) {
	string sid, sbalance, appuser;
	stringstream converter(id);
	converter >> sid;
	stringstream converter2(this->get_balance());
	converter2 >> sbalance;
	appuser = sid + "|" + this->get_username() + "|" + this->get_fullname() + "|" + this->get_password() + "|3| | | |";
	return appuser;
}