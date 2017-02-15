#pragma once
#include "stdafx.h"
#include "Main_functions.h"

using namespace std;

class User {
	int user_id;
	string username;
	string fullname;
	string password;
	int type;
public:
	User (string Username = "-", string Fullname = "-", string Password = "-" , int Type = 0) {
		username = Username;
		fullname = Fullname;
		password = Password;
		type = Type;
	}
	virtual void Operation(string){}
	virtual void Bets(){}
	virtual void Print_Operations(){}
};

class Guest : User{ 
public:
	Guest ():User() {
		std::cout << "Welcome!" << endl;
	}
	void Operation(string);
	void Bets() {}
	void Print_Operations();

};

class Wallet {
protected:
	double amount;
public:
	Wallet(double money) {
		amount = money;
	}
};

class Punter : public User{
private:
	string status;
	Wallet balance;
	string freebets;
public:
	Punter (string username, string fullname, string password, double money): User(username, fullname, password, 1), balance(money) {
		status = get_status(username);
		freebets = get_freebets(username);
		std::cout << "Welcome mr." << username << endl;
	}
	void Operation(string);
	void Bets() {}
	void Print_Operations();
};

class Trader : User{
public:
	Trader (string username, string fullname, string password):User(username, fullname, password, 2){
		std::cout << "Welcome back mr." << username << endl;
	}
	void Operation(string);
	void Bets();
	void Print_Operations();
};

class Director : User{
public:
	Director (string username, string fullname, string password):User(username, fullname, password, 3) {
		std::cout << "Welcome back boss" << endl;
	}
	void Operation(string);
	void Bets();
	void Print_Operations();
};