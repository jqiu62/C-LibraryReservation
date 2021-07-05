#include "Teacher.h"
#include "Reservation.h"
#include <vector>

Teacher::Teacher()
{
}

Teacher::Teacher(int employId, string name, string password)
{
	this->employId = employId;
	this->name = name;
	this->password = password;
}

void Teacher::operatingMenu()
{
	cout << "******************* Welcome dear teacher " << this->name << "! *****************" << endl;
	cout << "----------------------------------------------------------\n";
	cout << "|                                                         |\n";
	cout << "|                1. Check all reservations                |\n";
	cout << "|                                                         |\n";
	cout << "|                2. Approve a reservation                 |\n";
	cout << "|                                                         |\n";
	cout << "|                0. Log out                               |\n";
	cout << "|                                                         |\n";
	cout << "----------------------------------------------------------\n";
}

void Teacher::showAllRes()
{
	Reservation res;
	res.showRes();
}

void Teacher::verifyRes()	//verify a reservation
{
	Reservation res;
	if (res.size == 0) {	//no reservation record
		cout << "No record found!" << endl;
		system("pause");
		system("cls");
		return;
	}

	cout << "Only in process reservations need to be verified!" << endl;
	vector<int>v;	//self reservation record number
	for (int i = 0; i < res.size; i++) {	//compare and match with self id
		if (res.resRecord[i]["Status"] == "1") {	//1-In process
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
	if (v.empty()) {	//no record to be approved
		cout << "No reservations need to be approved!" << endl;
	}
	else {
		cout << "Please indicate the record number you would like to verify: " << endl;
		cout << "Or type '-1' to Exit" << endl;
		int choice = -1;	//user choice
		while (true) {
			cin >> choice;
			if (choice >= 0 && find(v.begin(), v.end(), choice) != v.end()) {	//choice can be found in unapproved vector
				cout << "Please indicate your verification of this reservation: " << endl;
				cout << "1. Approve" << endl;
				cout << "2. Deny" << endl;
				cout << "0. Exit" << endl;
				int choice2 = 0;
				while (true) {
					cin >> choice2;
					if (choice2 == 0) {
						break;
					}
					else if (choice2 == 1) {
						res.resRecord[choice]["Status"] = "2";	//2-Approve
						break;
					}
					else if (choice2 == 2) {
						res.resRecord[choice]["Status"] = "-1";	//-1-Failed
						break;
					}
				}				
				res.updateRes();
				cout << "The status of this reservation has been successfully changed!" << endl;
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
