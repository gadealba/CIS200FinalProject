#include "User.h"
int User::USER_ID = []{
	ifstream reader("userTable.txt");
	string input;
	int temp = 0;
	while (getline(reader, input)) {
		stringstream substring(input);
		string getId, getUsername, getPassword;
		if (getline(substring, getId, ':') && getline(substring, getUsername, ':') && getline(substring, getPassword, ':')) {
			temp = stoi(getId);
		}
	}
		cout << "THIS IS THE USER_ID" << temp << endl;
		reader.close();
		return temp;
}();

bool User::checkForUser(const string& username, const string& password) {
	ifstream reader(this->fileName);
	string input;
	if (!reader) {
		cout << "Error:File unavailable for reading." << endl;
		return false;
	}
	while (getline(reader, input)) {
		stringstream substring(input);
		string getId, getUsername, getPassword;
		if (getline(substring, getId, ':') && getline(substring, getUsername, ':') && getline(substring, getPassword, ':')) {
			if (username == getUsername && password == getPassword) {
				login(getUsername, getPassword);

				fileEvents = username + ".txt"; // file used to grab the events saved.
				cout << "this is fileEvents file name " << fileEvents << endl;
				reader.close();
				return true;
			}
		}
		
	}
	cout << "did not successfully login." << endl;
	reader.close();
	return false;
}
void User::setUsername(const string& username) {
	this->username = username;
}
void User::changeUsername(const string& oldUsername, const string& newUsername) {

}
void User::changePassword(const string& oldPassword, const string& newPassword) {

}
void User::setPassword(const string& password) {
	this->password = password;
}
bool User::checkForLoggedIn() {
	return this->isLoggedin;
}
void User::addUserToTable(const User &user) { 
	ofstream reader(this->fileName,ios::app);
	if (!reader) {
		cout << "Error: File unavailable for reading." << endl;
		return;
	}
	reader << ++USER_ID << ":" + this->username + ":" + this->password << endl;
	this->isLoggedin = true;
	reader.close();
	createUserDatabase(this->username);
}
void User::login(const string& username, const string& password) {
	this->isLoggedin = true;
	this->username = username;
	this->password = password;
	this->fileEvents = username + ".txt";
	getSavedEvents();
}
void User::createUserDatabase(const string& username) { // for saving Events
	fileEvents = username + ".txt";
	ofstream reader(fileEvents);
	if (!reader) {
		cout << "Error:File unavailable." << endl;
	}
	reader.close();
}
void User::createEvent(string& description,  int& month,  int& day,  int& year) {
	event.createEvent(description, month, day, year);
	addEventToTable(event);
	events.push_back(event);
}
void User::createEvent(string& description, int& month, int& day, int& year, int& hour, int& mins) {
	event.createEvent(description, month, day, year,hour,mins);
	addEventToTable(event);
	events.push_back(event);
}
void User::addEventToTable( Event& event) {
	ofstream reader(this->fileEvents,ios::app); // allows overwriting.
	if (!reader) {
		cout << "Error: File is unavailable." << endl;
		return;
	}
	reader << event.getDescription() + ":" + to_string(event.getDate().getMonth()) + ":" +
		to_string(event.getDate().getDay()) + ":" + to_string(event.getDate().getYear()) + ":" +
		to_string(event.getTime().getHour()) + ":" + to_string(event.getTime().getMins()) << endl;


}
void User::printAllEvents() {
	cout << "\n \n " << endl;
	for (int x = 0; x < events.size(); x++) {
		events.at(x).print();
	}
	cout << "\n \n " << endl;
}
void User::getSavedEvents() {
	ifstream reader(this->fileEvents); //opens events file
	if (!reader) {
		cout << "Error: File is unavailable." << endl;
	}
	if (reader.peek() == ifstream::traits_type::eof()) {
		cout << "no events in user account." << endl;
		return;
	}
	Event newEvent;
	int month,day,year,hour,mins;
	string description,fileMonth,fileDay,fileYear,fileHour,fileMins;
	while (getline(reader, inputFromFile)) { // for now the time does nothing.
		stringstream substring(inputFromFile);
		if (getline(substring, description, ':') && getline(substring, fileMonth, ':') && 
			getline(substring, fileDay, ':') && getline(substring, fileYear, ':') &&
			getline(substring, fileHour, ':') && getline(substring, fileMins, ':')) {
			month = stoi(fileMonth);
			day = stoi(fileDay);
			year = stoi(fileYear);
			hour = stoi(fileHour);
			mins = stoi(fileMins);
			if (hour == 0 && mins == 0) {
				newEvent.createEvent(description, month, day, year);
				events.push_back(newEvent);
			}
			else if (hour > 0 || mins > 0) {
				newEvent.createEvent(description, month, day, year, hour, mins);
				events.push_back(newEvent);
			}		
		}
	}
		
}

