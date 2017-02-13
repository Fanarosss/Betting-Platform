// Sportsbook.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "Users_categories.h"
#include "Main_functions.h"

using namespace std;

int main(int argc, char *argv[])
{
	//for starters we are not going to use the preprocessing #ifdef, but remain in a known environment of argv,argc
	string parameter = argv[1];
	string username, password, appuser;
	bool registration_flag = true;
	// Eggrafi part
	// #ifdef -R    // preproccesing compilation of registration part
	if (parameter.compare("-R")) {
		cout << "<username>" << endl << "<password>" << endl;
		cin >> username;
		cout << endl;
		cin >> password;
		fstream file("users.csv", std::fstream::in);
		if (file.is_open()) {
			while (!file.eof()) {
				getline(file, appuser); //this takes the line and put it to string appuser
				if ((appuser.find(username, 0)) != string::npos) { //this takes the line and check if there is a word in there mathcing to the given username
					cout << "There is already a register with that username." << endl;
					file.close(); //to kleinw prin termatisei to programma
					return 0;
				}
			}
			cout << "Please enter your full name" << endl;
			string fullname;
			cin >> fullname;
			cout << "Registration succesfull" << endl;
			string last_appuser = appuser;
			while (!file.eof) {
				getline(file, last_appuser); //mexri na ftasei stin teleutaia grammi
			}
			string sid = read_from_csv(1, last_appuser); //tote diavazei to teleutaio id
			stringstream converter(sid); //converting from string to int
			int id = 0;
			converter >> id; //now we know the last id
			id++;
			sid = to_string(id);
			string stype = to_string(1);
			file.close();
			file.open("users.csv", std::fstream::out);
			string new_user;
			new_user = id + "|" + username + "|" + fullname + "|" + password + "|" + stype + "|" + "-" + "|" + "-" + "|" + "-" + "|";
			file << new_user << endl;
			file.close();
		}
		else {
			cout << "Can't open file.";
			return 0;
		}
	}
	// end of registration!
	// #endif 
	cout << "Welcome to sportsbook" << endl << "Please enter your username and password for signing in. If you don't have an account please press enter, or type guest" << endl;
	registration_flag = false; //esto oti o xristis den exei eggrafei akoma
	cout << "Username: ";
	cin >> username;
	if (username != "guest") {
		fstream file("users.csv" , std::fstream::in);
		if (file.is_open()) {
			while (!file.eof()) {
				getline(file, appuser);
				//here will have to be a line where delete all the useless part of the line, and keeps only the username
				if ((appuser.find(username, 0)) != string::npos) {
					registration_flag = true;
					break;
				}
			}
			if (!registration_flag) {
				cout << "There is no register with that username. Please try again! " << endl;
			}
			cout << endl << "Password: ";
			cin >> password;
			cout << endl;
			bool is_password_correct = check_for_password(username); //sinartisi pou psaxnei an to password einai to sosto gia to username pou exei dothei
			if (is_password_correct == true) {
				cout << "You have been logged in to the system succesfully" << endl;
				//procedure for finding the type
				//type in .csv is the 5th element
				int type_pos = 4;
				int type = read_from_csv(type_pos, appuser);
				//int type = stoi(appuser); //warning!!! c++11 ONLY!!!
				int type;
				stringstream converter(appuser);
				converter >> type;
				if (type == 1) {
					//constructor for punter
				}
				else if (type == 2) {
					//constructor for trader
				}
				else if (type == 3) {
					//constructor for director
				}
			}
		}
		else {
			cout << "User files are missing. End of program!";
				return 0;
		}
	} //else -> an telika ekane type guest os username!!! --> xreiazetai enchancement na erxetai edo kai an apla pataei enter !!! <--
	else { 
		cout << "Logged in as guest" << endl;
	}
	string Location = "/BetAtzis"; //krataei thn 8esh ths ierarxias pou vriskomaste
    return 0;
}
