#pragma once

class Person {
public:
	virtual void Operation(char) = 0;
};

class Guest {
	public:
		void Operation(char);

};

class Punter {
private:
	Wallet wallet;
public:
	void Operation(char);
};

class Wallet {
	double amount;
};

class Trader {
public:
	void Operation(char);
};

class Director {
public:
	void Operation(char);
};