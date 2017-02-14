#include "stdafx.h"
#include "BetAtzis.h"

using namespace std;

BetAtzis::BetAtzis() {
	fstream hierarchy("hierarchy.dat", std::fstream::in);
	//read from hierarchy.dat and create the categeories in home, subcategories in categories etc.
	string HierLine,temp,name,time;
	short int NodeCounter = 1;
	while (!hierarchy.eof()) {
		getline(hierarchy, HierLine);
		temp = HierLine;
		size_t pos;
		pos = temp.find(" ");
		temp.erase(temp.begin() + pos, temp.end()); //adeiazo to temp apo ta ipoloipa
		while (temp != " ") {
			if (temp.find(".") != string::npos) {
				NodeCounter++;
				temp.substr(temp.find(".") + 1);
			}
		}
		NodeCounter += 2;
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
						pos = time.find(" ");
						time = time.substr(pos + 1);
						int length = time.length();
						name.erase((name.begin() + (name.length() - length + 1)),name.end());
						Event* evptr = scptr->set_event(name, time);
						break;
			case 4: Market* market_ptr = evptr->set_market(name);
						break;
			case 5: string profit = name;
						pos = profit.find(" ");
						profit = profit.substr(pos + 1);
						Selection * slptr = market_ptr->set_selection(name,profit);
						break;
			}
	}
}

BetAtzis::~BetAtzis() {
	//cout << "System destroyed" << endl;
}