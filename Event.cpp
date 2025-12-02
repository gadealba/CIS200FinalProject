#include "Event.h"
#include "Date.h"
#include <iomanip>

void Event::createEvent(string& description, int& month, int& day, int& year) {
    this->description = description;
    this->date.setDate(month, day, year);
    this->time.setTime(0, 0);
}
void Event::createEvent(string& description, int& month, int& day, int& year, int& hour, int& mins) {
    this->description = description;
    this->date.setDate(month, day, year);
    this->time.setTime(hour, mins);
}

void Event::print() {
    if (this->time.getHour() == 0 && this->time.getMins() == 0) {
        std::cout << this->description << " is on "
            << this->date.getMonth() << "/"
            << this->date.getDay()
            << "/" << this->date.getYear() << endl;
        return;
    }
    std::cout << this->description << " is on "
        << this->date.getMonth() << "/"
        << this->date.getDay()
        << "/" << this->date.getYear() << " at " << this->time.getHour() << ":"
        << std::setfill('0') << std::setw(2) << this->time.getMins() << "." << endl;

}
string Event::getDescription() {
    return this->description;
}
Date Event::getDate() {
    return this->date;
}
Time Event::getTime() {
    return this->time;
}
//Event::Event(){}