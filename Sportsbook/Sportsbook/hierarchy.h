#pragma once

#include "stdafx.h"

using namespace std;

class Node {
	int id;
	string name;
public:
	Node(int ID, string NAME);
	virtual ~Node();
	inline void set_id(int ID) { id = ID; }
	inline void get_id(int &ID) { ID = id; }
	inline void print_id() { cout << id; }
	inline void set_name(string NAME) { name = NAME; }
	inline void get_name(string &NAME) { NAME = name; }
	inline void print_name() { cout << name; }
	virtual void set_location(string &LOCATION) {};
	virtual void set_date_time(string DATE_TIME) {}
	virtual void get_date_time(string &DATE_TIME) {}
	virtual void print_date_time() {}
	virtual void set_profit(double PROFIT) {}
	virtual void get_profit(double &PROFIT) {}
	virtual void print_profit() {}
};

class Selection : public Node {
	string profit;
public:
	Selection(int ID, string NAME, string profit);
	~Selection();
	void set_location(string &LOCATION);
	void set_profit(string PROFIT) {
		profit = PROFIT;
	};
	void get_profit(string &PROFIT) {
		PROFIT = profit;
	};
	void print_profit() {
		cout << profit;
	};
};

class Market : public Node {
	vector<Selection*> Selections;
public:
	Market(int ID, string NAME);
	~Market();
	void set_location(string &LOCATION);
	Selection* set_selection(string, string);
};

class Event : public Node {
	string date_time;
	vector<Market*> Markets;
public:
	Event(int ID, string NAME, string DATE_TIME);
	~Event();
	void set_location(string &LOCATION);
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
};

class Subcategory : public Node {
	vector<Event*> Events;
public:
	Subcategory(int ID, string NAME);
	~Subcategory();
	void set_location(string &LOCATION);
	Event* set_event(string, string);
};

class Category : public Node {
	vector<Subcategory*> Subcategories;
public:
	Category(int ID, string NAME);
	~Category();
	void set_location(string &LOCATION);
	Subcategory* set_subcategory(string);
};

class Home {
	vector<Category*> Categories;
public:
	Home();
	~Home();
	Category*  set_category(string);
};
