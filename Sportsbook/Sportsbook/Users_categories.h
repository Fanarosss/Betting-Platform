#pragma once
#include "stdafx.h"
#include "Main_functions.h"
#include "hierarchy.h"
//#include "BetAtzis.h"//

using namespace std;

class BetAtzis;

class User {
	int user_id;
	string username;
	string fullname;
	string password;
	int type;
	//vector <bet*> bets;
public:
	User (int id = 0,string Username = "-", string Fullname = "-", string Password = "-" , int Type = 0) {
		user_id = id;
		username = Username;
		fullname = Fullname;
		password = Password;
		type = Type;
	}
	void print_username() { cout << username; }
	void print_fullname() { cout << fullname; }
	void print_password() { cout << password; }
	int get_id() { return user_id; }
	//void set_bet(bet &bt) { bets.push_back(&bt); }
	string get_username() { return username; }
	string get_fullname() { return fullname; }
	string get_password() { return password; }
	void set_username(string nusername) { username = nusername; }
	void set_fullname(string nfullname) { fullname = nfullname; }
	void set_password(string npassword) { password = npassword; }
	virtual void print_status(){}
	virtual void print_balance(){}
	virtual void print_freebets(){}
	virtual string get_Status() { return NULL; }
	virtual double get_balance() { return 0; }
	virtual string get_free_bets() { return NULL; }
	virtual void set_status(string nstatus){}
	virtual void set_balance(double namount){}
	virtual void set_freebets(string freebet){}
	virtual bool Operation(string, BetAtzis&) { return 1; }
	virtual void Bets(){}
	virtual void Print_Operations(BetAtzis&){}
	virtual string conversion() { return NULL; }
	virtual void place(BetAtzis&){}
};

class Guest : public User{ 
public:
	Guest ():User() {
		std::cout << "Welcome!" << endl;
	}
	bool Operation(string, BetAtzis&);
	void Bets() {}
	void Print_Operations(BetAtzis&);

};

class Wallet {
private:
	double amount;
public:
	Wallet(double money) {
		amount = money;
	}
	void print_wallet() {
		cout << amount;
	}
	double get_wallet() {
		return amount;
	}
	void set_wallet(double namount) {
		amount += namount;
	}
};

class Punter : public User{
private:
	string status;
	Wallet balance;
	string freebets;
public:
	Punter (int id,string username, string fullname, string password, double money): User(id,username, fullname, password, 1), balance(money) {
		status = get_status(username);
		freebets = get_freebets(username);
		std::cout << "Welcome mr." << username << endl;
	}
	bool Operation(string, BetAtzis&);
	void Bets() {}
	void Print_Operations(BetAtzis&);
	string conversion();
	void print_status() { cout << status; }
	void print_balance() { balance.print_wallet(); }
	void print_freebets() { cout << freebets; }
	string get_Status() { return status; }
	double get_balance() { double amount = balance.get_wallet(); return amount; }
	string get_free_bets() { return freebets; }
	void set_status(string nstatus) { status = nstatus; }
	void set_balance(double namount) { balance.set_wallet(namount); }
	void set_freebets(string freebet) { freebets.append(", "); freebets.append(freebet); }
	void place(BetAtzis&);
};

class Trader : public User{
public:
	Trader (int id,string username, string fullname, string password):User(id,username, fullname, password, 2){
		std::cout << "Welcome back mr." << username << endl;
	}
	bool Operation(string, BetAtzis&);
	void Bets();
	void Print_Operations(BetAtzis&);
	string conversion();
};

class Director : public User{
public:
	Director (int id,string username, string fullname, string password):User(id,username, fullname, password, 3) {
		std::cout << "Welcome back boss" << endl;
	}
	bool Operation(string, BetAtzis&);
	void Bets();
	void Print_Operations(BetAtzis&);
	string conversion();
};

class bet {
private:
	int bet_id;
	int user_id;
	User* user;
	string node_id;
	double stake;
	string result;
public:
	bet(int betid, int userid, string nodeid, double stk, string rslt, User * user);
	~bet() {}
	string conversion();
	void set_user(User *usr) {
		user = usr;
		user_id = usr->get_id();
	}
	void set_user_byid(int id) {
		//search in vector
	}
	User * get_user() {
		return user;
	}
	int get_bet_id() {
		return bet_id;
	}
	int get_user_id() {
		return user_id;
	}
	string get_nodeid() {
		return node_id;
	}
	void set_stake(double stk) {
		stake = stk;
	}
	double get_stake() {
		return stake;
	}
	void set_result(string outcome) {
		result = outcome;
	}
	string get_result() {
		return result;
	}
};