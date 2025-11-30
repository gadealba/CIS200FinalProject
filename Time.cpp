#include "Time.h"

void Time::setTime(const int& hour,const int& mins) {
	this->hour = hour;
	this->mins = mins;
}

int Time::getHour() {
	return this->hour;
}
int Time::getMins() {
	return this->mins;
}

