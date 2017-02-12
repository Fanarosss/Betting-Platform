#pragma once

class Guest { 
	protected:
		//access by all the others too.
	public:
		virtual void Operation(char);

};

class Punter : public Guest{
private:
	Wallet wallet;
public:
	void Operation(char);
};

class Wallet : Punter{
protected:
	double amount;
};

class Trader : Guest{
public:
	void Operation(char);
};

class Director : Guest{
public:
	void Operation(char);
};