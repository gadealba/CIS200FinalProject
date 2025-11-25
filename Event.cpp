#include "Event.h"
#include "Date.h"

void Event::createEvent(string description, int month, int day, int year) {
    this->description = description;
    this->date.setDate(month, day, year);
}

void Event::print() {
    std::cout << this->description << " is on " << this->date.getMonth() << "/" << this->date.getDay() << "/" << this->date.getYear();
}
//Event::Event(){}
