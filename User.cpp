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

				//save the username for the correct file.
				return true;
			}
		}
	}
	cout << "did not successfully login." << endl;
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
}
void User::createUserDatabase(const string& username) { // for saving Events
	string fileName = username +".txt";
	ofstream reader(fileName);
	if (!reader) {
		cout << "Error:File unavailable." << endl;
	}
	reader.close();
}