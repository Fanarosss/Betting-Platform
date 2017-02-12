#pragma once

class User {
//abstract class
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
	Wallet wallet;
public:
	Punter(double money):wallet(money){}
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