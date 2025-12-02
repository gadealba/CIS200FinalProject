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
	//int user_id;
	Event event;
	string inputFromFile;
	string username;
	string password;
	string fileName = "userTable.txt";
	string fileEvents = "";
	bool isLoggedin = 0;
	vector<Event> events;
	void addEventToTable(Event& event);
	void getSavedEvents();

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
	void logout();
	static int USER_ID;
	void createEvent(string& description, int& month, int& day, int& year);
	void createEvent(string& description, int& month, int& day, int& year, int& hour, int& mins);
	void printAllEvents();

};


#endif