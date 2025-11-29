#include "User.h"


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
	 
	ofstream reader(this->fileName);
	if (!reader) {
		cout << "Error: File unavailable for reading." << endl;
		return;
	}
	reader << ++USER_ID << ":" + this->username + ":" + this->password;
	this->isLoggedin = true;
}
void User::login(const string& username, const string& password) {
	this->isLoggedin = true;
	this->username = username;
	this->password = password;
}