#pragma once

#include "stdafx.h"

class Node {

};

class Category : public Node {

};

class Subcategory : public Category {

};

class Event {
	std::string name;
	std::string date;
	std::string time;

};

class Market {
	Selection ** selection_menu;
};

class Price {
	double price;
};

class Selection {
	Price apodosi;
};