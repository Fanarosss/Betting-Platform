#include "stdafx.h"
#include "BetAtzis.h"
#include "Main_functions.h"
#include "Users_categories.h"
#include "hierarchy.h"

using namespace std;

bool Guest::Operation(string leitourgia, BetAtzis& interface) {
	if ((leitourgia.compare("H")==0)||(leitourgia.compare("Home")==0) || (leitourgia.compare("h") == 0) || (leitourgia.compare("home") == 0)) {
		interface.return_home();
		interface.write_log("Return Home", "Guest", " ", "SUCCESS");
		return 1;
	}
	else if ((leitourgia.compare("T") == 0) || (leitourgia.compare("Toggle") == 0) || (leitourgia.compare("t") == 0) || (leitourgia.compare("toggle") == 0)) {
		interface.write_log("Toggle", "Guest", " ", "SUCCESS");
		return 1;
	}
	else if ((leitourgia.compare("X") == 0) || (leitourgia.compare("Exit") == 0) || (leitourgia.compare("x") == 0) || (leitourgia.compare("exit") == 0)) {
		interface.write_log("Exit", "Guest", "Exiting the program ", "SUCCESS");
		cout << "Exiting the program..." << endl;
		return 0; //eksodos apo to sistima
	}
	else {
		interface.write_log("Operation", "Guest", "WRONG INPUT", "ERROR");
		cout << "WRONG INPUT" << endl;
		return 1;
	}
}


