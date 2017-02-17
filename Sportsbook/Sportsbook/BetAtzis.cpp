#include "stdafx.h"
#include "BetAtzis.h"

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
					Cptr = cptr;
					break; }
			case 2: {Subcategory* scptr = Cptr->set_subcategory(name);
					SCptr = scptr;
					break; }
			case 3: {size_t pos;
					time = name;
					pos = time.find(" ");
					time = time.substr(pos + 1);
					size_t length = time.length();
					name.erase((name.begin() + (name.length() - length + 1)), name.end());
					Event* eptr = SCptr->set_event(name, time);
					Eptr = eptr;
					break; }
			case 4: {Market* mptr = Eptr->set_market(name);
					Mptr = mptr;
					break; }
			case 5: {string profit = name;
					pos = profit.find("#");
					profit = profit.substr(pos + 1);
					Selection* sptr = Mptr->set_selection(name, profit);
					Sptr = sptr;
					break; }
			}
	} while (!HierLine.empty() && !hierarchy.eof());
}

BetAtzis::~BetAtzis() {
	//cout << "System destroyed" << endl;
}