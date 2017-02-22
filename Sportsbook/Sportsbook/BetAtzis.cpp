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
		size_t position = name.find(" ");
		name = name.substr(position + 1); //svinei tous arithmous kai to space
		switch (NodeCounter) {
			case 1: {Category* cptr = home->set_category(name);
					cptr->set_back(home);
					cptr->set_location("");
					Cptr = cptr;
					break; }
			case 2: {Subcategory* scptr = Cptr->set_subcategory(name);
					scptr->set_back(Cptr);
					scptr->set_location("");
					SCptr = scptr;
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
					break; }
			case 4: {Market* mptr = Eptr->set_market(name);
					mptr->set_back(Eptr);
					mptr->set_location("");
					Mptr = mptr;
					break; }
			case 5: {string profit = name;
					pos = profit.find("#");
					profit = profit.substr(pos + 1);
					size_t length = profit.length();
					name.erase((name.begin() + (name.length() - length - 1)), name.end());
					Selection* sptr = Mptr->set_selection(name, profit);
					sptr->set_back(Mptr);
					sptr->set_location("");
					Sptr = sptr;
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
			case 1: users.push_back(new Punter(extract_username(suser), extract_password(suser), extract_fullname(suser),extract_balance(suser)));
				break;
			case 2: users.push_back(new Trader(extract_username(suser), extract_password(suser), extract_fullname(suser)));
				break;
			case 3: users.push_back(new Director(extract_username(suser), extract_password(suser), extract_fullname(suser)));
				break;
			}
			getline(Users, suser); //sto telos gia na mpainei ston elegxo toy while gia eof and empty
		}

	}
	else {
		cout << "Error opening file users.csv " << endl;
	}
	Users.close();
}

bool BetAtzis::operation(string op, BetAtzis* interface) {
	bool OP = user->Operation(op, *interface);
	return OP;
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
	double balance; //now appuser equals to username; pass it throught only for clarity issues.
	stringstream converter(appuser);
	converter >> balance;
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

//functions for vector changes

void set_new_username(string OLD, string NEW) {
	User* user = NULL;
	for(int i=0; i<=users.)
}