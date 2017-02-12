#pragma once

#include "stdafx.h"

class Node {

};

class Category : public Node {
	int id;
	vector<Subcategory> Subcategories;
};

class Subcategory : public Category {
	int id;
};

class Event : public Subcategory {
	int id;
	std::string name;
	std::string date;
	std::string time;

};

class Market : public Event {
	int id;
	Selection ** selection_menu;
};

class Price {
	double price;
};

class Selection : public Market {
	int id;
	Price apodosi;
};