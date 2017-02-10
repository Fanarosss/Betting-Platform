// Sportsbook.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"

using namespace std;

int main(int argc, char *argv[])
{
	//for starters we are not going to use the preprocessing #ifdef, but remain in a known environment of argv,argc
	char parameter = atof(argv[0]);
	// Eggrafi part
	if (parameter == 'R') {
		bool registration_flag = true;
		string username, password, appuser;
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
	}
	// end of eggrafi!
    return 0;
}

