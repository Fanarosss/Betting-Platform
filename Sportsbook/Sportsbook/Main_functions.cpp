#include "stdafx.h"
#include "Main_functions.h"

using namespace std;

bool check_for_password(string username) {
	bool is_password_correct;
	//body
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
	string appuser;
	fstream file("users.csv", std::fstream::in);
	while (!file.eof()) {
		getline(file, appuser); //this takes the line and put it to string appuser
		if ((appuser.find(username, 0)) != string::npos) { //this takes the line and check if there is a word in there mathcing to the given username
			break;
		}
	}
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
	stringstream converter(appuser);
	converter >> balance;
	return balance;
}

int get_type(string username) {
	int type;
	string appuser;
	fstream file("users.csv" , std::fstream::in);
	while (!file.eof()) {
		getline(file, appuser); //this takes the line and put it to string appuser
		if ((appuser.find(username, 0)) != string::npos) { //this takes the line and check if there is a word in there mathcing to the given username
			break;
		}
	}
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
	stringstream converter(appuser);
	converter >> type;
	return type;
}

string get_status(string username) {
	string status;
	string appuser;
	fstream file("users.csv", std::fstream::in);
	while (!file.eof()) {
		getline(file, appuser); //this takes the line and put it to string appuser
		if ((appuser.find(username, 0)) != string::npos) { //this takes the line and check if there is a word in there mathcing to the given username
			break;
		}
	}
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
	status = appuser;
	return status;
}

string get_freebets(string username) {
	string freebets;
	string appuser;
	fstream file("users.csv", std::fstream::in);
	while (!file.eof()) {
		getline(file, appuser); //this takes the line and put it to string appuser
		if ((appuser.find(username, 0)) != string::npos) { //this takes the line and check if there is a word in there mathcing to the given username
			break;
		}
	}
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
	appuser = freebets;
	return freebets;
}

int get_id(string username) {
	int id;
	string appuser;
	fstream file("users.csv", std::fstream::in);
	while (!file.eof()) {
		getline(file, appuser); //this takes the line and put it to string appuser
		if ((appuser.find(username, 0)) != string::npos) { //this takes the line and check if there is a word in there mathcing to the given username
			break;
		}
	}
	size_t pos;
	for (int i = 1; i<1; i++) {
		pos = appuser.find("|");
		appuser = appuser.substr(pos + 1); //gia na aferesei kai tin pavla mazi
	} //krataei olo to string deksia apo auto pou psaxnw
	int count_of_string = 0;
	while ((appuser[count_of_string] != '|')) {
		count_of_string++;
	}
	appuser.erase((appuser.begin() + count_of_string), appuser.end()); //now appuser = what im looking for
																	   //svistike kai to deksia
	stringstream converter(appuser);
	converter >> id;
	return id;
}