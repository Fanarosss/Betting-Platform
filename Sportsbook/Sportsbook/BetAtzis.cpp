#include "stdafx.h"
#include "BetAtzis.h"
#include "Main_functions.h"

using namespace std;

BetAtzis::BetAtzis() {
	fstream hierarchy("hierarchy.dat", std::fstream::in);
	//read from hierarchy.dat and create the categeories in home, subcategories in categories etc.
	string HierLine,temp,name,time;
	short int NodeCounter;
	type_ofProfits = "Klasmatika"; // by deafult, if you toggle it goes dekadika
	Category* Cptr = NULL;
	Subcategory* SCptr = NULL;
	Event* Eptr = NULL;
	Market* Mptr = NULL;
	Selection* Sptr = NULL;
	home = new Home();
	node = home;
	Current_lvl = 0;
	profits = 0;
	promitheia = 0.05;
	do{
		NodeCounter = 0;
		getline(hierarchy, HierLine);
		temp = HierLine;
		size_t pos;
		pos = temp.find(" ");
		temp.erase((temp.begin() + pos), temp.end()); //adeiazo to temp apo ta ipoloipa
		while (!temp.empty()) {
			if (pos = temp.find(".") != string::npos) {
				NodeCounter++;
				temp = temp.substr(pos + 1);
			}
			else if (temp.length() < 5) {
				NodeCounter++;
				temp.clear();
				}
		}
		name = HierLine;
		bool voided=0;
		size_t position = name.find(" ");
		name = name.substr(position + 1); //svinei tous arithmous kai to space
		switch (NodeCounter) {
			case 1: {Category* cptr = home->set_category(name);
					cptr->set_back(home);
					cptr->set_location("");
					Cptr = cptr;
					nodes.push_back(cptr);
					break; }
			case 2: {Subcategory* scptr = Cptr->set_subcategory(name);
					scptr->set_back(Cptr);
					scptr->set_location("");
					SCptr = scptr;
					nodes.push_back(scptr);
					break; }
			case 3: {size_t pos;
					time = name;
					pos = time.find("-");
					if (pos != string::npos) {   //uparxoun gegonota pou DEN EXOUN TIME
						time = time.substr(pos + 1);
						size_t length = time.length();
						name.erase((name.begin() + (name.length() - length - 1)), name.end());
					}
					else {
						time = "";
					}
					Event* eptr = SCptr->set_event(name, time);
					eptr->set_back(SCptr);
					eptr->set_location("");
					Eptr = eptr;
					nodes.push_back(eptr);
					break; }
			case 4: {Market* mptr = Eptr->set_market(name);
					mptr->set_back(Eptr);
					mptr->set_location("");
					Mptr = mptr;
					nodes.push_back(mptr);
					break; }
			case 5: {string profit = name;
					pos = profit.find("#");
					profit = profit.substr(pos + 1);
					pos = profit.find("(");
					if (pos != std::string::npos) {
						voided = 1;
						profit.erase(profit.begin() + pos, profit.end());
					}
					else {
						voided = 0;
					}
					size_t length = profit.length();
					pos = name.find("#");
					name.erase((name.begin() + pos), name.end());
					Selection* sptr = Mptr->set_selection(name, profit, voided);
					sptr->set_back(Mptr);
					sptr->set_location("");
					Sptr = sptr;
					nodes.push_back(sptr);
					break; }
			}
	} while (!HierLine.empty() && !hierarchy.eof());
	hierarchy.close();
	ifstream Users("users.csv"); //initializing the vector with all of the users.
	if (Users.is_open()) {
		string suser;
		getline(Users, suser); //1. gia na parei tous titlous
		getline(Users, suser); //2. gia na ksekinsei apo tin proti grammi
		while (!Users.eof() && !suser.empty()) {
			int Type = extract_type(suser);
			switch (Type) {
			case 1: users.push_back(new Punter(extract_id(suser), extract_username(suser), extract_fullname(suser), extract_password(suser),extract_balance(suser)));
				break;
			case 2: users.push_back(new Trader(extract_id(suser), extract_username(suser), extract_fullname(suser), extract_password(suser)));
				break;
			case 3: users.push_back(new Director(extract_id(suser), extract_username(suser), extract_fullname(suser), extract_password(suser)));
				break;
			}
			getline(Users, suser); //sto telos gia na mpainei ston elegxo toy while gia eof and empty
		}
		if (!suser.empty()) { //for the last user.
			int Type = extract_type(suser);
			switch (Type) {
			case 1: users.push_back(new Punter(extract_id(suser), extract_username(suser), extract_fullname(suser), extract_password(suser), extract_balance(suser)));
				break;
			case 2: users.push_back(new Trader(extract_id(suser), extract_username(suser), extract_fullname(suser), extract_password(suser)));
				break;
			case 3: users.push_back(new Director(extract_id(suser), extract_username(suser), extract_fullname(suser), extract_password(suser)));
				break;
			}
		}

	}
	else {
		cout << "Error opening file users.csv " << endl;
	}
	Users.close();
	ifstream Bets("bets.csv");
	if (Bets.is_open()) {
		string sbet,sbet2;
		getline(Bets, sbet2);
		getline(Bets, sbet);
		if (!(sbet == sbet2)) {
			while ((!Bets.eof() && !sbet.empty())) {
				bets.push_back(new bet(extract_betid(sbet), extract_userid(sbet), extract_nodeid(sbet), extract_stake(sbet), extract_result(sbet), this->get_userptr(extract_userid(sbet)), (this->home)->get_node_byid(extract_nodeid(sbet)))); //den kserw epidi eimaste mesa ston consturctor tou interface an mporo na to kanw auto
				getline(Bets, sbet);
			}
			if (!sbet.empty()) {
				bets.push_back(new bet(extract_betid(sbet), extract_userid(sbet), extract_nodeid(sbet), extract_stake(sbet), extract_result(sbet), this->get_userptr(extract_userid(sbet)), (this->home)->get_node_byid(extract_nodeid(sbet))));
			}
		}
	}
	else {
		cout << "Error opening bets" << endl;
	}
	Bets.close();
}

