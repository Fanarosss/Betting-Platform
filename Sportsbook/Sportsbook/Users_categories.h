#pragma once

class User {
	int user_id;
	string username;
	string fullname;
	string password;
	int type;
public:
	virtual void Operation(string)= 0;
	virtual void Bets()= 0;
	virtual void Print_Operations()= 0;
};

class Guest : User{ 
public:
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
	Punter(double money):balance(money){}
	void Operation(string);
	void Bets() {}
	void Print_Operations();
};

class Trader : User{
public:
	void Operation(string);
	void Bets();
	void Print_Operations();
};

class Director : User{
public:
	void Operation(string);
	void Bets();
	void Print_Operations();
};