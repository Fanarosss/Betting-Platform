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
	bool visibility;
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
	virtual void print_options(int type) {}
	virtual int get_vector_size() { return 0; }
	virtual void set_result(string rslt){}
	virtual string get_result() { return NULL; }
	virtual bool get_voided() { return 0; }  //mono gia selection
	virtual void set_voided(){}	 //mono gia selection
	virtual bool is_operation_valid(string operation) { return false; }
	virtual void place(BetAtzis* Interface) { cout << "Cannot place bet in this node. You have to go the market" << endl; }
	virtual Node* get_selection_ptr(int selection_id) { return NULL; }
	virtual Node * get_node_byid(string id) { return NULL; }
	virtual string conversion() { return NULL; }
	string get_name() { return name; }
	void set_visibility(bool hidden) { visibility = hidden; }
	void set_visibility() { visibility = !visibility;  } //overloaded function for set_visibility of betatzis
	bool get_visibility() { return visibility; }
};

class Selection : public Node {
	string profit;
	bool voided;
	string result;
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
	void set_result(string rslt) {
		result = rslt;
	}
	string get_result() {
		return result;
	}
	void set_voided() { voided = 1; }
	bool get_voided() { return voided; }
	string get_full_id() {
		Node* node = get_back();
		string cur_id = node->get_full_id(); //mipos thelei += ???to arxikopoieis se mia timi to auksaneis, kai meta ksana to arxikopoieis
		int id;
		get_id(id);
		stringstream sid;
		sid << id;
		string this_id = sid.str();
		cur_id += "." + this_id;
		return cur_id;
	}
	string conversion();
};

class Market : public Node {
	vector<Selection*> Selections;
public:
	Market(int ID, string NAME);
	~Market();
	void set_location(string LOCATION);
	Selection* set_selection(string, string,bool);
	void print_options(int type);
	string conversion();

	Node* get_next(int NEXT) {
		return Selections[NEXT - 1];
	}

	bool is_operation_valid(string operation) {
		int option = 0, i = 0;
		if ((operation == "Cancel") || (operation == "cancel")) {
			return true;
		}
		for (i = 0; i < Selections.size(); i++) {
			stringstream converter(operation);
			converter >> option;
			if (option == (i + 1)) {
				if (Selections[i]->get_voided() == 0) {			//elegxos an h epilogh exei akurw8ei
					return true;
				}
				else {
					cout << "You cannot place a bet in a voided selection." << endl;
					return false;
				}
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

	Node* get_selection_ptr(int selection_id) { return Selections[selection_id - 1]; }
};

class Event : public Node {
	string date_time;
	vector<Market*> Markets;
public:
	Event(int ID, string NAME, string DATE_TIME);
	~Event();
	void set_location(string LOCATION);
	Market* set_market(string);
	string conversion();
	void set_date_time(string DATE_TIME) {
		date_time = DATE_TIME;
	};
	void get_date_time(string &DATE_TIME) {
		DATE_TIME = date_time;
	};
	void print_date_time() {
		cout << date_time;
	};
	void print_options(int type);
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
	string conversion();
	void print_options(int type);
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
	string conversion();
	void print_options(int type);
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
	void print_options(int type);
	Node* get_next(int NEXT) {
		return Categories[NEXT - 1];
	}
	int get_vector_size() {
		return Categories.size();
	}
	Node * get_node_byid(string id);
};