bool BetAtzis::operation(string op, BetAtzis* interface) {
	bool OP = user->Operation(op, *interface);
	return OP;
}

void BetAtzis::print_user_bets() {
	for (int i = 0; i < bets.size(); i++) {
		if (bets[i]->get_user_id() == user->get_id()) {
			cout << bets[i]->get_nodeid() << "|" << bets[i]->get_stake() << "|";
			if (bets[i]->get_voided() == 0) {
				if (bets[i]->get_result() == "-") {
					cout << "Pending|" << endl;
				}
				else if(bets[i]->get_result() == "W") {
					cout << "Won|" << endl;
				}
				else {
					cout << "Lost|" << endl;
				}
			}
			else {
				cout << "Voided|" << endl;
			}
		}
	}
}

void BetAtzis::voided(string full_id) {				//epistrofh xrhmatwn
	int user_id;
	double stake;
	for (int i = 0; i < bets.size(); i++) {
		stake = 0;
		user_id = 0;
		if (bets[i]->get_nodeid() == full_id) {
			user_id = bets[i]->get_user_id();
			stake = bets[i]->get_stake();
			users[user_id - 1]->set_balance(stake);
			bets[i]->set_result();
			//delete bets[i];
		}
	}
}

void BetAtzis::settle(string full_id, int option) {
	for (int i = 0; i < node->get_vector_size(); i++) {
		node = node->get_next(i + 1);
		int id;
		node->get_id(id);
		if (id == option) {
			node->set_result("W");
			string s1 = node->get_result();
		}
		else {
			if (node->get_voided() == 0) {
				node->set_result("L");
				string s2 = node->get_result();
			}
		}
		node = node->get_back();
	}
	for (int j = 0; j < bets.size(); j++) {
		bets[j]->set_result();
		string s3 = bets[j]->get_result();
	}
}

