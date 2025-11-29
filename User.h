#pragma once
#ifndef USER_H
#define USER_H
#include "Event.h"
#include <vector>
#include <iostream>
#include <fstream> // for writing on text file: userTable.
#include <sstream> // for parsing text file: userTable.
#include <string> // for writing on text file : userTable.
using namespace std;
class User {
	private:
		int user_id;
		Event event;
		string username;
		string password;
		string fileName = "userTable.txt";
		string fileEvents = "";
		bool isLoggedin = 0;
		vector<Event> events;
		
	public:
		bool checkForUser(const string& username, const string& password);
		void setUsername(const string& username);
		void setPassword(const string& password);
		void changeUsername(const string& oldUsername, const string& newUsername);
		void changePassword(const string& oldPassword, const string& newPassword);
		bool checkForLoggedIn();
		void addUserToTable(const User& user);
		void createUserDatabase(const string& username);
		void login(const string& username, const string& password);
		static int USER_ID;
		void addEvent(const string& description, const int& month, const int& day, const int& year);
};


#endif