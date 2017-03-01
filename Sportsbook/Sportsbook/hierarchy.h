#pragma once

#include "stdafx.h"
//#include "BetAtzis.h"//

using namespace std;

class BetAtzis;

class Node {
	int id;
	string name;
	string location;
	Node* back;
public:
	Node(int ID, string NAME);
	virtual ~Node();
	inline void set_id(int ID) { id = ID; }
	inline void get_id(int &ID) { ID = id; }
	inline void print_id() { cout << id; }
	inline void set_name(string NAME) { name = NAME; }
	inline void get_name(string &NAME) { NAME = name; }
	inline void print_name() { cout << name; }
	inline void set_back(Node* NODE) { back = NODE; } //deikths ston proigoymeno komvo//
	inline Node* get_back() { return back; }
	virtual Node* get_next(int NEXT) { return NULL; } //epistrefei ton komvo tou vector poy deixnei o ari8mos NEXT
	virtual string get_full_id() { return NULL; }
	virtual void set_location(string LOCATION) { location = LOCATION; }
	virtual void get_location(string &LOCATION) { LOCATION = location; }
	virtual void print_location() { cout << location << endl; }
	virtual void set_date_time(string DATE_TIME) {}
	virtual void get_date_time(string &DATE_TIME) {}
	virtual void print_date_time() {}
	virtual void set_profit(string PROFIT) {}
	virtual void get_profit(string &PROFIT) {}
	virtual void print_profit() {}
	virtual void print_options() {}
	virtual int get_vector_size() { return 0; }
	virtual bool is_operation_valid(string operation) { return false; }
	virtual void place(BetAtzis* Interface) { cout << "Cannot place bet in this node. You have to go the market" << endl; }
};

class Selection : public Node {
	string profit;
public:
	Selection(int ID, string NAME, string profit);
	~Selection();
	void set_location(string LOCATION);
	void set_profit(string PROFIT) {
		profit = PROFIT;
	}
	void get_profit(string &PROFIT) {
		PROFIT = profit;
	}
	void print_profit() {
		cout << profit;
	}
	string get_full_id() {
		Node* node = get_back();
		string cur_id = node->get_full_id();
		int id;
		get_id(id);
		stringstream sid;
		sid << id;
		string this_id = sid.str();
		cur_id += "." + this_id;
		return cur_id;
	}
};

class Market : public Node {
	vector<Selection*> Selections;
public:
	Market(int ID, string NAME);
	~Market();
	void set_location(string LOCATION);
	Selection* set_selection(string, string);
	void print_options();

	Node* get_next(int NEXT) {
		return Selections[NEXT - 1];
	}

	bool is_operation_valid(string operation) {
		int oprtion = 0, i = 0;
		if ((operation == "Cancel") || (operation == "cancel")) {
			return true;
		}
		for (i = 0; i < Selections.size(); i++) {
			stringstream converter(operation);
			converter >> oprtion;
			if (oprtion == i) {
				return true;
			}
		}
		return false;
	}
	string get_full_id() {
		Node* node = get_back();
		string cur_id = node->get_full_id();
		int id;
		get_id(id);
		stringstream sid;
		sid << id;
		string this_id = sid.str();
		cur_id += "." + this_id;
		return cur_id;
	}
	int get_vector_size() {
		return Selections.size();
	}
	void place(BetAtzis* Interface);
};

class Event : public Node {
	string date_time;
	vector<Market*> Markets;
public:
	Event(int ID, string NAME, string DATE_TIME);
	~Event();
	void set_location(string LOCATION);
	Market* set_market(string);
	void set_date_time(string DATE_TIME) {
		date_time = DATE_TIME;
	};
	void get_date_time(string &DATE_TIME) {
		DATE_TIME = date_time;
	};
	void print_date_time() {
		cout << date_time;
	};
	void print_options();
	Node* get_next(int NEXT) {
		return Markets[NEXT - 1];
	};
	string get_full_id() {
		Node* node = get_back();
		string cur_id = node->get_full_id();
		int id;
		get_id(id);
		stringstream sid;
		sid << id;
		string this_id = sid.str();
		cur_id += "." + this_id;
		return cur_id;
	}
	int get_vector_size() {
		return Markets.size();
	}
};

class Subcategory : public Node {
	vector<Event*> Events;
public:
	Subcategory(int ID, string NAME);
	~Subcategory();
	void set_location(string LOCATION);
	Event* set_event(string, string);
	void print_options();
	Node* get_next(int NEXT) {
		return Events[NEXT - 1];
	};
	string get_full_id() {
		Node* node = get_back();
		string cur_id = node->get_full_id();
		int id;
		get_id(id);
		stringstream sid;
		sid << id;
		string this_id = sid.str();
		cur_id += "." + this_id;
		return cur_id;
	}
	int get_vector_size() {
		return Events.size();
	}
};

class Category : public Node {
	vector<Subcategory*> Subcategories;
public:
	Category(int ID, string NAME);
	~Category();
	void set_location(string LOCATION);
	Subcategory* set_subcategory(string);
	void print_options();
	Node* get_next(int NEXT) {
		return Subcategories[NEXT - 1];
	};
	string get_full_id() {
		int id;
		get_id(id);
		stringstream sid;
		sid << id;
		string cur_id = sid.str();
		return cur_id;
	}
	int get_vector_size() {
		return Subcategories.size();
	}
};

class Home : public Node {
	vector<Category*> Categories;
public:
	Home();
	~Home();
	void set_location(string LOCATION);
	Category* set_category(string);
	void print_options();
	Node* get_next(int NEXT) {
		return Categories[NEXT - 1];
	}
	int get_vector_size() {
		return Categories.size();
	}
};
