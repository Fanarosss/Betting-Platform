#pragma once

#include "stdafx.h"

using namespace std;

class Node {

};

class Category : public Node {
	int id;
	vector<Subcategory> Subcategories;
};

class Subcategory : public Category {
	int id;
	vector<Event> Events;
};

class Event : public Subcategory {
	int id;
	vector<Market> Markets;
	string name;
	string date;
	string time;

};

class Market : public Event {
	int id;
	vector<Selection> Selections;
	Selection ** selection_menu;
};

class Price {
	double price;
};

class Selection : public Market {
	int id;
	Price apodosi;
};