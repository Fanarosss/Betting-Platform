// Sportsbook.cpp : Defines the entry point for the console application.
////

#include "stdafx.h"
#include "Users_categories.h"
#include "Main_functions.h"
#include "hierarchy.h"
#include "BetAtzis.h"

using namespace std;

int main(int argc, char *argv[])
{
	string username, password, appuser;
	string parameter;
	if (argv[1] != NULL) { //checking for -R
		parameter = argv[1];
	}
	bool registration_flag = true;
	// Registration part
	if (parameter == "-R") {
		cout << "<username> ";
		cin >> username;
		fstream file("users.csv", std::fstream::in);
		if (file.is_open()) {
			getline(file, appuser); 
			while (!appuser.empty() && !file.eof()) { //searching for username in the file
				size_t pos1, pos2;
				pos1 = appuser.find("|");
				appuser = appuser.substr(pos1 + 1);
				pos2 = appuser.find("|");
				appuser = appuser.erase(pos2);
				if ((appuser.compare(username) == 0)) { //this takes the line and check if there is a word in there mathcing to the given username
					cout << "There is already a register with that username!" << endl;
					registration_flag = false;
					file.close();
					return 0;
				}
				getline(file, appuser);
			}
			file.close();
			cout << "<password> ";
			cin >> password;
			cout << "Please enter your full name: ";
			string fullname;
			cin >> fullname;
			cout << endl;
			cout << "Registration succesfull" << endl;
			cin.get();
			string last_appuser;
			file.open("users.csv", std::fstream::in);
			do {
				last_appuser = appuser;
				getline(file, appuser); //until it reaches the last line
			} while (!appuser.empty() && !file.eof());
			string last_app;
			if (appuser.empty()) {
				last_app = last_appuser; //in case that files has an extra /n with an empty string
			}
			else {
				last_app = appuser;
			}
			int id;
			last_app.erase((last_app.begin() + 1), last_app.end()); 
			if (last_app.compare("u") || last_app.compare("U")) { //if last line is the title user_id|... etc. means that there are no users -> so user_id =1;
				if (appuser.empty()) {
					id = get_id(last_appuser);
				}
				else {
					id = get_id(appuser);
				}
				id++; //current user id
			}
			else {
				id = 1;
			}
			stringstream converter; //using sstream for conversions from string to int,double and the opposite.
			converter.clear();
			converter << id;
			string sid;
			converter >> sid;
			string stype;
			stringstream converter2; //same with above
			converter2.clear();
			converter2 << 1;
			converter2 >> stype;
			file.close();
			file.open("users.csv", std::fstream::out | std::fstream::app); //using fstream::out to write and fstream::app in order to append in the end of file, and NOT to overwrite it.
			string new_user;
			new_user = sid + "|" + username + "|" + fullname + "|" + password + "|" + stype + "|" + "-" + "|" + "-" + "|" + "-" + "|";
			file << endl << new_user;
			file.close();
		}
		else {
			cout << "Can't open file.";
			return 0;
		}
	}
	// end of registration!


	cout << "Welcome to sportsbook" << endl << "Please enter your username and password for signing in. If you don't have an account please press enter, or type guest. " << endl;
	registration_flag = false; //Considering that the user is not yet registered
	string status; //checking for the user status
	User * uptr = NULL;
	cout << "Username: ";
	getline(cin, username); //using getline to read in case of hitting enter('/n'), and logging in as guest
	bool guest = false;
	if ((username != "guest")&&(!username.empty())) {
		fstream file("users.csv", std::fstream::in);
		if (file.is_open()) {
			while (!file.eof() || appuser.empty()) {
				getline(file, appuser);
				//delete all the useless parts of the line, and keep only the username.
				size_t pos1, pos2; 
				pos1 = appuser.find("|"); //returns -1 if it doesn't find "|", find() starts searching from the begining of the string and stops at the first "|" where it returns it's position.
				appuser = appuser.substr(pos1 + 1); //substract all the left part of the string. using + 1 to substract the "|" too.
				pos2 = appuser.find("|"); //same;
				appuser = appuser.erase(pos2);
				if (appuser.compare(username) == 0) { //if there is a registration with that username
					registration_flag = true;
					status = get_status(username);
					pos1 = status.find(",");
					if (pos1!=std::string::npos) { //npos is used to indicate failure, in our case failure of find. If we didnt use this, there would be a segmentation fault.(undefined behaviour)
						status.erase(status.begin() + pos1, status.end()); //because here it will try to delete from status.begin() - 1.
					}
					break; //break the loop as the username was found inside the file. Now the user will have to enter the password.
				}
			}
			if (registration_flag == false) {
				cout << "There is no register with that username. Please try again! " << endl;
				return 0;
			}
			if (status == "L") {
				cout << "You cannot sign in. This user is locked." << endl;
				return 0;
			}
			cout << "Password: ";
			cin >> password;
			cout << endl;
			bool is_password_correct = check_for_password(username, password); //function that looks if the password that is given is correct
			if (is_password_correct == true) {
				cout << "You have been logged in to the system succesfully" << endl;
			}
			else {
				cout << "Password incorrect. Please try again!" << endl;
				return 0;
			}
		} 
		else {
			cout << "User files are missing. End of program!";
			return 0;
		}
	}
	else {
		cout << "Logged in as guest" << endl;
		uptr = new Guest;
		guest = true;
	}
	BetAtzis* Interface = new BetAtzis;
	if (guest == false) {
		uptr = Interface->current_user(username);
	}
	Interface->set_user(uptr);
	bool flag = true;
	string operation;
	do {
		cout << endl << "Location: ";
		Interface->print_location(); //prints the current location.
		Interface->print_options(); //prints the node that we can access
		Interface->print_operations(Interface); //prints the user operations
		cin >> operation;
		if ((isdigit(operation[0]) == 0)) {
			flag = Interface->operation(operation, Interface);
		}
		else {
			int choice;
			if (!(istringstream(operation) >> choice)) choice = 0; //converting operation from string to int in order to access the node
			Interface->set_level(choice);
		}
	} while (flag == true);
	return 0;
}