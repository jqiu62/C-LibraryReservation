#include "Manager.h"
#include <fstream>
#include <algorithm>
#include "loginFile.h"

Admin::Admin()
{
}

Admin::Admin(string name, string password)
{
	this->name = name;
	this->password = password;

	this->initVector();	//clear vectors, get number of students and teachers
}

void Admin::operatingMenu()
{
	cout << "******************** Welcome dear admin! ******************" << endl;
	cout << "----------------------------------------------------------\n";
	cout << "|                                                         |\n";
	cout << "|                   1. Add Account                        |\n";
	cout << "|                                                         |\n";
	cout << "|                   2. Check Account                      |\n";
	cout << "|                                                         |\n";
	cout << "|                   3. Check Library Room                 |\n";
	cout << "|                                                         |\n";
	cout << "|                   4. Clear Reservations                 |\n";
	cout << "|                                                         |\n";
	cout << "|                   0. Log out                            |\n";
	cout << "|                                                         |\n";
	cout << "----------------------------------------------------------\n";
}

void Admin::addProfile()
{
	cout << "Enter the type of profile: " << endl;
	cout << "1. Add student " << endl;
	cout << "2. Add Teacher " << endl;

	string fileName;
	string tip;
	string errorTip;	//error message

	ofstream ofs;
	int choice = 0;
	cin >> choice;
	if (choice == 1) {	//add student
		fileName = StudentFile;
		tip = "Please enter student ID: ";
		errorTip = "Duplicated student ID, please reenter another ID: ";
	}
	else if (choice == 2) {	//add teacher
		fileName = TeacherFile;
		tip = "Please enter teacher/employee ID: ";
		errorTip = "Duplicated employee ID, please reenter another ID: ";
	}
	else {
		cout << "Invalid input." << endl;
		system("pause");
		system("cls");
		return;
	}

	
	ofs.open(fileName, ios::out | ios::app);	//append
	int id;		//take new info as id, name and password
	string name;
	string password;
	cout << tip << endl;
	//duplicated id control
	while (true) {
		cin >> id;
		bool isUnique = !checkDuplicate(id, choice);
		if (isUnique) {
			break;
		}
		else {
			cout << errorTip << endl;
		}
	}
	cout << "Please enter name: " << endl;
	cin >> name;
	cout << "Please enter password" << endl;
	cin >> password;

	//add profile
	ofs << id << " " << name << " " << password << " " << endl;
	cout << "Add profile successfully!" << endl;

	system("pause");
	system("cls");
	ofs.close();
	this->initVector();	//read all profile including recent added info

}

void printStudent(Student& s);
void printTeacher(Teacher& t);

void Admin::showProfile()
{
	cout << "Please select the type of profile to check: " << endl;
	cout << "1. Check student profile" << endl;
	cout << "2. Check teacher profile" << endl;

	int choice = 0;
	cin >> choice;
	if (choice == 1) {	//student
		cout << "All student profile: " << endl;
		for_each(vStudent.begin(), vStudent.end(), printStudent);
	}
	else if (choice == 2) {	//teacher
		cout << "All teacher profile: " << endl;
		for_each(vTeacher.begin(), vTeacher.end(), printTeacher);
	}

	system("pause");
	system("cls");
}

void printStudent(Student& s) {
	cout << "Student ID: " << s.studentId << " Student name: " << s.name << " Student password: " << s.password << endl;
}

void printTeacher(Teacher& t)
{
	cout << "Employee ID: " << t.employId << " Employee name: " << t.name << " Employee password: " << t.password << endl;
}

void printLib(LibraryRoom& l) {
	cout << "Library room #" << l.roomId << " Maximum capacity: " << l.maxCapacity << endl;
}

void Admin::showLibraryRoom()
{
	cout << "Library room capacity: " << endl;
	for_each(vLib.begin(), vLib.end(), printLib);
	system("pause");
	system("cls");
}

void Admin::clearRes()
{
	ofstream ofs(ResFile, ios::trunc);
	ofs.close();

	cout << "Successfully clear all reservations!" << endl;
	system("pause");
	system("cls");
}

void Admin::initVector()	//initiate vector
{
	vStudent.clear();
	vTeacher.clear();
	//read student file
	ifstream ifs;
	ifs.open(StudentFile, ios::in);
	if (!ifs.is_open()) {
		cout << "Failed to open!" << endl;
		return;
	}
	Student s;
	while (ifs >> s.studentId && ifs >> s.name && ifs >> s.password) {
		vStudent.push_back(s);
	}
	cout << "Current number of students: " << vStudent.size() << endl;
	ifs.close();

	//read teacher file
	ifs.open(TeacherFile, ios::in);
	if (!ifs.is_open()) {
		cout << "Failed to open!" << endl;
		return;
	}
	Teacher t;
	while (ifs >> t.employId && ifs >> t.name && ifs >> t.password) {
		vTeacher.push_back(t);
	}
	cout << "Current number of teachers: " << vTeacher.size() << endl;
	ifs.close();

	//read library room file
	ifs.open(LibraryFile, ios::in);
	if (!ifs.is_open()) {
		cout << "Failed to open!" << endl;
		return;
	}
	LibraryRoom l;
	while (ifs >> l.roomId && ifs >> l.maxCapacity) {
		vLib.push_back(l);
	}
	cout << "The number of library rooms: " << vLib.size() << endl;
	ifs.close();
}

bool Admin::checkDuplicate(int id, int type)
{
	if (type == 1) {	//student
		for (vector<Student>::iterator it = vStudent.begin();it != vStudent.end();it++) {
			if (id == it->studentId) {
				return true;
			}
		}
	}
	else if (type == 2) {	//teacher
		for (vector<Teacher>::iterator it = vTeacher.begin();it != vTeacher.end();it++) {
			if (id == it->employId) {
				return true;
			}
		}
	}
	return false;
}