void BetAtzis::pay(string full_id, double profit) {
	int user_id;
	double earnings, stake, commission;
	for (int i = 0; i < bets.size(); i++) {
		user_id = 0;
		earnings = 0;
		stake = 0;
		commission = 0;
		if (bets[i]->get_nodeid() == full_id) {
			user_id = bets[i]->get_user_id();
			stake = bets[i]->get_stake();
			earnings = profit*stake;
			commission = promitheia*earnings;
			earnings = earnings - commission;
			users[user_id - 1]->set_balance(earnings);
			profits += commission;
		}
	}
}

BetAtzis::~BetAtzis() {
	//cout << "System destroyed" << endl;
}


//functions for vector initialization

string extract_username(string appuser) {
	size_t pos;
	for (int i = 1; i<2; i++) {
		pos = appuser.find("|");
		appuser = appuser.substr(pos + 1); //gia na aferesei kai tin pavla mazi
	} //krataei olo to string deksia apo auto pou psaxnw
	int count_of_string = 0;
	while ((appuser[count_of_string] != '|')) {
		count_of_string++;
	}
	appuser.erase((appuser.begin() + count_of_string), appuser.end()); //now appuser = what im looking for
																	   //svistike kai to deksia
	string username = appuser; //now appuser equals to username; pass it throught only for clarity issues.
	return username;
}

string extract_password(string appuser) {
	size_t pos;
	for (int i = 1; i<4; i++) {
		pos = appuser.find("|");
		appuser = appuser.substr(pos + 1); //gia na aferesei kai tin pavla mazi
	} //krataei olo to string deksia apo auto pou psaxnw
	int count_of_string = 0;
	while ((appuser[count_of_string] != '|')) {
		count_of_string++;
	}
	appuser.erase((appuser.begin() + count_of_string), appuser.end()); //now appuser = what im looking for
																	   //svistike kai to deksia
	string password = appuser; //now appuser equals to username; pass it throught only for clarity issues.
	return password;
}

string extract_fullname(string appuser) {
	size_t pos;
	for (int i = 1; i<3; i++) {
		pos = appuser.find("|");
		appuser = appuser.substr(pos + 1); //gia na aferesei kai tin pavla mazi
	} //krataei olo to string deksia apo auto pou psaxnw
	int count_of_string = 0;
	while ((appuser[count_of_string] != '|')) {
		count_of_string++;
	}
	appuser.erase((appuser.begin() + count_of_string), appuser.end()); //now appuser = what im looking for
																	   //svistike kai to deksia
	string fullname = appuser; //now appuser equals to username; pass it throught only for clarity issues.
	return fullname;
}

double extract_balance(string appuser) {
	size_t pos;
	for (int i = 1; i<7; i++) {
		pos = appuser.find("|");
		appuser = appuser.substr(pos + 1); //gia na aferesei kai tin pavla mazi
	} //krataei olo to string deksia apo auto pou psaxnw
	int count_of_string = 0;
	while ((appuser[count_of_string] != '|')) {
		count_of_string++;
	}
	appuser.erase((appuser.begin() + count_of_string), appuser.end()); //now appuser = what im looking for
																	   //svistike kai to deksia
	double balance = 0.0; //now appuser equals to username; pass it throught only for clarity issues.
	if (appuser == "-") {
		balance = 0;
	}
	else {
		stringstream converter;
		converter << appuser;
		converter >> balance;
	}
	return balance;
}

string extract_status(string appuser) {
	size_t pos;
	for (int i = 1; i<6; i++) {
		pos = appuser.find("|");
		appuser = appuser.substr(pos + 1); //gia na aferesei kai tin pavla mazi
	} //krataei olo to string deksia apo auto pou psaxnw
	int count_of_string = 0;
	while ((appuser[count_of_string] != '|')) {
		count_of_string++;
	}
	appuser.erase((appuser.begin() + count_of_string), appuser.end()); //now appuser = what im looking for
																	   //svistike kai to deksia
	string status = appuser; //now appuser equals to username; pass it throught only for clarity issues.
	return status;
}

