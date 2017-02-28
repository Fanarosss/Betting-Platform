#include "stdafx.h"
#include "BetAtzis.h"
#include "Main_functions.h"
#include "Users_categories.h"
#include "hierarchy.h"

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
						interface.save();
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
				interface.save();
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
			interface.save();
			cout << "Your balance has changed successfully!" << endl;
			double nbalance = user->get_balance();
			cout << "Your new balance is: " << nbalance << endl;
			//eisagw to upoloipo sto arxeio
		}
		else if ((leitourgia.compare("P") == 0) || (leitourgia.compare("Place") == 0) || (leitourgia.compare("p") == 0) || (leitourgia.compare("place") == 0)) {
			(interface.get_node())->place(&interface);
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
		//print_lastbets();
		cout << "20 last bets" << endl;
		cout << "bet_id|user_id|node_id|stake|result|" << endl;
		for (int i = 0; i < 20; i++) {
			cout << interface.get_bet(i);
		}
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
		cout << "20 last bets" << endl;
		cout << "bet_id|user_id|node_id|stake|result|" << endl;
		for (int i = 0; i < 20; i++) {
			cout << interface.get_bet(i);
		}
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

//saving vector to file//

string Punter::conversion() {
	string sid, sbalance, appuser;
	stringstream converter;
	converter << this->get_id();
	sid = converter.str();
	stringstream converter2;
	converter2 << this->get_balance();
	sbalance = converter.str();
	if (sbalance.empty()) sbalance = "-";
	appuser = sid + "|" + this->get_username() + "|" + this->get_fullname() + "|" + this->get_password() + "|1|" + this->get_Status() + "|" + sbalance + "|" + this->get_free_bets() + "|";
	return appuser;
}

string Trader::conversion() {
	string sid, sbalance, appuser;
	stringstream converter;
	converter << this->get_id();
	stringstream converter2(this->get_balance());
	converter2 >> sbalance;
	appuser = sid + "|" + this->get_username() + "|" + this->get_fullname() + "|" + this->get_password() + "|2| | | |";
	return appuser;
}

string Director::conversion() {
	string sid, sbalance, appuser;
	stringstream converter;
	converter << this->get_id();
	stringstream converter2(this->get_balance());
	converter2 >> sbalance;
	appuser = sid + "|" + this->get_username() + "|" + this->get_fullname() + "|" + this->get_password() + "|3| | | |";
	return appuser;
}

bet::bet(int betid, int userid, string nodeid, double stk, string rslt, User * usr) {
	bet_id = betid;
	user_id = userid;
	node_id = nodeid;
	stake = stk;
	result = rslt;
	user = usr;
}

void Punter::place(BetAtzis* Interface) {
	string operation;
	//User* user = Interface->get_user();
	cout << "Balance: " << get_balance() << endl << "Select option to place the bet. " << endl;
	cin >> operation;
	bool validation = (Interface->get_node())->is_operation_valid(operation);
	if (validation == true) {
		if (operation == "Cancel") {
			return;
		}
		else {
			cout << "betting on node: " << Interface->get_node() << "/" << operation << endl;
			string freebets;
			freebets = get_free_bets();
			vector<string> frbts;
			string temp;
			size_t pos;
			char c = 'a';
			cout << "Your free bets: " << endl;
			while (!freebets.empty()) {
				temp = freebets;
				pos = temp.find("|");
				temp.erase(temp.begin() + pos, temp.end());
				cout << c << ". " << temp << endl;
				frbts.push_back(temp);
				c++;
				freebets = freebets.substr(pos + 1);
			}
			cout << "Enter the amount, or choose the coupon you wish." << endl;
			string sbounty;
			cin >> sbounty;
			if (!(isdigit(sbounty[0]) == 0)) {
				int bounty;
				stringstream converter(sbounty);
				converter >> bounty;
				if (get_balance() == 0) {
					cout << "Your balance is 0. Please fill your wallet from the the main menu. " << endl;
					return;
				}
				if (bounty > get_balance()) {
					cout << "Please enter a smaller bet. Your balance is smaller than the bet you played. " << endl;
					//flag smth
				}
				else {
					set_balance(get_balance() - bounty);
					string node_id;
					//it recursively needs to go back to all nodes and get their id;
					//node_id = (Interface->get_node())->get_id();
					//des to mia re kosta giati exeis ftiaksei mia get_id sto node inline void pou den katalavenw giati litourgei etsi
					Interface->set_bet(node_id, bounty);
				}
			}
			else {
				//aferw ena kouponi
				int coupon = c - '0';
				coupon -= 48; // converting from ascii
				frbts.erase(frbts.begin() + coupon);
				freebets = "";
				for (int i = 0; i < frbts.size(); i++) {
					freebets += frbts[i] + "|";
				}
				set_freebets(freebets);
			}
		}
	}
	return;
}

string bet::conversion() {
	string sid, sstake, sbetid, bet;
	stringstream converter;
	converter << this->get_user_id();
	sid = converter.str();
	stringstream converter2;
	converter2 << this->get_stake();
	sstake = converter.str();
	stringstream converter3;
	converter3 << this->get_bet_id();
	sbetid = converter3.str();
	bet = sbetid + "|" + sid + "|" + this->get_nodeid() + "|" + sstake + "|" + this->get_result() + "|";
	return bet;
}