bool Punter::Operation(string leitourgia, BetAtzis& interface) {
	if ((leitourgia.compare("H") == 0) || (leitourgia.compare("Home") == 0) || (leitourgia.compare("h") == 0) || (leitourgia.compare("home") == 0)) {
		interface.return_home();
		interface.write_log("Return Home", get_username(), " ", "SUCCESS");
		return 1;
	}
	else if ((leitourgia.compare("T") == 0) || (leitourgia.compare("Toggle") == 0) || (leitourgia.compare("t") == 0) || (leitourgia.compare("toggle") == 0)) {
		Node* node = interface.get_home();
		for (int a = 1; a <= node->get_vector_size(); a++) {
			node = node->get_next(a);
			for (int b = 1; b <= node->get_vector_size(); b++) {
				node = node->get_next(b);
				for (int c = 1; c <= node->get_vector_size(); c++) {
					node = node->get_next(c);
					for (int d = 1; d <= node->get_vector_size(); d++) {
						node = node->get_next(d);
						for (int e = 1; e <= node->get_vector_size(); e++) {
							node = node->get_next(e);
							string old_profit;
							node->get_profit(old_profit);
							if (interface.get_type_of_profits() == 0) {			//an einai klasma metatrepw se dekadiko
								size_t klasma = old_profit.find("/");
								string sdividend, sdivisor, snew_profit;
								sdivisor = old_profit.substr(klasma + 1);
								sdividend = old_profit.substr(0, klasma);
								double dividend, divisor, new_profit;
								dividend = atof(sdividend.c_str());
								divisor = atof(sdivisor.c_str());		//den eimai sigouros oti douleuei se c++98
								new_profit = (dividend / divisor) + 1;		
								new_profit = round(new_profit * 100) / 100;
								stringstream convert;
								convert << new_profit;
								snew_profit = convert.str();
								node->set_profit(snew_profit);
							}													//alliws apo decadiko se klasma
							else {
								double decimal = atof(old_profit.c_str());
								decimal--;
								decimal = decimal * 100;
								double divisor = 100;
								bool there_is_a_divisor = false;
								do {
									there_is_a_divisor = false;
									for (int i = 2; i <= decimal; i++) {
										if ((fmod(decimal,i)==0)&&(fmod(divisor,i)==0)) {
											decimal = decimal / i;
											divisor = divisor / i;
											there_is_a_divisor = true;
											break;
										}
									}
								} while (there_is_a_divisor == true);
								string sdividend, sdivisor, snew_profit;
								stringstream con1, con2;
								con1 << decimal;
								sdividend = con1.str();
								con2 << divisor;
								sdivisor = con2.str();
								snew_profit = sdividend + "/" + sdivisor;
								node->set_profit(snew_profit);
							}
							node = node->get_back();
						}
						node = node->get_back();
					}
					node = node->get_back();
				}
				node = node->get_back();
			}
			node = node->get_back();
		}
		if (interface.get_type_of_profits() == 0) {
			cout << "Conversion from fraction to decimal was successful." << endl;
			interface.write_log("Toggle", get_username(), "Dekadika ", "SUCCESS");
			interface.set_type_of_profits("Dekadika");
		}
		else {
			cout << "Conversion from decimal to fraction was successful." << endl;
			interface.write_log("Toggle", get_username(), "Klasmatika ", "SUCCESS");
			interface.set_type_of_profits("Klasmatika");
		}
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
		interface.write_log("Account", get_username(), " ", "SUCCESS");
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
						interface.write_log("Rename", get_username(), " ", "SUCCESS");
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
				interface.write_log("Password", get_username(), "Changed ", "SUCCESS");
				//eisagw ton kainoyrgio kwdiko sto arxeio
			}
			else {
				interface.write_log("Password", get_username(), "no match ", "FAILED");
				cout << "Your passwords don't match!" << endl;
			}
		}
		else if ((option == "B") || (option == "Bets")) {
			cout << "BETTING HISTORY:" << endl;
			cout << "node_id|stake|result|" << endl;
			interface.print_user_bets();
			interface.write_log("Bets", get_username(), "Betting history ", "SUCCESS");
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
			interface.write_log("Deposit", get_username(), "Changed ", "SUCCESS");
			//eisagw to upoloipo sto arxeio
		}
		else {
			interface.write_log("Deposit", get_username(), "WRONG INPUT ", "ERROR");
			cout << "WRONG INPUT" << endl;
		}
		return 1;
	}
	else if ((leitourgia.compare("P") == 0) || (leitourgia.compare("Place") == 0) || (leitourgia.compare("p") == 0) || (leitourgia.compare("place") == 0)) {
		(interface.get_node())->place(&interface);
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
		Node* node = interface.get_home();
		for (int a = 1; a <= node->get_vector_size(); a++) {
			node = node->get_next(a);
			for (int b = 1; b <= node->get_vector_size(); b++) {
				node = node->get_next(b);
				for (int c = 1; c <= node->get_vector_size(); c++) {
					node = node->get_next(c);
					for (int d = 1; d <= node->get_vector_size(); d++) {
						node = node->get_next(d);
						for (int e = 1; e <= node->get_vector_size(); e++) {
							node = node->get_next(e);
							string old_profit;
							node->get_profit(old_profit);
							if (interface.get_type_of_profits() == 0) {			//an einai klasma metatrepw se dekadiko
								size_t klasma = old_profit.find("/");
								string sdividend, sdivisor, snew_profit;
								sdivisor = old_profit.substr(klasma + 1);
								sdividend = old_profit.substr(0, klasma);
								double dividend, divisor, new_profit;
								dividend = atof(sdividend.c_str());
								divisor = atof(sdivisor.c_str());		//den eimai sigouros oti douleuei se c++98
								new_profit = (dividend / divisor) + 1;
								new_profit = round(new_profit * 100) / 100;
								stringstream convert;
								convert << new_profit;
								snew_profit = convert.str();
								node->set_profit(snew_profit);
							}													//alliws apo decadiko se klasma
							else {
								double decimal = atof(old_profit.c_str());
								decimal--;
								decimal = decimal * 100;
								double divisor = 100;
								bool there_is_a_divisor = false;
								do {
									there_is_a_divisor = false;
									for (int i = 2; i <= decimal; i++) {
										if ((fmod(decimal, i) == 0) && (fmod(divisor, i) == 0)) {
											decimal = decimal / i;
											divisor = divisor / i;
											there_is_a_divisor = true;
											break;
										}
									}
								} while (there_is_a_divisor == true);
								string sdividend, sdivisor, snew_profit;
								stringstream con1, con2;
								con1 << decimal;
								sdividend = con1.str();
								con2 << divisor;
								sdivisor = con2.str();
								snew_profit = sdividend + "/" + sdivisor;
								node->set_profit(snew_profit);
							}
							node = node->get_back();
						}
						node = node->get_back();
					}
					node = node->get_back();
				}
				node = node->get_back();
			}
			node = node->get_back();
		}
		if (interface.get_type_of_profits() == 0) {
			cout << "Conversion from fraction to decimal was successful." << endl;
			interface.set_type_of_profits("Dekadika");
		}
		else {
			cout << "Conversion from decimal to fraction was successful." << endl;
			interface.set_type_of_profits("Klasmatika");
		}
		return 1;
	}
	else if ((leitourgia.compare("B") == 0) || (leitourgia.compare("Bets") == 0) || (leitourgia.compare("b") == 0) || (leitourgia.compare("bets") == 0)) {
		//print_lastbets();
		cout << "20 last bets" << endl;
		cout << "bet_id|user_id|node_id|stake|result|" << endl;
		for (int i = 0; i < 20; i++) {
			cout << interface.get_bet(i);
		}
		return 1;
	}
	else if ((leitourgia.compare("F") == 0) || (leitourgia.compare("Freebets") == 0) || (leitourgia.compare("f") == 0) || (leitourgia.compare("freebets") == 0)) {
		int user;
		string amount;
		interface.print_users();
		cout << endl << "Enter the name of the user you want to give a freebet." << endl;
		cin >> user;
		User * userptr = interface.get_userptr(user);
		cout << endl << "Enter the amount to be given." << endl;
		cin >> amount;
		userptr->set_freebets(amount);
		//eisagw sto arxeio to freebet;
		interface.save();
		return 1;
	}
	else if ((leitourgia.compare("V") == 0) || (leitourgia.compare("Void") == 0) || (leitourgia.compare("v") == 0) || (leitourgia.compare("void") == 0)) {
		if (interface.get_current_level() == 4) {
			cout << "Select the option you want to cancel:" << endl;
			int option;
			cin >> option;
			Node* node = interface.get_node();
			if (node->get_vector_size() >= option) {
				node = node->get_next(option);
				if (node->get_voided() == 0) {
					node->set_voided();
					cout << "Option No" << option << " was cancelled succesfully." << endl;	//mhpws 8elei apo8hkeush sto arxeio hierarchy.dat;;
					string full_id = node->get_full_id();
					interface.voided(full_id);
					interface.save();
				}
				else {
					cout << "Option No" << option << " is already voided." << endl;
				}
			}
			else {
				cout << "The option you chose does not exist." << endl;
				return 1;
			}
			return 1;
		}
		else {
			cout << "Error. In order to cancel a selection you should be in a market." << endl;
			return 0;
		}
	}
	else if ((leitourgia.compare("S") == 0) || (leitourgia.compare("Settle") == 0) || (leitourgia.compare("s") == 0) || (leitourgia.compare("settle") == 0)) {
		if (interface.get_current_level() == 4) {
			cout << "Choose the winning option:" << endl;
			int option;
			cin >> option;
			Node* node = interface.get_node();
			if (node->get_vector_size() >= option) {
				node = node->get_next(option);
				if (node->get_voided() == 1) {
					cout << "A voided option cannot win!" << endl;
					return 1;
				}
				string full_id = node->get_full_id();
				interface.settle(full_id, option);		//8etw W kai L stis epiloges
				string sprofit;
				node->get_profit(sprofit);
				double profit;
				if (interface.get_type_of_profits() == 0) {
					size_t klasma = sprofit.find("/");
					string sdividend, sdivisor, snew_profit;
					sdivisor = sprofit.substr(klasma + 1);
					sdividend = sprofit.substr(0, klasma);
					double dividend, divisor, new_profit;
					dividend = atof(sdividend.c_str());
					divisor = atof(sdivisor.c_str());
					new_profit = (dividend / divisor);
					profit = new_profit;
				}
				else {
					stringstream converter(sprofit);
					converter >> profit;
				}
				interface.pay(full_id, profit);				//plhrwnw tous nikhtes
				interface.save();
				cout << "Option No" << option << " was settled succesfully." << endl;
			}
			else {
				cout << "The option you chose does not exist." << endl;
				return 1;
			}
			return 1;
		}
		else {
			cout << "Error. In order to cancel a selection you should be in a market." << endl;
			return 0;
		}
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
		Node* node = interface.get_home();
		for (int a = 1; a <= node->get_vector_size(); a++) {
			node = node->get_next(a);
			for (int b = 1; b <= node->get_vector_size(); b++) {
				node = node->get_next(b);
				for (int c = 1; c <= node->get_vector_size(); c++) {
					node = node->get_next(c);
					for (int d = 1; d <= node->get_vector_size(); d++) {
						node = node->get_next(d);
						for (int e = 1; e <= node->get_vector_size(); e++) {
							node = node->get_next(e);
							string old_profit;
							node->get_profit(old_profit);
							if (interface.get_type_of_profits() == 0) {			//an einai klasma metatrepw se dekadiko
								size_t klasma = old_profit.find("/");
								string sdividend, sdivisor, snew_profit;
								sdivisor = old_profit.substr(klasma + 1);
								sdividend = old_profit.substr(0, klasma);
								double dividend, divisor, new_profit;
								dividend = atof(sdividend.c_str());
								divisor = atof(sdivisor.c_str());		//den eimai sigouros oti douleuei se c++98
								new_profit = (dividend / divisor) + 1;
								new_profit = round(new_profit * 100) / 100;
								stringstream convert;
								convert << new_profit;
								snew_profit = convert.str();
								node->set_profit(snew_profit);
							}													//alliws apo decadiko se klasma
							else {
								double decimal = atof(old_profit.c_str());
								decimal--;
								decimal = decimal * 100;
								double divisor = 100;
								bool there_is_a_divisor = false;
								do {
									there_is_a_divisor = false;
									for (int i = 2; i <= decimal; i++) {
										if ((fmod(decimal, i) == 0) && (fmod(divisor, i) == 0)) {
											decimal = decimal / i;
											divisor = divisor / i;
											there_is_a_divisor = true;
											break;
										}
									}
								} while (there_is_a_divisor == true);
								string sdividend, sdivisor, snew_profit;
								stringstream con1, con2;
								con1 << decimal;
								sdividend = con1.str();
								con2 << divisor;
								sdivisor = con2.str();
								snew_profit = sdividend + "/" + sdivisor;
								node->set_profit(snew_profit);
							}
							node = node->get_back();
						}
						node = node->get_back();
					}
					node = node->get_back();
				}
				node = node->get_back();
			}
			node = node->get_back();
		}
		if (interface.get_type_of_profits() == 0) {
			cout << "Conversion from fraction to decimal was successful." << endl;
			interface.set_type_of_profits("Dekadika");
		}
		else {
			cout << "Conversion from decimal to fraction was successful." << endl;
			interface.set_type_of_profits("Klasmatika");
		}
		return 1;
	}
	else if ((leitourgia.compare("B") == 0) || (leitourgia.compare("Bets") == 0) || (leitourgia.compare("b") == 0) || (leitourgia.compare("bets") == 0)) {
		cout << "20 last bets" << endl;
		cout << "bet_id|user_id|node_id|stake|result|" << endl;
		for (int i = 0; i < 20; i++) {
			cout << interface.get_bet(i);
		}
		return 1;
	}
	else if ((leitourgia.compare("F") == 0) || (leitourgia.compare("Freebets") == 0) || (leitourgia.compare("f") == 0) || (leitourgia.compare("freebets") == 0)) {
		int user;
		string amount;
		interface.print_users();
		cout << endl << "Enter the name of the user you want to give a freebet." << endl;
		cin >> user;
		User * userptr = interface.get_userptr(user);
		cout << endl << "Enter the amount to be given." << endl;
		cin >> amount;
		userptr->set_freebets(amount);
		//eisagw sto arxeio to freebet;
		interface.save();
		return 1;
	}
	else if ((leitourgia.compare("S") == 0) || (leitourgia.compare("Save") == 0) || (leitourgia.compare("s") == 0) || (leitourgia.compare("save") == 0)) {
		bool save = true;
		save = interface.save();
		if (save == true) {
			cout << "Files update successful!" << endl;
		}
		else {
			cout << "An error occured! Current state could not be saved." << endl;
		}
		return 1;
	}
	else if ((leitourgia.compare("X") == 0) || (leitourgia.compare("Exit") == 0) || (leitourgia.compare("x") == 0) || (leitourgia.compare("exit") == 0)) {
		cout << "Exiting the program..." << endl;
		return 0; //eksodos apo to sistima
	}
	else if ((leitourgia.compare("L") == 0) || (leitourgia.compare("Logs") == 0) || (leitourgia.compare("l") == 0) || (leitourgia.compare("logs") == 0)) {
		//fanh diko sou!!
		return 1;
	}
	else if ((leitourgia.compare("U") == 0) || (leitourgia.compare("Users") == 0) || (leitourgia.compare("u") == 0) || (leitourgia.compare("users") == 0)) {
		cout << "Select a choice:" << endl;
		cout << "V(View), to view users info." << endl;
		cout << "S(Search), to search a user." << endl;
		cout << "L(Lock), to change the exclusion state of a user." << endl;
		string option;
		cin >> option;
		if ((option == "V") || (option == "View")) {
			interface.print_users();
			cout << endl;
		}
		else if ((option == "S") || (option == "Search")) {
			cout << "Type the username:" << endl;
			string username;
			cin >> username;
			interface.search_user(username);
			cout << endl;
		}
		else if ((option == "L") || (option == "Lock")) {
			cout << "Type the username:" << endl;
			string username;
			cin >> username;
			interface.lock_user(username);
			cout << endl;
			interface.save();
		}
		else {
			cout << "WRONG INPUT" << endl;;
		}
		return 1;
	}
	else {
		cout << "WRONG INPUT" << endl;
		return 1;
	}
}

