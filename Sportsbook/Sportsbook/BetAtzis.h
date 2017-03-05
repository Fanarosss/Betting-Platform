#pragma once
#include "Users_categories.h"
#include "stdafx.h"
#include "hierarchy.h"


class BetAtzis {
private:
	long double profits;
	double promitheia;
	string type_ofProfits;
	int Current_lvl;
	User* user; // deikths ston current user
	Home* home; // to home den einai node opote to vazw edw ksexorista gia na exw panta prosvasi xoris pollapla back//
	Node* node;
	vector <User*> users;
	vector <Node*> nodes;
	vector <bet*> bets;
	int num_of_logs;
public:
	BetAtzis();
	~BetAtzis();
	void set_num_of_logs(int num) {
		num_of_logs = num;
	}

	int get_num_of_logs() {
		return num_of_logs;
	}

	void print_location() {
		node->print_location();
	}

	void print_options() {
		node->print_options();
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
		Current_lvl++;
		node = node->get_next(lvl);
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
			return 0;							//0 gia klasma
		}
		else {
			return 1;							//1 gia dekadiko
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

	void delete_node(string full_id) {
		for (int i = 0; i < nodes.size(); i++) {
			if (nodes[i]->get_full_id() == full_id) {
				nodes.erase(nodes.begin() + i);
				break;
			}
		}
	}

	void place() {
		user->place(*this);
	}

	void print_user_bets(); //ektupwnei ta stoixhmata tou xrhsth
	void voided(string full_id);  //epistrefei ta xrhmata stous users pou pontarane sthn epilogh pou akurw8hke
	void settle(string full_id,int option);	  //ka8orizei thn nikhthria epilogh
	void pay(string full_id, double profit);		  //plhrwnei tous nikhtes

	void set_bet(string node_id, double stake,int selection_id);

//	void set_results(string node_id);
//functions for vector changes
	void set_new_username(string OLD, string NEW);
	void set_new_password(string name, string NEW);
	void set_new_balance(string name, double ADD);
	bool operation(string, BetAtzis*);
//vector save
	bool save();

	void Logs();

	bool write_log(string, string, string, string);

	bet * get_bet(int bet_id);

	User * current_user(string usrnm);

	int get_bets_size() {
		return bets.size();
	}

	void print_users();
	void search_user(string user);
	void lock_user(string user);
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