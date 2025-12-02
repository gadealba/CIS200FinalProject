// FinalProject.cpp : This file contains the 'main' function. Program execution begins and ends there.

#include <iostream>
#include <cstdlib>  // For system()
#include <iomanip>  // For setfill and setw
#include "Date.h"
#include "Event.h"
#include "User.h"

void clearScreen();
void setUpInfo(string& userResponse, string& string);
void addEventDetails(string& description, int& month, int& day, int& year, int& hour, int& mins);

// Cross-platform screen clearing function
void clearScreen() {
#ifdef _WIN32
    system("cls");  // Windows
#else
    system("clear");  // Linux/Mac
#endif
}

int main() {
    string description;
    int month, day, year, hour = 0, mins = 0;
    User currentUser;
    string username;
    string password;
    string userResponse;

    bool programRunning = true;

    while (programRunning) {
        while (!currentUser.checkForLoggedIn()) { // loops until user creates account or logs in.
            clearScreen();
            cout << "If you are a new user please type [new]. If not please type [login]. To exit type [quit]" << endl;
            cin >> userResponse;
            cin.ignore(numeric_limits<streamsize>::max(), '\n');

            if (userResponse == "quit") {
                programRunning = false;
                break; // Exit login loop
            }

            while (userResponse != "new" && userResponse != "login") { // validating response.
                cin.clear();
                cout << "Error: input was invalid, please make sure to not have caps lock on." << endl;
                cin >> userResponse;


            }
            if (userResponse == "new") { // creates new user.
                clearScreen();
                cout << " please set up your username." << endl;
                setUpInfo(userResponse, username);
                currentUser.setUsername(username);
                clearScreen();
                cout << "Please set up your password." << endl;
                setUpInfo(userResponse, password);
                currentUser.setPassword(password); // maybe add some password requirements?
                currentUser.addUserToTable(currentUser); // isLoggedin = true now.
            }
            else if (userResponse == "login") {
                while (true) {
                    clearScreen();
                    cout << "Please enter your username (or type 'back' to return to main menu, 'quit' to exit):" << endl;
                    cin >> username;
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');

                    if (username == "back") {
                        break; // Go back to login/new user screen
                    }
                    if (username == "quit") {
                        programRunning = false;
                        break; // Exit program
                    }

                    cout << "Please enter your password (or type 'back' to return, 'quit' to exit):" << endl;
                    cin >> password;
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');

                    if (password == "back") {
                        continue; // Go back to username prompt
                    }
                    if (password == "quit") {
                        programRunning = false;
                        break; // Exit program
                    }

                    if (currentUser.checkForUser(username, password)) {
                        break;
                    }
                    else {
                        cout << "\nLogin failed. Incorrect username or password." << endl;
                        cout << "Press Enter to try again...";
                        cin.get();
                    }
                }
            }
        }
        while (userResponse != "quit") {
            clearScreen();
            cout << "Please one of the following options:\n[event] adds an event to your account." <<
                "\n[view] shows all the events related to this account." <<
                "\n[logout] to logout and return to login screen." <<
                "\n[quit] to quit the program.";
            cin >> userResponse;
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            if (userResponse == "event") {
                clearScreen();
                addEventDetails(description, month, day, year, hour, mins);
                if (description == "" || month == 0 || day == 0 || year == 0) {
                    continue;
                }
                if (hour == 0 && mins == 0) {
                    currentUser.createEvent(description, month, day, year);
                }
                else if (hour > 0 || mins > 0) {
                    currentUser.createEvent(description, month, day, year, hour, mins);
                }
                cout << "\nEvent created successfully! Press Enter to continue...";
                cin.get();
            }
            if (userResponse == "view") {
                clearScreen();
                currentUser.printAllEvents();
                cout << "Press Enter to continue...";
                cin.get();
            }
            if (userResponse == "logout") {
                currentUser.logout();
                break; // Exit inner loop to go back to login screen
            }
        }

        if (userResponse == "quit") {
            programRunning = false; // Exit outer loop to quit program
        }
    }
    return 0;
}

