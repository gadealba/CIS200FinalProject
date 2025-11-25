#include "Date.h"

//Date::Date(){}

void Date::setDate(int month, int day, int year) {
    this->month = month;
    this->day = day;
    this->year = year;
}

int Date::getMonth() {
    return this->month;
}
int Date::getDay() {
    return this->day;
}
int Date::getYear() {
    return this->year;
}