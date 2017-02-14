#include "stdafx.h"
#include "BetAtzis.h"

using namespace std;

BetAtzis::BetAtzis() {
	fstream hierarchy("hierarchy.dat", std::fstream::in);
	//read from hierarchy.dat and create the categeories in home, subcategories in categories etc.
	string HierLine;
	while (!hierarchy.eof()) {
		getline(hierarchy, HierLine);

	}
}

BetAtzis::~BetAtzis() {
	//cout << "System destroyed" << endl;
}