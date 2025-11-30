#pragma once
#ifndef TIME_H
#define TIME_H

class Time {
private:
    int hour = 0, mins = 0;

public:
    void setTime(const int& hour, const int& mins);
    int getHour();
    int getMins();
};
#endif 