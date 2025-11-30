#pragma once

#ifndef DATE_H
#define DATE_H
#include<iostream>

class Date {
private:
    int month = 0, day = 0, year = 0;


public:
    void setDate(int month, int day, int year);
    int getMonth();
    int getDay();
    int getYear();
};

#endif
