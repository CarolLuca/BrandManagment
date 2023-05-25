#ifndef TIME_H_
#define TIME_H_


#include <stdlib.h>

// time struct to keep the hour minute and second of an event
struct time
{
    int hour;
    int minute;
    int second;
};
typedef struct time Time;

// function to create time instance
Time *createTime(int hour, int minute, int second);

// function to add a certain number of seconds to a time instance
// and return a new instance with the correctly calculated
// hour minute and second
Time *addTime(Time *timeInst, int seconds);

// function to compare to time instances
int compareTimes(Time *time1, Time *time2);

// function to clear time instance
void freeTime(Time *time);

#endif