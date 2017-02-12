// Sportsbook.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "Users_categories.h"
#include "Main_functions.h"

using namespace std;

int main(int argc, char *argv[])
{
	//for starters we are not going to use the preprocessing #ifdef, but remain in a known environment of argv,argc
	char parameter = atof(argv[0]);
	string username, password, appuser;
	bool registration_flag = true;
	// Eggrafi part
	// #ifdef -R    // preproccesing compilation of registration part
	if (parameter == 'R') {
		cout << "<username>" << endl << "<password>" << endl;
		cin >> username;
		cout << endl;
		cin >> password;
		fstream file("users.txt");
		if (file.is_open()) {
			while (!file.eof()) {
				getline(file, appuser); //this takes the line and put it to string appuser
				if ((appuser.find(username, 0)) != string::npos) { //this takes the line and check if there is a word in there mathcing to the given username
					cout << "There is already a register with that username." << endl;
					file.close(); //to kleinw prin termatisei to programma
					return 0;
				}
			}
			cout << "Registration succesfull" << endl;
			//construction call for user class
			//this is the part where registration is succesfull, the user logins and his username and password are passed in csv
		}
		else {
			cout << "Can't open file.";
			return 0;
		}
	}
	// end of eggrafi!
	// #endif 
	cout << "Welcome to sportsbook" << endl << "Please enter your username and password for signing in. If you don't have an account please press enter, or type guest" << endl;
	registration_flag = false; //esto oti o xristis den exei eggrafei akoma
	cout << "Username: ";
	cin >> username;
	if (username != "guest") {
		fstream file("users.txt");
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
			if (is_password_correct) {
				cout << "You have been logged in to the system succesfully" << endl;
				//procedure for finding the type
				//type in .csv is the 5th element
				int type_pos = 4;
				size_t pos;
				for (int i = 0; i<type_pos; i++) {
					pos = appuser.find("|");
					appuser = appuser.substr(pos + 1); //gia na aferesei kai tin pavla mazi
				}
				appuser.erase(appuser.begin() + 1, appuser.end()); //now appuser = type
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
    return 0;
}
