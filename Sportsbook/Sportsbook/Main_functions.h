#pragma once

#include "stdafx.h"

using namespace std;

//reading from users.csv

bool check_for_password(string,string);

string read_from_csv(int,string);

double get_balance(string);

int get_type(string);

string get_status(string);

string get_freebets(string);

int get_id(string);

string get_fullname(string);

string get_password(string);

//reading from bets.csv

void print_lastbets();

int get_betid(string);