#include <iostream>
#include <fstream>
using namespace std;
#include "Identity.h"
#include "Student.h"
#include "Teacher.h"
#include "Manager.h"
#include "loginFile.h"

void Login(string fileName, int type);
void adminMenu(Identity*& admin);
void studentMenu(Identity*& student);
void teacherMenu(Identity*& teacher);


int main()
{
	int choice = 0;	//user choice

	while (true)
	{
		cout << "*** Welcome to the library room seat reservation system! ***" << endl;
		cout << "************** Please indicate your identity: **************" << endl;
		cout << "----------------------------------------------------------\n";
		cout << "|                                                         |\n";
		cout << "|                   1. Student                            |\n";
		cout << "|                                                         |\n";
		cout << "|                   2. Teacher                            |\n";
		cout << "|                                                         |\n";
		cout << "|                3. Administrator                         |\n";
		cout << "|                                                         |\n";
		cout << "|                   0. Exit                               |\n";
		cout << "|                                                         |\n";
		cout << "----------------------------------------------------------\n";
		cout << "*** Your identity: ***" << endl;

		cin >> choice;
		switch (choice)
		{
		case 1:	//student
			Login(StudentFile, 1);
			break;
		case 2:	//teacher
			Login(TeacherFile, 2);
			break;
		case 3:	//admin
			Login(AdminFile, 3);
			break;
		case 0:	//exit
			cout << "Thanks for using the reservation system!" << endl;
			system("pause");
			return 0;
			break;
		default:
			cout << "Invalid choice! Please reenter the correct identity:" << endl;
			system("pause");
			system("cls");
			break;
		}
	}

	system("pause");
	return 0;
}

//login with file name and identity type
void Login(string fileName, int type) 
{
	Identity* person = NULL;
	//read file
	ifstream ifs;
	ifs.open(fileName, ios::in);
	//check if the file exists
	if (!ifs.is_open()) 
	{
		cout << "File does not exist!" << endl;
		ifs.close();
		return;
	}

	//take user info
	int id = 0;
	string name;
	string password;
	//identify
	if (type == 1) {	//student
		cout << "Enter your student ID: " << endl;
		cin >> id;
	}
	else if (type == 2) {	//teacher
		cout << "Enter your employee ID: " << endl;
		cin >> id;
	}	//admin has no ID

	//take user name and password
	cout << "Enter your user name: " << endl;
	cin >> name;
	cout << "Enter your password: " << endl;
	cin >> password;

	if (type == 1) {
		//student identity verification
		int fId;	//id, name and password read from file
		string fName;
		string fPassword;
		//read each line as id, name and password
		while (ifs >> fId && ifs >> fName && ifs >> fPassword) {
			//match info
			if (fId == id && fName == name && fPassword == password) {
				cout << "Student login succeed!" << endl;
				system("pause");
				system("cls");
				person = new Student(id, name, password);
				//enter student menu
				studentMenu(person);
				return;
			}
		}
	}
	else if (type == 2) {
		//teacher identity verification
		int fId;	//id, name and password read from file
		string fName;
		string fPassword;
		//read each line as id, name and password
		while (ifs >> fId && ifs >> fName && ifs >> fPassword) {
			//match info
			if (fId == id && fName == name && fPassword == password) {
				cout << "Teacher login succeed!" << endl;
				system("pause");
				system("cls");
				person = new Teacher(id, name, password);
				//enter teacher menu
				teacherMenu(person);
				return;
			}
		}
	}
	else if (type == 3) {
		//admin verification
		//name and password read from file
		string fName;
		string fPassword;
		//read each line as id, name and password
		while (ifs >> fName && ifs >> fPassword) {
			//match info
			if (fName == name && fPassword == password) {
				cout << "Admin login succeed!" << endl;
				system("pause");
				system("cls");
				person = new Admin(name, password);
				//enter admin menu
				adminMenu(person);
				return;
			}
		}
	}

	cout << "Login failed!" << endl;	//id, name and password not match
	system("pause");
	system("cls");
	return;
}

//Admin Menu
void adminMenu(Identity*& admin) {
	while (true) {
		//operating menu
		admin->operatingMenu();
		//build admin under identity
		Admin* ad = (Admin*)admin;

		int choice = 0;	//take user choice
		cin >> choice;
		if (choice == 1) {	//add account
			cout << "Add account" << endl;
			ad->addProfile();
		}
		else if (choice == 2) {	//check account
			cout << "Check account" << endl;
			ad->showProfile();
		}
		else if (choice == 3) {	//check library room capacity
			cout << "Check library room capacity" << endl;
			ad->showLibraryRoom();
		}
		else if (choice == 4) {	//clear all reservations
			ad->clearRes();
		}
		else {	//log out
			delete admin;
			cout << "Log out succeed!" << endl;
			system("pause");
			system("cls");
			return;
		}
	}
}

//Student Menu
void studentMenu(Identity*& student) {
	while (true) {
		//operating menu
		student->operatingMenu();
		//build admin under identity
		Student* s = (Student*)student;

		int choice = 0;	//take user choice
		cin >> choice;
		if (choice == 1) {	//make reservaton
			cout << "Reserve a seat" << endl;
			s->applyRes();
		}
		else if (choice == 2) {	//check personal reservation
			cout << "Check self reservation" << endl;
			s->showMyRes();
		}
		else if (choice == 3) {	//check all reservations
			cout << "Check all reservations" << endl;
			s->showAllRes();
		}
		else if (choice == 4) {	//clear all reservations
			s->cancelRes();
		}
		else {	//log out
			delete student;
			cout << "Log out succeed!" << endl;
			system("pause");
			system("cls");
			return;
		}
	}
}

//Teacher Menu
void teacherMenu(Identity*& teacher) {
	while (true) {
		teacher->operatingMenu();
		Teacher* t = (Teacher*)teacher;

		int choice = 0;	//take user choice
		cin >> choice;
		if (choice == 1) {	//check student reservaton
			cout << "Check all reservations" << endl;
			t->showAllRes();
		}
		else if (choice == 2) {	//approve reservations
			cout << "Approve a reservation" << endl;
			t->verifyRes();
		}
		else {	//log out
			delete teacher;
			cout << "Log out succeed!" << endl;
			system("pause");
			system("cls");
			return;
		}
	}
}