int extract_type(string appuser) {
	size_t pos;
	for (int i = 1; i<5; i++) {
		pos = appuser.find("|");
		appuser = appuser.substr(pos + 1); //gia na aferesei kai tin pavla mazi
	} //krataei olo to string deksia apo auto pou psaxnw
	int count_of_string = 0;
	while ((appuser[count_of_string] != '|')) {
		count_of_string++;
	}
	appuser.erase((appuser.begin() + count_of_string), appuser.end()); //now appuser = what im looking for
																	   //svistike kai to deksia
	int type;
	stringstream converter(appuser);
	converter >> type;
	return type;
}

int extract_id(string appuser) {
	int count_of_string = 0;
	while ((appuser[count_of_string] != '|')) {
		count_of_string++;
	}
	appuser.erase((appuser.begin() + count_of_string), appuser.end()); //now appuser = what im looking for
																	   //svistike kai to deksia
	int id;
	stringstream converter(appuser);
	converter >> id;
	return id;
}

//functions for bets csv

int extract_betid(string sbet) {
	size_t pos;
	int ibet;
	pos = sbet.find("|");
	if (pos != -1)
	sbet.erase(sbet.begin() + pos, sbet.end());
	stringstream converter(sbet);
	converter >> ibet;
	return ibet;
}

int extract_userid(string sbet) {
	size_t pos;
	int user_id;
	for (int i = 1; i<2; i++) {
		pos = sbet.find("|");
		sbet = sbet.substr(pos + 1); //gia na aferesei kai tin pavla mazi
	} //krataei olo to string deksia apo auto pou psaxnw
	pos = sbet.find("|");
	sbet.erase(sbet.begin() + pos, sbet.end());
	stringstream converter(sbet);
	converter >> user_id;
	return user_id;
}

string extract_nodeid(string sbet) {
	string node_id;
	size_t pos;
	for (int i = 1; i<3; i++) {
		pos = sbet.find("|");
		sbet = sbet.substr(pos + 1); //gia na aferesei kai tin pavla mazi
	} //krataei olo to string deksia apo auto pou psaxnw
	pos = sbet.find("|");
	sbet.erase(sbet.begin() + pos, sbet.end());
	node_id = sbet;
	return node_id;
}

double extract_stake(string sbet) {
	double stake = 0.0;
	size_t pos;
	for (int i = 1; i<4; i++) {
		pos = sbet.find("|");
		sbet = sbet.substr(pos + 1); //gia na aferesei kai tin pavla mazi
	} //krataei olo to string deksia apo auto pou psaxnw
	pos = sbet.find("|");
	sbet.erase(sbet.begin() + pos, sbet.end());
	stringstream converter(sbet);
	converter >> stake;
	return stake;
}

string extract_result(string sbet) {
	string outcome;
	size_t pos;
	for (int i = 1; i<5; i++) {
		pos = sbet.find("|");
		sbet = sbet.substr(pos + 1); //gia na aferesei kai tin pavla mazi
	} //krataei olo to string deksia apo auto pou psaxnw
	pos = sbet.find("|");
	sbet.erase(sbet.begin() + pos, sbet.end());
	outcome = sbet;
	return outcome;

}

//functions for vector changes

void BetAtzis::set_new_username(string OLD, string NEW) {
	User* user = NULL;
	for (int i = 0; i <= users.size(); i++) {
		string name = users[i]->get_username();
		if (name == OLD) {
			user = users[i];
			break;
		}
	}
	user->set_username(NEW);
	//metafora vector se arxeio
}

void BetAtzis::set_new_password(string name, string NEW) {
	User* user = NULL;
	for (int i = 0; i <= users.size(); i++) {
		string username = users[i]->get_username();
		if (username == name) {
			user = users[i];
			break;
		}
	}
	user->set_password(NEW);
	//metafora vector se arxeio//
}

void BetAtzis::set_new_balance(string name, double ADD) {
	User* user = NULL;
	for (int i = 0; i <= users.size(); i++) {
		string username = users[i]->get_username();
		if (username == name) {
			user = users[i];
			break;
		}
	}
	user->set_balance(ADD);
	user->print_balance();
}

