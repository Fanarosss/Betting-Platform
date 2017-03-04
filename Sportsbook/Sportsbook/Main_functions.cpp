#include "stdafx.h"
#include "Main_functions.h"

using namespace std;

bool check_for_password(string username,string password) {
	bool is_password_correct = false;
	string R_password = get_password(username);
	if (R_password == password) {
		is_password_correct = true;
	}
	return is_password_correct;
}

string read_from_csv(int my_pos,string appuser) {
	size_t pos;
	for (int i = 1; i<my_pos; i++) {
		pos = appuser.find("|");
		appuser = appuser.substr(pos + 1); //gia na aferesei kai tin pavla mazi
	} //krataei olo to string deksia apo auto pou psaxnw
	int count_of_string = 0;
	while ((appuser[count_of_string] != '|')) {
		count_of_string++;
	}
	appuser.erase(appuser.begin() + count_of_string, appuser.end()); //now appuser = what im looking for
	//svistike kai to deksia
	return appuser;
}

double get_balance(string username) {
	double balance;
	string appuser,s_appuser;
	fstream file("users.csv", std::fstream::in);
	do {
		s_appuser = appuser;
		getline(file, appuser); //this takes the line and put it to string appuser
		if ((appuser.find(username)) != string::npos) { //this takes the line and check if there is a word in there mathcing to the given username
			break;
		}
	} while (!file.eof() && !appuser.empty());
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
	if (appuser == "-") {
		balance = 0;
	}
	else {
		stringstream converter(appuser);
		converter >> balance;
	}
	file.close();
	return balance;
}

int get_type(string username) {
	int type;
	string appuser,s_appuser;
	fstream file("users.csv" , std::fstream::in);
	getline(file, appuser);
	while ((!file.eof()) && (!appuser.empty())) {
		s_appuser = appuser;
		getline(file, appuser); //this takes the line and put it to string appuser
		if ((appuser.find(username)) != string::npos) { //this takes the line and check if there is a word in there mathcing to the given username
			s_appuser = appuser;
			break;
		}
	}
	size_t pos;
	for (int i = 1; i<5; i++) {
		pos = s_appuser.find("|");
		s_appuser = s_appuser.substr(pos + 1); //gia na aferesei kai tin pavla mazi	
	} 
	//krataei olo to string deksia apo auto pou psaxnw
	pos = s_appuser.find("|");
	s_appuser.erase((s_appuser.begin() + pos), s_appuser.end()); //now appuser = what im looking for
	//svistike kai to deksia
	stringstream converter(s_appuser);
	converter >> type;
	file.close();
	return type;
}

string get_status(string username) {
	string status;
	string appuser, s_appuser;
	fstream file("users.csv", std::fstream::in);
	do {
		s_appuser = appuser;
		getline(file, appuser); //this takes the line and put it to string appuser
		if ((appuser.find(username)) != string::npos) { //this takes the line and check if there is a word in there mathcing to the given username
			break;
		}
	} while (!file.eof() && !appuser.empty());
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
	status = appuser;
	file.close();
	return status;
}

string get_freebets(string username) {
	string freebets;
	string appuser, s_appuser;
	fstream file("users.csv", std::fstream::in);
	do {
		s_appuser = appuser;
		getline(file, appuser); //this takes the line and put it to string appuser
		if ((appuser.find(username)) != string::npos) { //this takes the line and check if there is a word in there mathcing to the given username
			break;
		}
	} while (!file.eof() && !appuser.empty());
	size_t pos;
	for (int i = 1; i<8; i++) {
		pos = appuser.find("|");
		appuser = appuser.substr(pos + 1); //gia na aferesei kai tin pavla mazi
	} //krataei olo to string deksia apo auto pou psaxnw
	int count_of_string = 0;
	while ((appuser[count_of_string] != '|')) {
		count_of_string++;
	}
	appuser.erase((appuser.begin() + count_of_string), appuser.end()); //now appuser = what im looking for
																	   //svistike kai to deksia
	freebets = appuser;
	file.close();
	return freebets;
}

int get_id(string appuser) {
	int id = 0;
	size_t pos;
	pos = appuser.find("|");
	if (pos != string::npos)
		appuser.erase((appuser.begin() + pos), appuser.end());
	stringstream converter(appuser);
	converter >> id;
	return id;
}

string get_fullname(string username) {
	string fullname;
	string appuser, s_appuser;
	fstream file("users.csv", std::fstream::in);
	do {
		s_appuser = appuser;
		getline(file, appuser); //this takes the line and put it to string appuser
		if ((appuser.find(username)) != string::npos) { //this takes the line and check if there is a word in there mathcing to the given username
			break;
		}
	} while (!file.eof() && !appuser.empty());
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
	fullname = appuser;
	file.close();
	return fullname;
}

string get_password(string username) {
	string appuser, s_appuser,password;
	fstream file("users.csv", std::fstream::in);
	do {
		s_appuser = appuser;
		getline(file, appuser); //this takes the line and put it to string appuser
		if ((appuser.find(username)) != string::npos) { //this takes the line and check if there is a word in there mathcing to the given username
			break;
		}
	} while (!file.eof() && !appuser.empty());
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
	password = appuser;
	file.close();
	return password;
}

//reading from csv;

void print_lastbets() {
	string bet;
	fstream bets("bets.csv", std::fstream::in);
	if (bets.is_open()) {
		getline(bets, bet);
		cout << bet << endl;
		getline(bets, bet);
		while (get_betid(bet) <= 20) {
			cout << bet << endl;
			getline(bets, bet);
		}
	}
	else {
		cout << "Missing file bets. " << endl;
		return;
	}
}

int get_betid(string bet) {
	string sid;
	int id;
	size_t pos = bet.find("|");
	bet.erase(bet.begin() + pos, bet.end());
	stringstream converter(bet);
	converter >> id;
	return id;
}

bool write_log(string origin, string user, string outcome = "SUCCESS") {
	fstream logs("audit.log", std::fstream::in | std::fstream::app);
	if (logs.is_open()){
		string line;
		getline(logs, line);
		string myline;
		size_t pos;
		if (!line.empty()) {
			pos = line.find("|");
			line.erase(line.begin() + pos, line.end());
			stringstream converter(line);
			int iline;
			converter >> iline;
			iline++;
			converter.clear();
			converter << iline;
			converter >> line;
			//tora to line auksithike kata ena.
		}
		else {
			line = "1";
		}
		string log_id = line;
		myline.clear();
		logs.clear(); //katharizw to output stream
		myline = log_id + "|" + origin + "|" + user + "|" + outcome + "|";
		logs << endl << myline;
		logs.close();
		return true;
	}
	else {
		cout << "Error, cannot open log file." << endl;
		logs.close();
	}
}