void Guest::Print_Operations(BetAtzis& interface) {
	cout << "Press the ID of the node you want to enter." << endl;
	cout << "H(Home), to return to home screen." << endl;
	cout << "T(Toggle), to toggle prices." << endl;
	cout << "X(Exit), to exit." << endl;
}

void Punter::Print_Operations(BetAtzis& interface) {
	cout << "Press the ID of the node you want to enter." << endl;
	cout << "H(Home), to return to home screen." << endl;
	cout << "T(Toggle), to toggle prices." << endl;
	cout << "A(Account), to change your account settings." << endl;
	if (interface.get_current_level() == 4) {
		cout << "P(Place), to place your bet." << endl;
	}
	cout << "X(Exit), to exit." << endl;
}

void Trader::Print_Operations(BetAtzis& interface) {
	cout << "Press the ID of the node you want to enter." << endl;
	cout << "H(Home), to return to home screen." << endl;
	cout << "T(Toggle), to toggle prices." << endl;
	cout << "B(Bets), to see the last 20 bets." << endl;
	cout << "F(Freebets), to give coupon to punter." << endl;
	if (interface.get_current_level() == 4) {
		cout << "V(Void), to cancel a selection." << endl;
		cout << "S(Settle), to settle the market." << endl;
	}
	cout << "X(Exit), to exit." << endl;
}

