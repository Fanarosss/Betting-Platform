#include "stdafx.h"
#include "hierarchy.h"
#include "BetAtzis.h"

using namespace std;


//CONSTRUCTORS

Node::Node(int ID, string NAME) {
	id = ID;
	name = NAME;
	//cout<<"A Node has been constructed."<<endl;
}

Home::Home() :Node(0,"Home"){
	set_location("/BetAtzis");
	set_back(NULL);
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

Selection::Selection(int ID, string NAME, string PROFIT) :Node(ID, NAME) {
	profit = PROFIT;
	voided = 0;
	result = "-";
	//cout<<"A Selection has been constructed."<<endl;
}


//DESTRUCTORS

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


//SET_LOCATION

void Home::set_location(string LOCATION) {
	Node::set_location(LOCATION);
}

void Category::set_location(string LOCATION) {
	string location, name;
	Node* temp = get_back();					//pointer to previous node
	temp->get_location(location);				//take the location until the previous node
	location.append("/");
	get_name(name);
	location.append(name);						//add to the location the name of the current location
	Node::set_location(location);				//set the new current location
}

void Subcategory::set_location(string LOCATION) {
	string location, name;
	Node* temp = get_back();
	temp->get_location(location);
	location.append("/");
	get_name(name);
	location.append(name);
	Node::set_location(location);
}

void Event::set_location(string LOCATION) {
	string location, name;
	Node* temp = get_back();
	temp->get_location(location);
	location.append("/");
	get_name(name);
	location.append(name);
	Node::set_location(location);
}

void Market::set_location(string LOCATION) {
	string location, name;
	Node* temp = get_back();
	temp->get_location(location);
	location.append("/");
	get_name(name);
	location.append(name);
	Node::set_location(location);
}

void Selection::set_location(string LOCATION) {
	string location, name;
	Node* temp = get_back();
	temp->get_location(location);
	location.append("/");
	get_name(name);
	location.append(name);
	Node::set_location(location);
}


//INITIALIZATION OF VECTORS INSIDE NODES

Category* Home::set_category(string NAME) {
	Category * ctg_ptr;
	ctg_ptr = new Category(Categories.size()+1,NAME);	//Categories.size + 1 = ID
	Categories.push_back(ctg_ptr);						//add the new category to home's vector
	return ctg_ptr;
}

Subcategory* Category::set_subcategory(string NAME) {
	Subcategory * sctg_ptr;
	sctg_ptr = new Subcategory(Subcategories.size()+1, NAME); 
	Subcategories.push_back(sctg_ptr);
	return sctg_ptr;
}

Event* Subcategory::set_event(string NAME,string DATE_TIME) {
	Event * event_ptr;
	event_ptr = new Event(Events.size()+1, NAME, DATE_TIME); 
	Events.push_back(event_ptr);
	return event_ptr;
}

Market* Event::set_market(string NAME) {
	Market * mrk_ptr;
	mrk_ptr = new Market(Markets.size()+1, NAME); 
	Markets.push_back(mrk_ptr);
	return mrk_ptr;
}

Selection* Market::set_selection(string NAME,string profit, bool voided) {
	Selection * sl_ptr;
	sl_ptr = new Selection(Selections.size()+1, NAME, profit);
	Selections.push_back(sl_ptr);
	if (voided) sl_ptr->set_voided();
	return sl_ptr;
}


//PRINT_OPTIONS

void Home::print_options(int type) {
	for (int i = 0; i < Categories.size(); i++) { 
		bool hidden = Categories[i]->get_visibility();			//flag to see if the node is hidden
		if (hidden == 1) {										//if it is then don't show this option to punter
			if (type != 1) {									//trader and director can see it as hidden
				cout << "[Hidden]";
				Categories[i]->print_id();
				cout << ". ";
				Categories[i]->print_name();
				cout << endl;
			}
		}
		else {													//if it is not show to everyone
			Categories[i]->print_id();
			cout << ". ";
			Categories[i]->print_name();
			cout << endl;
		}
	}
}

void Category::print_options(int type) {
	for (int i = 0; i < Subcategories.size(); i++) {
		bool hidden = Subcategories[i]->get_visibility();
		if (hidden == 1) {
			if (type != 1) {
				cout << "[Hidden]";
				Subcategories[i]->print_id();
				cout << ". ";
				Subcategories[i]->print_name();
				cout << endl;
			}
		}
		else {
			Subcategories[i]->print_id();
			cout << ". ";
			Subcategories[i]->print_name();
			cout << endl;
		}
	}
}

void Subcategory::print_options(int type) {
	for (int i = 0; i < Events.size(); i++) {
		bool hidden = Events[i]->get_visibility();
		if (hidden == 1) {
			if (type != 1) {
				cout << "[Hidden]";
				Events[i]->print_id();
				cout << ". ";
				Events[i]->print_name();
				Events[i]->print_date_time();
				cout << endl;
			}
		}
		else {
			Events[i]->print_id();
			cout << ". ";
			Events[i]->print_name();
			Events[i]->print_date_time();
			cout << endl;
		}
	}
}

void Event::print_options(int type) {
	for (int i = 0; i < Markets.size(); i++) {
		bool hidden = Markets[i]->get_visibility();
		if (hidden == 1) {
			if (type != 1) {
				cout << "[Hidden]";
				Markets[i]->print_id();
				cout << ". ";
				Markets[i]->print_name();
				cout << endl;
			}
		}
		else {
			Markets[i]->print_id();
			cout << ". ";
			Markets[i]->print_name();
			cout << endl;
		}
	}
}

void Market::print_options(int type) {
	for (int i = 0; i < Selections.size(); i++) {
		bool hidden = Selections[i]->get_visibility();
		if (hidden == 1) {
			if (type != 1) {
				cout << "[Hidden]";
				Selections[i]->print_id();
				cout << ". ";
				Selections[i]->print_name();
				cout << " #";
				Selections[i]->print_profit();					
				if (Selections[i]->get_voided() == 1) {			//if selection is voided print it
					cout << " (VOIDED)";
				}
				cout << endl;
			}
		}
		else {
			Selections[i]->print_id();
			cout << ". ";
			Selections[i]->print_name();
			cout << " #";
			Selections[i]->print_profit();
			if (Selections[i]->get_voided() == 1) {
				cout << " (VOIDED)";
			}
			cout << endl;
		}
	}
}


//PLACE (function for punters to place bets)

void Market::place(BetAtzis* Interface) {
	User* user = Interface->get_user();
	user->place(*Interface);
}


//find a node from its id

Node * Home::get_node_byid(string id)								//find every single number and finally the node itself
{ //following the same block 5 times. Decided not to work in a big for loop since the nodes are just 5.
	//also decided to work with 5 converters (stringstreams) and not just one(because of .clear())
	string node_id = id, node_id2 = id, node_id3 = id, node_id4 = id, node_id5 = id;
	size_t pos, pos2;
	int digit_node_id; //extracting one by one the numbers from full id
	Node * ptr;

	pos = node_id.find(".");										//first dot
	node_id.erase(node_id.begin() + pos, node_id.end()); //deleting all content from the node i want to end.
	stringstream converter(node_id); //converting node id frorm string to int digit node id
	converter >> digit_node_id;
	ptr = get_next(digit_node_id); //starting from home and going to digit_node_id category
	converter.clear();

	for (int j = 0; j < 1; j++) {
		pos2 = node_id2.find("."); //extracting the second node id
		node_id2 = node_id2.substr(pos2 + 1); //substracting the left part from the "." that was found
	}
	pos = node_id2.find(".");										//second dot
	node_id2.erase(node_id2.begin() + pos, node_id2.end());
	stringstream converter2;
	converter2 << node_id2;
	converter2 >> digit_node_id;
	ptr = ptr->get_next(digit_node_id); //going from category to digit node id subcategory
	converter2.clear();


	for (int j = 0; j < 2; j++) {
		pos2 = node_id3.find(".");
		node_id3 = node_id3.substr(pos2 + 1);
	}
	pos = node_id3.find(".");										//third dot
	node_id3.erase(node_id3.begin() + pos, node_id3.end());
	stringstream converter3(node_id3);
	converter3 >> digit_node_id;
	ptr = ptr->get_next(digit_node_id); //from subcategory to event
	converter3.clear();


	for (int i = 0; i<3; i++) {
		pos2 = node_id4.find(".");
		node_id4 = node_id4.substr(pos2 + 1);
	}
	pos = node_id4.find(".");										//fourth dot
	node_id4.erase(node_id4.begin() + pos, node_id4.end());
	stringstream converter4(node_id4);
	converter4 >> digit_node_id;
	ptr = ptr->get_next(digit_node_id); //from event to market
	converter4.clear();


	for (int i = 0; i<4; i++) {
		pos2 = node_id5.find(".");
		node_id5 = node_id5.substr(pos2 + 1);
	}
	stringstream converter5(node_id5);
	converter5 >> digit_node_id;
	ptr = ptr->get_next(digit_node_id); // from market to selection
	converter5.clear();
	return ptr;
}


//CONVERSIONS

string Category::conversion() { //use this function to take all the parts and combine them together to return the full string that has to be put in the file
	string id = get_full_id(); //get full id of current node in a string
	string name = Node::get_name(); //calling superclass function in order to get the name
	string visibility;
	if (get_visibility()==1) { //if visibility = 1 the node is hidden. The visibility data is stored in Node.
		visibility = "[HIDDEN]";
	}
	else {
		visibility.clear();
	}
	string node_cat = visibility + id + "." + " " + name; //if visibility is empty nothing changes in string node_cat;
	return node_cat;
}

string Subcategory::conversion() { //same as above with all the other conversion
	string id = get_full_id();
	string name = Node::get_name();
	string visibility;
	if (get_visibility()==1) {
		visibility = "[HIDDEN]";
	}
	else {
		visibility.clear();
	}
	string node_subcat = visibility + id + " " + name;
	return node_subcat;
}

string Event::conversion() {
	string id = get_full_id();
	string name = Node::get_name();
	string visibility;
	if (get_visibility()==1) {
		visibility = "[HIDDEN]";
	}
	else {
		visibility.clear();
	}
	string node_event = visibility + id + " " + name + " " + date_time;
	return node_event;
}

string Market::conversion() {
	string id = get_full_id();
	string name = Node::get_name();
	string visibility;
	if (get_visibility()==1) {
		visibility = "[HIDDEN]";
	}
	else {
		visibility.clear();
	}
	string node_market = visibility + id + " " + name;
	return node_market;
}

string Selection::conversion() {
	string id = get_full_id();
	string name = Node::get_name();
	string visibility;
	if (get_visibility()==1) {
		visibility = "[HIDDEN]";
	}
	else {
		visibility.clear();
	}
	string node_selection = visibility + id + " " + name + "#" + profit;
	if (voided) {
		node_selection += "(VOIDED)";
	}
	return node_selection;
}