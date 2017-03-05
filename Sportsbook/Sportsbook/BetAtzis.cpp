#include "stdafx.h"
#include "BetAtzis.h"
#include "Main_functions.h"

using namespace std;

BetAtzis::BetAtzis() {
	fstream hierarchy("hierarchy.dat", std::fstream::in);
	//read from hierarchy.dat and create the categeories in home, subcategories in categories etc.
	string HierLine,temp,name,time;
	short int NodeCounter;
	type_ofProfits = "Klasmatika"; // by deafult, if you toggle it goes "dekadika"
	Category* Cptr = NULL;
	Subcategory* SCptr = NULL;
	Event* Eptr = NULL;
	Market* Mptr = NULL;
	Selection* Sptr = NULL;
	home = new Home();
	node = home;
	Current_lvl = 0; //0 is for home, 1 for categories, 2 for subcategories etc.
	profits = 0;
	promitheia = 0.05;  //commission taken from every bet
	do{
		NodeCounter = 0;
		getline(hierarchy, HierLine);
		temp = HierLine;
		size_t pos;
		pos = temp.find(" ");
		temp.erase((temp.begin() + pos), temp.end()); //erase everything apart from node id
		while (!temp.empty()) {
			if (pos = temp.find(".") != string::npos) { //identify the current level(category,subcategory etc.)
				NodeCounter++;
				temp = temp.substr(pos + 1);
			}
			else if (temp.length() < 5) {
				NodeCounter++;
				temp.clear();
				}
		}
		name = HierLine;
		bool voided=0;		//flag to see if node is voided
		bool hidden = 0;	//flag to see if node is hidden
		string visibility = HierLine;
		size_t pos2 = visibility.find("[Hidden]");
		if (pos2 != std::string::npos) hidden = 1;
		size_t position = name.find(" ");
		name = name.substr(position + 1);	//delete node id and space
		switch (NodeCounter) {				//find which node to create
			case 1: {Category* cptr = home->set_category(name);
					cptr->set_back(home);					//pointer to the previous class
					cptr->set_location("");
					cptr->set_visibility(hidden);
					Cptr = cptr;
					nodes.push_back(cptr);					//put node to (vector) nodes in BetAtzis
					break; }
			case 2: {Subcategory* scptr = Cptr->set_subcategory(name);
					scptr->set_back(Cptr);
					scptr->set_location("");
					scptr->set_visibility(hidden);
					SCptr = scptr;
					nodes.push_back(scptr);
					break; }
			case 3: {size_t pos;
					time = name;
					pos = time.find("-");
					if (pos != string::npos) {   //check if there is no time
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
					eptr->set_visibility(hidden);
					Eptr = eptr;
					nodes.push_back(eptr);
					break; }
			case 4: {Market* mptr = Eptr->set_market(name);
					mptr->set_back(Eptr);
					mptr->set_location("");
					mptr->set_visibility(hidden);
					Mptr = mptr;
					nodes.push_back(mptr);
					break; }
			case 5: {string profit = name;
					pos = profit.find("#");			//separate profit from name
					profit = profit.substr(pos + 1);
					pos = profit.find("(");
					if (pos != std::string::npos) {		//check if there is no profit
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
					sptr->set_visibility(hidden);
					Sptr = sptr;
					nodes.push_back(sptr);
					break; }
			}
	} while (!HierLine.empty() && !hierarchy.eof());
	hierarchy.close();
	ifstream Users("users.csv"); //initializing the vector with all of the users
	if (Users.is_open()) {
		string suser;
		getline(Users, suser); //1. to take the borders of the array, meaning "user_id|username|fullname|.."
		getline(Users, suser); //2. to start from the first user
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
			getline(Users, suser);
		}
		if (!suser.empty()) { //for the last user
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
	ifstream Bets("bets.csv"); //initializing the vector with all of the bets
	if (Bets.is_open()) {
		string sbet,sbet2;
		getline(Bets, sbet2);		//1. to take the borders of the array, meaning "bet_id|user_id|node_id|.."
		getline(Bets, sbet);		//2. to start from the first user
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
	fstream logs("audit.log", std::fstream::in); //opening audit.log to take the number of already registered logs
	if (logs.is_open()) {
		string line, myline;
		int log_id;
		getline(logs, line);
		while (!logs.eof()) {
			getline(logs, line);
		}
		if (isdigit(line[0]) == 0) {
			set_num_of_logs(0);
		}
		else {
			log_id = extract_id(line);
			set_num_of_logs(log_id);
		}
		logs.close();
	}
	else {
		logs.close();
		cout << "Error opening audit.log" << endl;
	}

}

bool BetAtzis::operation(string op, BetAtzis* interface) {	//operation of BetAtzis calls operation of user
	bool OP = user->Operation(op, *interface);
	return OP;
}

void BetAtzis::print_user_bets() {		//printing the last 20 bets of a single user
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

void BetAtzis::voided(string full_id) {		//return stake to users after a node was declared voided
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
		}
	}
}

void BetAtzis::settle(string full_id, int option) {		//settle the winning option and the losing ones
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

void BetAtzis::pay(string full_id, double profit) {			//pay the users who won and keep the commission
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

string extract_username(string appuser) {		//find user's username from a line of a file
	size_t pos;
	for (int i = 1; i<2; i++) {
		pos = appuser.find("|");
		appuser = appuser.substr(pos + 1); 
	}
	int count_of_string = 0;
	while ((appuser[count_of_string] != '|')) {
		count_of_string++;
	}
	appuser.erase((appuser.begin() + count_of_string), appuser.end()); //now appuser = what im looking for
	string username = appuser; //now appuser equals to username; pass it throught only for clarity issues.
	return username;
}

string extract_password(string appuser) {		//find user's password from a line of a file
	size_t pos;
	for (int i = 1; i<4; i++) {
		pos = appuser.find("|");
		appuser = appuser.substr(pos + 1); 
	}
	int count_of_string = 0;
	while ((appuser[count_of_string] != '|')) {
		count_of_string++;
	}
	appuser.erase((appuser.begin() + count_of_string), appuser.end()); 
	string password = appuser;
	return password;
}

string extract_fullname(string appuser) {		//find user's fullname from a line of a file
	size_t pos;
	for (int i = 1; i<3; i++) {
		pos = appuser.find("|");
		appuser = appuser.substr(pos + 1);
	} 
	int count_of_string = 0;
	while ((appuser[count_of_string] != '|')) {
		count_of_string++;
	}
	appuser.erase((appuser.begin() + count_of_string), appuser.end()); 
	string fullname = appuser; 
	return fullname;
}

double extract_balance(string appuser) {		//find user's balance from a line of a file
	size_t pos;
	for (int i = 1; i<7; i++) {
		pos = appuser.find("|");
		appuser = appuser.substr(pos + 1); 
	}
	int count_of_string = 0;
	while ((appuser[count_of_string] != '|')) {
		count_of_string++;
	}
	appuser.erase((appuser.begin() + count_of_string), appuser.end());
	double balance = 0.0; 
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

string extract_status(string appuser) {		//find user's status from a line of a file
	size_t pos;
	for (int i = 1; i<6; i++) {
		pos = appuser.find("|");
		appuser = appuser.substr(pos + 1); 
	} 
	int count_of_string = 0;
	while ((appuser[count_of_string] != '|')) {
		count_of_string++;
	}
	appuser.erase((appuser.begin() + count_of_string), appuser.end());
	string status = appuser;
	return status;
}

int extract_type(string appuser) {			//find user's type from a line of a file
	size_t pos;
	for (int i = 1; i<5; i++) {
		pos = appuser.find("|");
		appuser = appuser.substr(pos + 1); 
	} 
	int count_of_string = 0;
	while ((appuser[count_of_string] != '|')) {
		count_of_string++;
	}
	appuser.erase((appuser.begin() + count_of_string), appuser.end());
	int type;
	stringstream converter(appuser);
	converter >> type;
	return type;
}

int extract_id(string appuser) {			//find user's id from a line of a file
	int count_of_string = 0;
	while ((appuser[count_of_string] != '|')) {
		count_of_string++;
	}
	appuser.erase((appuser.begin() + count_of_string), appuser.end());
	int id;
	stringstream converter(appuser);
	converter >> id;
	return id;
}



//functions for bets csv

int extract_betid(string sbet) {			//find bet's id from a line of bets.csv
	size_t pos;
	int ibet;
	pos = sbet.find("|");
	if (pos != -1)
	sbet.erase(sbet.begin() + pos, sbet.end());
	stringstream converter(sbet);
	converter >> ibet;
	return ibet;
}

int extract_userid(string sbet) {			//find user's id from a line of bets.csv
	size_t pos;
	int user_id;
	for (int i = 1; i<2; i++) {
		pos = sbet.find("|");
		sbet = sbet.substr(pos + 1); 
	}
	pos = sbet.find("|");
	sbet.erase(sbet.begin() + pos, sbet.end());
	stringstream converter(sbet);
	converter >> user_id;
	return user_id;
}

string extract_nodeid(string sbet) {		//find node's id from a line of bets.csv
	string node_id;
	size_t pos;
	for (int i = 1; i<3; i++) {
		pos = sbet.find("|");
		sbet = sbet.substr(pos + 1); 
	} 
	pos = sbet.find("|");
	sbet.erase(sbet.begin() + pos, sbet.end());
	node_id = sbet;
	return node_id;
}

double extract_stake(string sbet) {			//find user's stake from a line of bets.csv
	double stake = 0.0;
	size_t pos;
	for (int i = 1; i<4; i++) {
		pos = sbet.find("|");
		sbet = sbet.substr(pos + 1);
	}
	pos = sbet.find("|");
	sbet.erase(sbet.begin() + pos, sbet.end());
	stringstream converter(sbet);
	converter >> stake;
	return stake;
}

string extract_result(string sbet) {		//find bet's result from a line of bets.csv
	string outcome;
	size_t pos;
	for (int i = 1; i<5; i++) {
		pos = sbet.find("|");
		sbet = sbet.substr(pos + 1);
	} 
	pos = sbet.find("|");
	sbet.erase(sbet.begin() + pos, sbet.end());
	outcome = sbet;
	return outcome;

}



//functions for vector changes

void BetAtzis::set_new_username(string OLD, string NEW) {			//for function "rename" of users
	User* user = NULL;
	for (int i = 0; i <= users.size(); i++) {
		string name = users[i]->get_username();
		if (name == OLD) {
			user = users[i];
			break;
		}
	}
	user->set_username(NEW);
}

void BetAtzis::set_new_password(string name, string NEW) {			//for function "password" of users
	User* user = NULL;
	for (int i = 0; i <= users.size(); i++) {
		string username = users[i]->get_username();
		if (username == name) {
			user = users[i];
			break;
		}
	}
	user->set_password(NEW);
}

void BetAtzis::set_new_balance(string name, double ADD) {			//for function "deposit" of users
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


//function to save any changes

bool BetAtzis::save() {
	//users.csv save
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
	//bets.csv save
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
	//hierarchy.dat save
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



//function for audit.log

bool BetAtzis::write_log(string origin, string user, string action, string outcome = "SUCCESS") {	//write every action to audit.log
	int log_id = get_num_of_logs();
	set_num_of_logs(++log_id);																	//increase logs by one to add the new one
	fstream logs("audit.log", std::fstream::out | std::fstream::app);
	if (logs.is_open()) {
		string log, myline;
		stringstream converter;
		converter << log_id;
		converter >> log;
		myline = log + "|" + origin + "|" + user + "|" + action + "|" + outcome + "|";			//write log_id, where, who, what and if it was successful
		logs << endl << myline;
		logs.close();
		return true;
	}
	else {
		logs.close();
		cout << "Error, cannot open log file." << endl;
		return false;
	}
}


//BetAtzis functions

User * BetAtzis::current_user(string usrnm) {				//search for a user by username and return pointer to this user
	for (int i = 0; i < users.size(); i++) {
		if (usrnm == (users[i]->get_username())) {
			return users[i];
			break;
		}
	}
}

void BetAtzis::set_bet(string node_id, double stake, int selection_id) {		//placing a bet
	int bet_id, user_id = 0;
	bet_id = bets.size() + 1;
	for (int i = 0; i < users.size(); i++) {								//find user_id of the user who placed the bet
		if (user == users[i]) {
			user_id = i + 1;
			break;
		}
	}
	string result = "-";													//result is unknown yet
	Node * s_node = node->get_selection_ptr(selection_id);					
	bets.insert(bets.begin(), new bet(bet_id, user_id, node_id, stake, result, user, s_node));
}

bet * BetAtzis::get_bet(int bet_id) {										//return pointer to a bet found by bet id
	return bets[bet_id];
}



//management

void BetAtzis::Logs() {														//print the last 25 logs
	string line;
	fstream logs("audit.log", std::fstream::in);
	if (num_of_logs >= 25) {							//if there are more than 25 logs
		getline(logs, line);
		for (int i = 0; i < num_of_logs - 25; i++) {	//delete first logs until the last 25
			getline(logs, line);
		}
		for (int i = 0; i < 25; i++) {					//print the last 25 logs
			getline(logs, line);
			cout << line << endl;
		}
	}
	else {												//if there are not more than 25 logs
		getline(logs, line);
		for (int i = 0; i < num_of_logs; i++) {			//print them all
			getline(logs, line);
			cout << line << endl;
		}
	}
}

void BetAtzis::print_users() {												//print all registered users
	cout << "user_id|username|fullname|password|type|status|balance|freebets|";
	for (int i = 0; i < users.size(); i++) {
		cout << endl << users[i]->conversion();
	}
}

void BetAtzis::search_user(string user) {									//find all users who include into their usernames the string user
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

void BetAtzis::lock_user(string user) {						//change the status of a user and give a comment about your action
	string status, comment, full;
	bool found = false;
	for (int i = 0; i < users.size(); i++) {
		if (users[i]->get_username() == user){
			found = true;
			if (users[i]->get_type() == 3) {				//3 is for directors
				cout << "You cannot lock a director." << endl;
				return;
			}
			else {
				if (users[i]->get_Status().empty()) {				//if punter is active, lock him
					status = "L";
					cout << "Please explain why you exclude this user:"<<endl;
					cin.get();										//just for the extra Enterkey
					getline(cin, comment);
					if (comment.empty()) {							//if you don't type a comment and press enter, it will show "N/A" as comment
						comment = "N/A";
					}
					full = status + ", " + comment;
					users[i]->set_status(full);
				}
				else {												//if punter is locked, unlock him
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

void BetAtzis::set_visibility(int option) {									//change the visibility of a node
	(node->get_next(option))->set_visibility();
}

bool BetAtzis::get_visibility(int option) {									//get the visibility of a node
	return (node->get_next(option))->get_visibility();
}

void BetAtzis::delete_node(string full_id) {								//delete a node and all subnodes
	bool first_found = false;		//flag for first node to be deleted
	int i = 0;
	while (i<nodes.size()) {
		string id = nodes[i]->get_full_id();
		if(id==full_id){			//if you find the node with the exact same id
			first_found = true;
			int j = i;
			while (j < nodes.size()) {
				string id = nodes[i]->get_full_id();
				size_t find = id.find(full_id);			//search for every subnode of it
				if (find != std::string::npos) {		//if you find a subnode
					nodes.erase(nodes.begin() + j);		//erase it
				}
				else break;
			}
		}
		else {						//if you don't find the node
			i++;					//go to the next one
		}
		if (first_found == true) {	//if you have found a node to erase, then break	
			break;
		}
	}
}