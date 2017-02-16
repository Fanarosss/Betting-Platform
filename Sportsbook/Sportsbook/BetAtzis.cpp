#include "stdafx.h"
#include "BetAtzis.h"

using namespace std;

BetAtzis::BetAtzis() {
	fstream hierarchy("hierarchy.dat", std::fstream::in);
	//read from hierarchy.dat and create the categeories in home, subcategories in categories etc.
	string HierLine,temp,name,time;
	short int NodeCounter = 0;
	Category* Cptr = NULL;
	Subcategory* SCptr = NULL;
	Event* Eptr = NULL;
	Market* Mptr = NULL;
	Selection* Sptr = NULL;
	do{
		getline(hierarchy, HierLine);
		temp = HierLine;
		size_t pos;
		pos = temp.find(" ");
		temp.erase((temp.begin() + pos), temp.end()); //adeiazo to temp apo ta ipoloipa
		while (!temp.empty()) {
			if (pos = temp.find(".") != string::npos) {
				NodeCounter++;
				cout << temp << endl; //debugging
				temp = temp.substr(pos + 1);
				cout << temp << endl; //debugging
			}
			else if (temp.length() < 3) {
				NodeCounter++;
				temp.clear();
				}
		}
		cout << "exited" << endl;
		if (NodeCounter > 1) {
			NodeCounter++;
		}
		name = HierLine;
		size_t position = name.find(" ");
		name.substr(position + 1); //svinei tous arithmous kai to space
		switch (NodeCounter) {
			case 1: {Category * cptr = home.set_category(name);
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
					pos = profit.find(" ");
					profit = profit.substr(pos + 1);
					Selection * sptr = Mptr->set_selection(name, profit);
					Sptr = sptr;
					break; }
			}
	} while (!HierLine.empty() && !hierarchy.eof());
}

BetAtzis::~BetAtzis() {
	//cout << "System destroyed" << endl;
}