void Director::Print_Operations(BetAtzis& interface) {
	cout << "Press the ID of the node you want to enter." << endl;
	cout << "H(Home), to return to home screen." << endl;
	cout << "T(Toggle), to toggle prices." << endl;
	cout << "B(Bets), to see the last 20 bets." << endl;
	cout << "F(Freebets), to give coupon to punter." << endl;
	cout << "S(Save), to save current state and synchronize system files." << endl;
	cout << "X(Exit), to exit." << endl;
	cout << endl << "MANAGEMENT:" << endl;
	cout << "L(Logs), to see the last 25 logs." << endl;
	cout << "U(Users), to manage users." << endl;
	cout << "V(Visibility), to change the visibility of a node." << endl;
	cout << "R(Rename), to rename a node." << endl;
	cout << "N(New), to create a new node." << endl;
	cout << "C(Copy), to copy a node(hidden)." << endl;
	cout << "D(Delete), to delete a node." << endl;
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
	sbalance = converter2.str();
	if (sbalance.empty()) sbalance = "-";
	appuser = sid + "|" + this->get_username() + "|" + this->get_fullname() + "|" + this->get_password() + "|1|" + this->get_Status() + "|" + sbalance + "|" + this->get_free_bets() + "|";
	return appuser;
}

string Trader::conversion() {
	string sid,appuser;
	stringstream converter;
	converter << this->get_id();
	sid = converter.str();
	appuser = sid + "|" + this->get_username() + "|" + this->get_fullname() + "|" + this->get_password() + "|2| | | |";
	return appuser;
}

