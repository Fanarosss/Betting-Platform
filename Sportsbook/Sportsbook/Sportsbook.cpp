// Sportsbook.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"

using namespace std;

int main(int argc, char *argv[])
{
	//for starters we are not going to use the preprocessing #ifdef, but remain in a known environment of argv,argc
	char parameter = atof(argv[0]);
	string username, password, appuser;
	bool registration_flag = true;
	// Eggrafi part
	if (parameter == 'R') {
		cout << "<username>" << endl << "<password>" << endl;
		cin >> username;
		cout << endl;
		cin >> password;
		int offset;
		fstream file("registrations.csv");
		while (!file.eof()) {
			getline(file, appuser);
			if ((offset = appuser.find(username, 0)) != string::npos) {
				cout << "There is already a register with that username." << endl;
				return 0;
			}
		}
		//this is the part where registration is succesfull, the user logins and his username and password are passed in csv
	}
	// end of eggrafi!
	cout << "Welcome to sportsbook" << endl << "Please enter your username and password for signing in. If you don't have an account please press enter, or type guest" << endl;
	registration_flag = false;
	cout << "Username: ";
	cin >> username;
	if (username != "guest") {
		int offset;
		fstream file("registrations.csv");
		while (!file.eof()) {
			getline(file, appuser);
			if ((offset = appuser.find(username, 0)) != string::npos) {
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
	}
	else {
		cout << "Logged in as guest" << endl;
	}
    return 0;
}

