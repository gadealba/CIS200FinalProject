#pragma once
#ifndef USER_H
#define USER_H
#include <iostream>
#include <fstream> // for writing on text file: userTable.
#include <sstream> // for parsing text file: userTable.
#include <string> // for writing on text file : userTable.
using namespace std;
class User {
	private:
		int user_id;
		string username;
		string password;
		string fileName = "userTable.txt";
		bool isLoggedin = 0;
	public:
		bool checkForUser(const string& username, const string& password);
		void setUsername(const string& username);
		void setPassword(const string& password);
		void changeUsername(const string& oldUsername, const string& newUsername);
		void changePassword(const string& oldPassword, const string& newPassword);
		bool checkForLoggedIn();
		void addUserToTable(const User& user);
		void login(const string& username, const string& password);
};
static int USER_ID = 0;

#endif