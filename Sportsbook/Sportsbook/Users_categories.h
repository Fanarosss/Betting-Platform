#pragma once

class User {
//abstract class
public:
	virtual void Operation(char)=0;
	virtual void Bets() = 0;
};

class Guest : User{ 
public:
	void Operation(char);
	void Bets() {}

};

class Wallet {
protected:
	double amount;
};

class Punter : public User{
private:
	Wallet wallet;
public:
	void Operation(char);
	void Bets() {}
};

class Trader : User{
public:
	void Operation(char);
	void Bets();
};

class Director : User{
public:
	void Bets();
	void Operation(char);
};