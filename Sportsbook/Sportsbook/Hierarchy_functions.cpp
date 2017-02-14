#include "stdafx.h"
#include "hierarchy.h"

using namespace std;

Node::Node(int ID, string NAME) {
	id = ID;
	name = NAME;
	//cout<<"A Node has been constructed."<<endl;
}

Home::Home() {
	//cout << "Home has been constructed" << endl;
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

Home::~Home() {
	//cout << "Home will be destroyed."<<endl;
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

//!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
//kosta poli pithanon auti i ylopoiisi na einai lathos, den tin allazw akoma, alla logika thelei to vector na einai sto node me vector < node * > Nodes kai oles oi sinartiseis virtual!

Category* Home::set_category(string NAME) {
	Category * ctg_ptr;
	ctg_ptr = new Category(Categories.size(),NAME); //Categories.size = ID
	Categories.push_back(ctg_ptr);
	return ctg_ptr;
}

Subcategory* Category::set_subcategory(string NAME) {
	Subcategory * sctg_ptr;
	sctg_ptr = new Subcategory(Subcategories.size(), NAME); //vector.size = ID
	Subcategories.push_back(sctg_ptr);
	return sctg_ptr;
}

Event* Subcategory::set_event(string NAME,string DATE_TIME) {
	Event * event_ptr;
	event_ptr = new Event(Events.size(), NAME, DATE_TIME); //vector.size = ID
	Events.push_back(event_ptr);
	return event_ptr;
}

Market* Event::set_market(string NAME) {
	Market * mrk_ptr;
	mrk_ptr = new Market(Markets.size(), NAME); //vector.size = ID
	Markets.push_back(mrk_ptr);
	return mrk_ptr;
}

Selection* Market::set_selection(string NAME,double profit) {
	Selection * sl_ptr;
	sl_ptr = new Selection(Selections.size(), NAME, profit); //vector.size = ID
	Selections.push_back(sl_ptr);
	return sl_ptr;
}