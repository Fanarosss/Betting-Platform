#include "stdafx.h"
#include "BetAtzis.h"

using namespace std;

BetAtzis::BetAtzis() {
	fstream hierarchy("hierarchy.dat", std::fstream::in);
	//read from hierarchy.dat and create the categeories in home, subcategories in categories etc.
	string HierLine,temp,name,time;
	while (!hierarchy.eof()) {
		getline(hierarchy, HierLine);
		short int NodeCounter=0;
		temp = HierLine;
		temp.erase((temp.begin() + 1), temp.end());
		while (temp != " ") {
			NodeCounter++;
			name = HierLine;
			size_t position = name.find(" ");
			name.substr(position + 1); //svinei tous arithmous kai to space
			switch (NodeCounter) {
				case 1: Category * cptr = home.set_category(name);
						break;
				case 2: Subcategory* scptr = cptr->set_subcategory(name);
						break;
				case 3: size_t pos;
						time = name;
						pos = time.find("#");
						time = time.substr(pos + 1);
						int length = time.length();
						name.erase((name.begin() + (name.length() - length + 1)),name.end());
						Event* evptr = scptr->set_event(name, time);
						break;
				case 4: Market* market_ptr = 
			}
			temp = HierLine;
			temp.erase((temp.begin() + 1), temp.end());
		}
	}
}

BetAtzis::~BetAtzis() {
	//cout << "System destroyed" << endl;
}