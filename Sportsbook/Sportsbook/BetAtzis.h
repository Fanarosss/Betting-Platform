#pragma once
#include "Users_categories.h"
#include "stdafx.h"
#include "hierarchy.h"


class BetAtzis {
private:
	long double profits;		// total profits from bets
	double promitheia;			// commission is 0.05
	string type_ofProfits;		// "Klasmatika" or "Dekadika"
	int Current_lvl;			// lvl=0->home, lvl=1->category, lvl=2->subcategory, etc.
	User* user;					// pointer to current user
	Home* home;					// pointer to home page
	Node* node;					// pointer to current node
	vector <User*> users;		// vector for registered users
	vector <Node*> nodes;		// vector for available nodes
	vector <bet*> bets;			// vector for placed bets
	int num_of_logs;			// number of logs
public:
	BetAtzis();
	~BetAtzis();
	void print_location() {
		node->print_location();
	}

	void print_options() {
		int type = user->get_type();
		node->print_options(type);
	}

	void print_operations(BetAtzis* interface) {
		user->Print_Operations(*interface);
	}

	void set_profits(double commission) {
		profits += commission;
	}

	long double get_profits() {
		return profits;
	}

	void set_commission(double commission) {
		promitheia = commission;
	}

	double get_commission() {
		return promitheia;
	}

	void set_num_of_logs(int num) {
		num_of_logs = num;
	}

	int get_num_of_logs() {
		return num_of_logs;
	}

	void set_user(User *usr) {
		user = usr;
	}

	User* get_user() {
		return user;
	}
	
	Node* get_node() {
		return node;
	}

	User* get_userptr(int user_id) {
		return users[user_id-1];
	}

	void set_level(int lvl) {
		if (Current_lvl == 4) {
			cout << "You cannot enter the selections. You can only place your bets." << endl;
		}
		else {
			Current_lvl++;
			node = node->get_next(lvl);
		}
	}

	void return_home() {
		Current_lvl = 0;
		node = home;
	}

	int get_current_level() {
		return Current_lvl;
	}

	Node* get_level() {
		return node;
	}

	Node* get_home() {
		return home;
	}

	int get_type_of_profits() {
		if (type_ofProfits == "Klasmatika") {
			return 0;							//0 for fraction
		}
		else {
			return 1;							//1 for decimal
		}
	}

	void set_type_of_profits(string NEW) {
		type_ofProfits = NEW;
	}

	int get_nodes_size() {
		return nodes.size();
	}

	string get_node_full_id(int option) {
		return nodes[option]->get_full_id();
	}

	void delete_node(string full_id);

	void place() {
		user->place(*this);
	}

	void print_user_bets();												//prints user's bets
	void voided(string full_id);										//returns stake to users
	void settle(string full_id,int option);								//defines the winning option
	void pay(string full_id, double profit);							//returns profit to users

	
//functions for vector changes
	void set_new_username(string OLD, string NEW);
	void set_new_password(string name, string NEW);
	void set_new_balance(string name, double ADD);
	bool operation(string, BetAtzis*);
//vector save
	bool save();
	void Logs();
//management
	bool write_log(string, string, string, string);
	bet * get_bet(int bet_id);
	void set_bet(string node_id, double stake, int selection_id);
	int get_bets_size() {
		return bets.size();
	}
	User * current_user(string usrnm);
	void print_users();
	void search_user(string user);
	void lock_user(string user);
	void set_visibility(int option);
	bool get_visibility(int option);
};

//functions for vector initialization

int extract_id(string);

string extract_username(string);

string extract_password(string);

string extract_fullname(string);

double extract_balance(string);

string extract_status(string);

int extract_type(string);

int extract_betid(string);

int extract_userid(string);

double extract_stake(string);

string extract_result(string);

string extract_nodeid(string);