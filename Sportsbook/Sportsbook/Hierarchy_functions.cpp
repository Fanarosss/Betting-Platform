#include "stdafx.h"
#include "hierarchy.h"

using namespace std;

Node::Node(int ID, string NAME) {
	id = ID;
	name = NAME;
	//cout<<"A Node has been constructed."<<endl;
}

Category::Category(int ID, string NAME) :Node(ID, NAME) {
	//cout<<"A Category has been constructed."<<endl;
}

Subcategory::Subcategory(int ID, string NAME) :Node(ID, NAME) {
	//cout<<"A Subcategory has been constructed."<<endl;
}

Event::Event(int ID, string NAME, string DATE_TIME) :Node(ID, NAME) {
	date_time = DATE_TIME;
	//cout<<"An Event has been constructed."<<endl;
}

Market::Market(int ID, string NAME) :Node(ID, NAME) {
	//cout<<"A Market has been constructed."<<endl;
}

Selection::Selection(int ID, string NAME, double PROFIT) :Node(ID, NAME) {
	profit = PROFIT;
	//cout<<"A Selection has been constructed."<<endl;
}

Node::~Node() {
	//cout<<"A Node will be destroyed."<<endl;
}

Category::~Category() {
	//cout<<"A Category will be destroyed."<<endl;
}

Subcategory::~Subcategory() {
	//cout<<"A Subcategory will be destroyed."<<endl;
}

Event::~Event() {
	//cout<<"An Event will be destroyed."<<endl;
}

Market::~Market() {
	//cout<<"A Market will be destroyed."<<endl;
}

Selection::~Selection() {
	//cout<<"A Selection will be destroyed."<<endl;
}

void Category::set_location(string &LOCATION) {
	LOCATION.append("/");
	string location;
	Node::get_name(location);
	LOCATION.append(location);
}

void Subcategory::set_location(string &LOCATION) {
	LOCATION.append("/");
	string location;
	Node::get_name(location);
	LOCATION.append(location);
}

void Event::set_location(string &LOCATION) {
	LOCATION.append("/");
	string location;
	Node::get_name(location);
	LOCATION.append(location);
}

void Market::set_location(string &LOCATION) {
	LOCATION.append("/");
	string location;
	Node::get_name(location);
	LOCATION.append(location);
}

void Selection::set_location(string &LOCATION) {
	LOCATION.append("/");
	string location;
	Node::get_name(location);
	LOCATION.append(location);
}
