// FinalProject.cpp : This file contains the 'main' function. Program execution begins and ends there.

#include <iostream>
#include "Date.h"
#include "Event.h"
#include "User.h"

void setUpInfo(string& userResponse,string& string);
void addEventDetails(string& description,int& month,int& day,int& year);

int main() {
    string description;
    int month, day, year;
    User currentUser;
    string username;
    string password;
    string userResponse;

    while (!currentUser.checkForLoggedIn()) { // loops until user creates account or logs in.
        cout << "If you are a new user please type [new]. If not please type [login] " <<endl;
        cin >> userResponse;
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        while (userResponse !="new" && userResponse != "login") { // validating response.
            cin.clear();
            cout << "Error: input was invalid, please make sure to not have caps lock on." << endl;
            cin >> userResponse;
            

        }
        if (userResponse == "new") { // creates new user.
            cout << " please set up your username." << endl;
            setUpInfo(userResponse, username);
            currentUser.setUsername(username);
            cout << "Please set up your password." << endl;
            setUpInfo(userResponse, password);
            currentUser.setPassword(password); // maybe add some password requirements?
            currentUser.addUserToTable(currentUser); // isLoggedin = true now.
        }
        else if (userResponse == "login") {
            while (true) {
                cout << "Please enter your username." << endl;
                cin >> username;
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                cout << "Please enter your password." << endl;
                cin >> password;
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                if (currentUser.checkForUser(username, password)) {
                    break;
                }
            }
        }   
    }
    while (userResponse != "quit") {
        cout << "please one of the following:\n[event] adds an event to your account." <<
            "\n[view] shows all the events related to this account." <<
            "\n[quit] to quit the program.";
        cin >> userResponse;
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        if (userResponse == "event") {
            addEventDetails(description,month,day,year);
            currentUser.addEvent(description, month, day, year);
        }
    }

    /*string description = "birthday party";
    Event myEvent;
    myEvent.createEvent(description, 11, 25, 2025);
    myEvent.print();*/
    return 0;
}

void setUpInfo(string& userResponse, string& string) { // creates new user.
    cin >> string;
    while (true) { // asking user to confirm username.
        cout << "you selected : [" << string << "] would you like to keep it? [yes / no]" << endl;
        cin >> userResponse;
        cin.ignore(numeric_limits<streamsize>::max(), '\n');

        while (userResponse != "yes" && userResponse != "no") {
            cin.clear();
            cout << "Error: invalid response. Please make sure to not have caps lock on." << endl;
            cin >> userResponse;
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }
        if (userResponse == "no") {
            cout << "please re-enter your selection." << endl;
            cin >> string;
        }
        if (userResponse == "yes") { break;}// leaves loop and continues on.
    }
}
void addEventDetails(string& description, int& month, int& day, int& year) {
    string userResponse;
    cout << "Please submit a description for the event." << endl;
    cin >> description;
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    while (true) {
        cout << "would you like to save the description?[yes]/[no]" << endl;
        cin >> userResponse;
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        if (userResponse == "yes") {
            break;
        }
        if (userResponse == "no") {
            cout << "Please submit a description for the event." << endl;
            cin >> description;
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            continue;
        }
        else if (userResponse != "yes" && userResponse != "no") {
            cout << "Please make sure you do not have caps lock on." << endl;
            continue;
        }
        cout << "Please submit a description for the event." << endl;
        cin >> description;
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }
    cout << "please enter the month day and year of the event." << endl;
    cin >> month >> day >> year;
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    while (true) {
        cout << "You have put " << month << "/" << day << "/" << year << "\n is this correct? [yes/[no]]" << endl;
        cin >> userResponse;
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        if (userResponse != "yes" && userResponse != "no") {
            cout << "please make sure you dod not have caps lock on." << endl;
            continue;
        }
        if (userResponse =="yes") {
            break;
        }
        cout << "please enter the month day and year of the event." << endl;
        cin >> month >> day >> year;
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        //add time perhaps here?
    }
}

