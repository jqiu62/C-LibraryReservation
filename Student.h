#pragma once
#include <iostream>
#include <vector>
#include <fstream>
using namespace std;
#include "Identity.h"
#include "libraryRoom.h"
#include "loginFile.h"
#include "Reservation.h"

class Student : public Identity 
{
public:
	Student();
	Student(int id, string name, string password);

	virtual void operatingMenu();

	void applyRes();	//apply for reservation
	void showMyRes();	//show personal reservation
	void showAllRes();	//show all reservations
	void cancelRes();	//cancel personal reservation

	int studentId;
	vector<LibraryRoom> vLib;

};
