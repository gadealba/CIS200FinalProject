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
    //Event();
    void createEvent(string description, int month, int day, int year);
    void print();



};

#endif

