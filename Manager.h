#pragma once
#include <iostream>
#include <vector>
using namespace std;
#include "Identity.h"
#include "Student.h"
#include "Teacher.h"
#include "libraryRoom.h"

class Admin :public Identity 
{
public:
	Admin();
	Admin(string name, string password);

	virtual void operatingMenu();

	void addProfile();	//add student or teacher
	void showProfile();	//show personal profile
	void showLibraryRoom();	//show library capacity
	void clearRes();	//clear reservations

	void initVector();	//initialize vectors
	bool checkDuplicate(int id, int type);	//check if there is any duplicated ID

	vector<Student> vStudent;
	vector<Teacher> vTeacher;
	vector<LibraryRoom> vLib;

};