string Director::conversion() {
	string sid, appuser;
	stringstream converter;
	converter << this->get_id();
	sid = converter.str();
	appuser = sid + "|" + this->get_username() + "|" + this->get_fullname() + "|" + this->get_password() + "|3| | | |";
	return appuser;
}

bet::bet(int betid, int userid, string nodeid, double stk, string rslt, User * USER, Node* NODE) {
	bet_id = betid;
	user_id = userid;
	node_id = nodeid;
	stake = stk;
	result = rslt;
	user = USER;
	node = NODE;
}

void Punter::place(BetAtzis& Interface) {
	string operation;
	//User* user = Interface->get_user();
	cout << "Balance: " << get_balance() << endl << "Select option to place the bet. " << endl;
	cin >> operation;
	bool validation = (Interface.get_node())->is_operation_valid(operation);
	if (validation == true) {
		if (operation == "Cancel") {
			return;
		}
		else {
			cout << "betting on node: " << (Interface.get_node())->get_full_id() << "." << operation << endl;
			string freebets;
			freebets = get_free_bets();
			vector<string> frbts;
			string temp;
			size_t pos;
			char c = 'a';
			cout << "Your free bets: " << endl;
			if (freebets != "-"){
				while (!freebets.empty()) {
					temp = freebets;
					pos = temp.find(",");
					if (pos != -1) {
						temp.erase(temp.begin() + pos, temp.end());
						cout << c << ". " << temp << endl;
						frbts.push_back(temp);
						c++;
						freebets = freebets.substr(pos + 1);
					}
					else {
						cout << c << ". " << temp << endl;
						frbts.push_back(temp);
						c++;
						freebets.clear();
					}
					
				}
			}
			else {
				cout << "No freebets available." << endl;
			}
			cout << "Enter the amount, or choose the coupon you wish(if there is available)." << endl;
			string sbounty;
			cin >> sbounty;
			int selection;
			stringstream converter2(operation);
			converter2 >> selection;
			if (!(isdigit(sbounty[0]) == 0)) {
				int bounty;
				stringstream converter(sbounty);
				converter >> bounty;
				if (bounty < 0) {
					cout << "You can't place a negative bounty" << endl;
					return;
				}
				if (get_balance() == 0) {
					cout << "Your balance is 0. Please fill your wallet from the the main menu. " << endl;
					return;
				}
				if (bounty > get_balance()) {
					cout << "Please enter a smaller bet. Your balance is smaller than the bet you played. " << endl;
					//flag smth
				}
				else {
					set_balance(-bounty);
					string node_id;
					//it recursively needs to go back to all nodes and get their id;
					node_id = (Interface.get_node())->get_next(selection)->get_full_id();
					//des to mia re kosta giati exeis ftiaksei mia get_id sto node inline void pou den katalavenw giati litourgei etsi
					Interface.set_bet(node_id, bounty, selection);
					Interface.save();
					cout << "Bet placed. "<< bounty << " credits were removed from your wallet." << endl;
				}
			}
			else {
				int coupon = sbounty[0] - '0';
				coupon -= 48; // converting from ascii -48 .
				int selection;
				stringstream converter(operation);
				converter >> selection;
				converter.clear();
				stringstream converter2(frbts[coupon-1]);
				int bounty;
				converter2 >> bounty;
				string node_id = (Interface.get_node())->get_next(selection)->get_full_id();
				Interface.set_bet(node_id, bounty, selection);
				frbts.erase(frbts.begin() + coupon - 1);
				freebets.clear();
				if (frbts.size() > 1) {
					for (int i = 0; i < frbts.size() - 1; i++) {
						freebets += frbts[i] + ",";
					}
					freebets += frbts[frbts.size()];
				}
				else if(frbts.size()>0){
					freebets = frbts[frbts.size()-1];
				}
				else {
					freebets.clear();
				}
				initialize_freebets(freebets);
				Interface.save();
				cout << "Bet placed." << endl;
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
	sstake = converter2.str();
	stringstream converter3;
	converter3 << this->get_bet_id();
	sbetid = converter3.str();
	bet = sbetid + "|" + sid + "|" + this->get_nodeid() + "|" + sstake + "|" + this->get_result() + "|";
	return bet;
}