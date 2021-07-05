#include "Reservation.h"

Reservation::Reservation()
{
	ifstream ifs;
	ifs.open(ResFile, ios::in);

	string day;
	string interval;
	string studentId;
	string studentName;
	string libraryRoom;
	string status;
	map<string, string>m;

	this->size = 0;
	while (ifs >> day && ifs >> interval && ifs >> studentId && ifs >> studentName && ifs >> libraryRoom && ifs >> status) {
		
		m = appendPair(day, m);
		m = appendPair(interval, m);
		m = appendPair(studentId, m);
		m = appendPair(studentName, m);
		m = appendPair(libraryRoom, m);
		m = appendPair(status, m);
		//insert all pairs into the greater map
		this->resRecord.insert(make_pair(this->size, m));
		this->size++;
		m.clear();
	}

	//print out test
	/*for (map<int, map<string, string>>::iterator it = resRecord.begin();it != resRecord.end();it++) {
		cout << "Record: "<<it->first << endl;
		for (map<string, string>::iterator mit = (*it).second.begin();mit != (*it).second.end();mit++) {
			cout << "Content: "<<mit->first << " " << mit->second << endl;
		}
	}*/
	ifs.close();
}

void Reservation::updateRes()	//rewrite old reservation file
{
	if (this->size == 0) {
		return;	//no record
	}
	ofstream ofs(ResFile, ios::out | ios::trunc);
	for (int i = 0; i < this->size;i++) {
		ofs << "Day:" << this->resRecord[i]["Day"] << " ";
		ofs << "Interval:" << this->resRecord[i]["Interval"] << " ";
		ofs << "StudentId:" << this->resRecord[i]["StudentId"] << " ";
		ofs << "StudentName:" << this->resRecord[i]["StudentName"] << " ";
		ofs << "LibraryRoom:" << this->resRecord[i]["LibraryRoom"] << " ";
		ofs << "Status:" << this->resRecord[i]["Status"] << endl;
	}
	ofs.close();
}

void Reservation::showRes()
{
	if (this->size == 0) {	//no reservation record
		cout << "No record found!" << endl;
		system("pause");
		system("cls");
		return;
	}

	for (int i = 0;i < this->size;i++) {	//compare StudentId
		cout << "Record #" << i << endl;
		string day;
		if (resRecord[i]["Day"] == "1") {
			day = "Monday";
		}
		else if (resRecord[i]["Day"] == "2") {
			day = "Tuesday";
		}
		else if (resRecord[i]["Day"] == "3") {
			day = "Wednesday";
		}
		else if (resRecord[i]["Day"] == "4") {
			day = "Thursday";
		}
		else if (resRecord[i]["Day"] == "5") {
			day = "Friday";
		}

		cout << "Reservation day: " << day << " ";
		cout << "Interval: " << (resRecord[i]["Interval"] == "1" ? "Morning" : "Afternoon") << " ";
		cout << "Student ID: " << resRecord[i]["StudentId"] << " ";
		cout << "Student Name: " << resRecord[i]["StudentName"] << " ";
		cout << "Library Room: " << resRecord[i]["LibraryRoom"] << " ";

		string status;
		if (resRecord[i]["Status"] == "1") {
			status = "In Process.";
		}
		else if (resRecord[i]["Status"] == "2") {
			status = "Passed.";
		}
		else if (resRecord[i]["Status"] == "-1") {
			status = "Failed.";
		}
		else if (resRecord[i]["Status"] == "0") {
			status = "Cancelled.";
		}

		cout << "Status: " << status << endl;
	}

	system("pause");
	system("cls");
}

map<string,string> Reservation::appendPair(string s, map<string, string> m)
{
	string key;
	string value;
	int pos = s.find(":");
	if (pos != -1) {
		key = s.substr(0, pos);
		value = s.substr(pos+1, s.size()-pos-1);
		m.insert(make_pair(key, value));
		return m;
	}
}
