#pragma once
#include <iostream>
using namespace std;
#include "loginFile.h"
#include <fstream>
#include <map>

class Reservation {
public:
	Reservation();
	void updateRes();
	void showRes();	//show the complete list of reservations

	int size;
	map<int, map<string, string>> resRecord;	//reservation number, key:value pairs
	map<string, string> appendPair(string s, map<string, string>m);

};