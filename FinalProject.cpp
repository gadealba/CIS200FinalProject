// FinalProject.cpp : This file contains the 'main' function. Program execution begins and ends there.
//
#include <iostream>
#include "Date.h"
#include "Event.h"
#include "User.h"
int main() {

    User user;
    string userResponse;
    while (!user.checkForLoggedIn()) { // loops until user creates account or logs in.
        cout << "If you are a new user please type \"new\". If not please type \"login\" " <<endl;
        cin >> userResponse;
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        ;
        while (userResponse !="new" && userResponse != "login") { // validating response.
            cin.clear();
            cout << "Error: input was invalid, please make sure to not have caps lock on." << endl;
            cin >> userResponse;
            

        }
        //create or login logic.
    }
    string description = "birthday party";
    Event myEvent;
    myEvent.createEvent(description, 11, 25, 2025);
    myEvent.print();
    return 0;
}


