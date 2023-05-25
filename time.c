
#include <stdlib.h>
#include "time.h"

Time *createTime(int hour, int minute, int second)
{
    Time *timeInst = (Time *)malloc(sizeof(Time));
    timeInst->hour = hour;
    timeInst->minute = minute;
    timeInst->second = second;
    return timeInst;
}

Time *addTime(Time *timeInst, int seconds)
{
    int hour = timeInst->hour;
    int minute = timeInst->minute;
    int second = timeInst->second + seconds;
    minute += second / 60;
    second %= 60;
    hour += minute / 60;
    minute %= 60;
    return createTime(hour, minute, second);
}

int compareTimes(Time *time1, Time *time2)
{
    int seconds1 = time1->hour * 3600 + time1->minute * 60 + time1->second;
    int seconds2 = time2->hour * 3600 + time2->minute * 60 + time2->second;
    if (seconds1 < seconds2)
        return -1;
    if (seconds1 == seconds2)
        return 0;
    return 1;
}

void freeTime(Time *time)
{
    free(time);
}
