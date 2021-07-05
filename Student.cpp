#include "Student.h"
#include <algorithm>

Student::Student()
{
}

Student::Student(int id, string name, string password)
{
	this->studentId = id;
	this->name = name;
	this->password = password;

	ifstream ifs;	//read library room file
	ifs.open(LibraryFile, ios::in);
	LibraryRoom l;
	while (ifs >> l.roomId && ifs >> l.maxCapacity) {
		vLib.push_back(l);
	}
	ifs.close();
}

void Student :: operatingMenu()
{
	cout << "******************* Welcome dear student "<< this->name<<"! *****************" << endl;
	cout << "----------------------------------------------------------\n";
	cout << "|                                                         |\n";
	cout << "|                1. Reserve a seat                        |\n";
	cout << "|                                                         |\n";
	cout << "|                2. Check personal reservations           |\n";
	cout << "|                                                         |\n";
	cout << "|                3. Check all reservations                |\n";
	cout << "|                                                         |\n";
	cout << "|                4. Cancel personal reservations          |\n";
	cout << "|                                                         |\n";
	cout << "|                0. Log out                               |\n";
	cout << "|                                                         |\n";
	cout << "----------------------------------------------------------\n";
}

void Student::applyRes()
{
	int day = 0;
	int interval = 0;	//morning or afternoon
	int room = 0;

	cout << "Library room open from Monday to Friday" << endl;
	cout << "Please enter the day you would like to make reservation: " << endl;
	cout << "1. Monday" << endl;
	cout << "2. Tuesday" << endl;
	cout << "3. Wednesday" << endl;
	cout << "4. Thursday" << endl;
	cout << "5. Friday" << endl;
	while (true) {
		cin >> day;
		if (day >= 1 && day <= 5) {
			break;
		}
		cout << "Invalid day! Please reenter: " << endl;
	}

	cout << "Please enter the period you would like to make reservation: " << endl;
	cout << "1. Morning" << endl;
	cout << "2. Afternoon" << endl;
	while (true) {
		cin >> interval;
		if (interval == 1 || interval == 2) {
			break;
		}
		cout << "Invalid period! Please reenter: " << endl;
	}

	cout << "Please enter the library room you would like to make reservation: " << endl;
	for (int i = 0; i < vLib.size(); i++) {
		cout << "Library room #" << vLib[i].roomId << " maximum capacity: " << vLib[i].maxCapacity << endl;
	}
	while (true) {
		cin >> room;
		if (room >= 1 && room <= vLib.size()) {
			break;
		}
		cout << "Invalid room number! Please reenter: " << endl;
	}

	cout << "Your reservation has been in process!" << endl;
	ofstream ofs;	//write reservation info
	ofs.open(ResFile, ios::app);
	ofs << "Day:" << day << " ";
	ofs << "Interval:" << interval << " ";
	ofs << "StudentId:" << this->studentId << " ";
	ofs << "StudentName:" << this->name << " ";
	ofs << "LibraryRoom:" << room << " ";
	ofs << "Status:" << 1 << endl;	//Status: 1:In process, 2:Passed, -1:Failed, 0:Cancelled
	ofs.close();

	system("pause");
	system("cls");
}

void Student::showMyRes()
{
	Reservation res;
	if (res.size == 0) {	//no reservation record
		cout << "No record found!" << endl;
		system("pause");
		system("cls");
		return;
	}

	int myRes = 0;	//self reservation
	for (int i = 0; i < res.size; i++) {	//compare StudentId
		if (this->studentId == atoi(res.resRecord[i]["StudentId"].c_str())) {	//match the id, convert string to const char* then to int
			myRes++;
			string day;
			if (res.resRecord[i]["Day"] == "1") {
				day = "Monday";
			}
			else if (res.resRecord[i]["Day"] == "2") {
				day = "Tuesday";
			}
			else if (res.resRecord[i]["Day"] == "3") {
				day = "Wednesday";
			}
			else if (res.resRecord[i]["Day"] == "4") {
				day = "Thursday";
			}
			else if (res.resRecord[i]["Day"] == "5") {
				day = "Friday";
			}
			cout << "Reservation day: " << day << " ";
			cout << "Interval: " << (res.resRecord[i]["Interval"] == "1" ? "Morning" : "Afternoon") << " ";
			cout << "Library Room: " << res.resRecord[i]["LibraryRoom"] << " ";

			string status;
			if (res.resRecord[i]["Status"] == "1") {
				status = "In Process.";
			}
			else if (res.resRecord[i]["Status"] == "2") {
				status = "Passed.";
			}
			else if (res.resRecord[i]["Status"] == "-1") {
				status = "Failed.";
			}
			else if (res.resRecord[i]["Status"] == "0") {
				status = "Cancelled.";
			}
			cout << "Status: " << status << endl;
		}
	}
	if (myRes==0) {	//no record found
		cout << "You have no reservation!" << endl;
	}

	system("pause");
	system("cls");
}

void Student::showAllRes()
{
	Reservation res;
	res.showRes();
}

void Student::cancelRes()
{
	Reservation res;
	if (res.size == 0) {	//no reservation record
		cout << "No record found!" << endl;
		system("pause");
		system("cls");
		return;
	}

	cout << "You may only cancel reservations that have been approved or in process!" << endl;
	vector<int>v;	//self reservation record number

	for (int i = 0; i < res.size; i++) {	//compare and match with self id
		if (this->studentId == atoi(res.resRecord[i]["StudentId"].c_str())) {	//match the id, convert string to const char* then to int
			if (res.resRecord[i]["Status"] == "1" || res.resRecord[i]["Status"] == "2") {	//1-In process 2-Passed
				v.push_back(i);	//record number

				cout << "Record #" << i << endl;

				string day;
				if (res.resRecord[i]["Day"] == "1") {
					day = "Monday";
				}
				else if (res.resRecord[i]["Day"] == "2") {
					day = "Tuesday";
				}
				else if (res.resRecord[i]["Day"] == "3") {
					day = "Wednesday";
				}
				else if (res.resRecord[i]["Day"] == "4") {
					day = "Thursday";
				}
				else if (res.resRecord[i]["Day"] == "5") {
					day = "Friday";
				}
				cout << "Reservation day: " << day << " ";
				cout << "Interval: " << (res.resRecord[i]["Interval"] == "1" ? "Morning" : "Afternoon") << " ";
				cout << "Library Room: " << res.resRecord[i]["LibraryRoom"] << " ";
				cout << "Status: " << (res.resRecord[i]["Status"] == "1" ? "In Process" : "Passed") << endl;	//only in process or passed reservation can be cancelled
			}
			
		}			
	}
	if (v.empty()) {	//no available record
		cout << "No reservations can be canceled!" << endl;
	}
	else {
		cout << "Please indicate the record number you would like to cancel: " << endl;
		cout << "Or type '-1' to Exit" << endl;
		int choice = -1;	//user choice
		while (true) {
			cin >> choice;
			if (choice >= 0 && find(v.begin(), v.end(), choice) != v.end()) {
				res.resRecord[choice]["Status"] = "0";	//cancel reservation
				res.updateRes();
				cout << "Your reservation has been canceled!" << endl;
				break;
			}
			else if (choice == -1) {
				break;
			}
			else {
				cout << "Invalid number! Please reenter." << endl;
			}
		}
	}
	system("pause");
	system("cls");
}
