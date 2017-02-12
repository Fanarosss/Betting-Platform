#pragma once

class User {
//abstract class
public:
	virtual void Operation(char)=0;
};

class Guest : User{ 
protected:
	//access by all the others too.
public:
	void Operation(char);

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
};

class Trader : User{
public:
	void Operation(char);
};

class Director : User{
public:
	void Operation(char);
};