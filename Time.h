#pragma once
#ifndef TIME_H
#define TIME_H

class Time {
private:
    int hour = 0, minute = 0;

public:
    void setTime(int hour, int minute);
};
#endif 