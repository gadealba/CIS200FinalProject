#pragma once

#ifndef EVENT_H
#define EVENT_H

#include <iostream>
#include "Date.h"
#include "Time.h"
using namespace std;
class Event {
private:
    string description;
    Date date;
    Time time;
public:
    void createEvent(string& description, int& month, int& day, int& year);
    void createEvent(string& description, int& month, int& day, int& year, int& hour, int& mins);
    void print();
    string getDescription();
    Date getDate();
    Time getTime();




};

#endif