bool BetAtzis::save() {
	//users save
fstream newfile("users.csv", std::fstream::out);
if (newfile.is_open()) {
	newfile << "user_id|username|fullname|password|type|status|balance|freebets|";
	for (int i = 0; i < users.size(); i++) {
		newfile << endl << users[i]->conversion();
	}
}
else {
	cout << "can't open file." << endl;
	newfile.close();
	return false;
}
newfile.close();
//bets save
fstream Bets("bets.csv", std::fstream::out);
if (Bets.is_open()) {
	Bets << "bet_id|user_id|node_id|stake|result|";
	for (int i = 0; i < bets.size(); i++) {
		if (bets[i] != NULL) {
			Bets << endl << bets[i]->conversion();
		}
	}
}
else {
	cout << "can't open file." << endl;
	Bets.close();
	return false;
}
Bets.close();
//hierarchy save
fstream hierarchy("hierarchy.dat", std::fstream::out);
if (hierarchy.is_open()) {
	hierarchy << nodes[0]->conversion();
	for (int i = 1; i < nodes.size(); i++) {
		hierarchy << endl << nodes[i]->conversion();
	}
	hierarchy.close();
}
return true;
}

User * BetAtzis::current_user(string usrnm) {
	for (int i = 0; i < users.size(); i++) {
		if (usrnm == (users[i]->get_username())) {
			return users[i];
			break;
		}
	}
}

void BetAtzis::set_bet(string node_id, double stake, int selection_id) {
	int bet_id, user_id = 0;
	bet_id = bets.size() + 1;
	for (int i = 0; i < users.size(); i++) {
		if (user == users[i]) {
			user_id = i + 1;
			break;
		}
	}
	string result = "-";
	Node * s_node = node->get_selection_ptr(selection_id);
	bets.insert(bets.begin(), new bet(bet_id, user_id, node_id, stake, result, user, s_node));
}

string BetAtzis::get_bet(int bet_id) {
	string bet = "-";
	string sbetid, userid, stake, node_id, result;
	//getting all of those putting them into bet and returning bet;
	return bet;
}

//management

void BetAtzis::print_users() {
	cout << "user_id|username|fullname|password|type|status|balance|freebets|";
	for (int i = 0; i < users.size(); i++) {
		cout << endl << users[i]->conversion();
	}
}

void BetAtzis::search_user(string user) {
	int found = 0;
	string username;
	for (int i = 0; i < users.size(); i++) {
		username = users[i]->get_username();
		if (username.find(user) != string::npos) {
			found++;
			if (found == 1) {
				cout << "user_id|username|fullname|password|type|status|balance|freebets|";
			}
			cout << endl << users[i]->conversion();
		}
	}
	if (found == 0) {
		cout << "The user does not exist." << endl;
	}
}

void BetAtzis::lock_user(string user) {
	string status, comment, full;
	bool found = false;
	for (int i = 0; i < users.size(); i++) {
		if (users[i]->get_username() == user){
			found = true;
			if (users[i]->get_type() == 3) {
				cout << "You cannot lock a director." << endl;
				return;
			}
			else {
				if (users[i]->get_Status().empty()) {
					status = "L";
					cout << "Please explain why you exclude this user:"<<endl;
					cin.get();
					getline(cin, comment);
					if (comment.empty()) {
						comment = "N/A";
					}
					full = status + ", " + comment;
					users[i]->set_status(full);
				}
				else {
					cout << "Please explain why you include this user again:"<<endl;
					cin.get();
					getline(cin, comment);
					if (comment.empty()) {
						comment = "-";
					}
					users[i]->set_status(comment);
				}
			}
		}
	}
	if (found == false) {
		cout << "The user does not exist." << endl;
	}
}
/*void BetAtzis::set_results(string node_id) { //for betatzis
	for (int i = 0; i < bets.size(); i++) {
		if (bets[i]->get_nodeid() == node_id) {
			bets[i]->set_result("Winning");
		}
	}
	this->save();
}
*/