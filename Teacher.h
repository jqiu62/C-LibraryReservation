#pragma once
#include <iostream>
using namespace std;
#include "Identity.h";

class Teacher : public Identity 
{
public:
	Teacher();
	Teacher(int employId, string name, string password);

	virtual void operatingMenu();

	void showAllRes();	//show all reservations
	void verifyRes();	//verify reservation

	int employId;
};