void setUpInfo(string& userResponse, string& string) { // creates new user.
    cin >> string;
    while (true) { // asking user to confirm.
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
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }
        if (userResponse == "yes") { break; }// leaves loop and continues on.
    }
}
void addEventDetails(string& description, int& month, int& day, int& year, int& hours, int& mins) {
    description = ""; month = 0; day = 0; year = 0;//resets the data.

    string userResponse;
    cout << "Please submit a description for the event." << endl;
    getline(cin, description);
    while (true) {
        cout << "Would you like to save the description?[yes]/[no]/[quit]" << endl;
        cin >> userResponse;
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        if (userResponse == "quit") { return; }
        if (userResponse == "yes") {
            break;
        }
        if (userResponse == "no") {
            cout << "Please submit a description for the event." << endl;
            getline(cin, description);
            continue;
        }
        else if (userResponse != "yes" && userResponse != "no" && userResponse != "quit") {
            cout << "Please make sure you do not have caps lock on." << endl;
            continue;
        }
        cout << "Please submit a description for the event." << endl;
        cin >> description;
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }
    cout << "Please enter the month, day, and year of the event, are all separated by the [enter] key between inputs. (Please note that these should be numerical inputs such as 12 instead of December)" << endl;
    while (true) {
        try {
            cin.exceptions(ios::failbit);
            cin >> month >> day >> year;
        }
        catch (const ios_base::failure& e) {
            std::cerr << "Caught exception: " << e.what() << "Please separate the month, day, and year, by the [enter] key between numerical inputs. " << "\n";
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Please enter the month, day, and year of the event, as numerical inputs only." << endl;
            continue;
        }
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        break;
    }
    while (true) {
        cout << "You have put " << month << "/" << day << "/" << year << "\n is this correct? [yes]/[no]/[quit]" << endl;
        cin >> userResponse;
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        if (userResponse != "yes" && userResponse != "no" && userResponse != "quit") {
            cout << "Please make sure you dod not have caps lock on." << endl;
            continue;
        }
        if (userResponse == "quit") { month = 0; day = 0; year = 0; return; }
        if (userResponse == "yes") {
            break;
        }
        clearScreen();
        cout << "Please enter the month, day, and year of the event, as numerical inputs only." << endl;
        try {
            cin.exceptions(ios::failbit);
            cin >> month >> day >> year;
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }
        catch (const ios_base::failure& e) {
            std::cerr << "Caught exception: " << e.what() << " Please enter numeric values only." << "\n";
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            continue;
        }
    }
    cout << " would you like to add a time?[yes]/[no]" << endl;
    cin >> userResponse;
    while (userResponse != "yes" && userResponse != "no") {
        cout << "Error: that response was invalid, please try again." << endl;
        cout << " would you like to add a time?[yes]/[no]" << endl;
        cin >> userResponse;
    }
    if (userResponse == "yes") {
        cout << "please type the hour and mins separated by the [enter] key between inputs" << endl;
        while (true) {
            try { cin >> hours >> mins; }
            catch (const ios_base::failure& e) {
                std::cerr << "Caught exception: " << e.what() << "Please separate the hour and minute by the [enter] key between inputs." << "\n";
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                cout << "please type the hour and mins separated by the [enter] key between inputs." << endl;
                continue;
            }
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "you have selected " << hours << ":" << setfill('0') << setw(2) << mins << ". Is this correct?[yes]/[no]/[quit]" << endl;
            cin >> userResponse;
            while (userResponse != "yes" && userResponse != "no" && userResponse != "quit") {
                cout << "Error: that input was invalid, please try again." << endl;
                cin >> userResponse;
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
            }
            if (userResponse == "quit") { month = 0; day = 0; year = 0; return; }
            if (userResponse == "no") {
                clearScreen();
                cout << "please type the hour and mins separated by the [enter] key" << endl;
                continue;
            }
            if (userResponse == "yes") { break; }
        }
    }
    if (userResponse == "no") {
        return;
    }
}