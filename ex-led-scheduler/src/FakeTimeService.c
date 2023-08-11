#include <stddef.h>
#include "../inc/FakeTimeService.h"

static Time fakeTime;
static WakeUpCallback callback;
static int period;

void TimeService_Create(void)
{
    fakeTime.minuteOfDay = -1;
    fakeTime.dayOfWeek = -1;
    callback = NULL;
    period = -1;
}

void TimeService_Destroy(void)
{
}

void FakeTimeService_SetDay(int dayOfWeek)
{
    fakeTime.dayOfWeek = dayOfWeek;
}

void FakeTimeService_SetMinute(int minuteOfDay)
{
    fakeTime.minuteOfDay = minuteOfDay;
}

void TimeService_GetTime(Time *time)
{
    time->dayOfWeek = fakeTime.dayOfWeek;
    time->minuteOfDay = fakeTime.minuteOfDay;
}

void TimeService_SetPeriodicAlarmInSeconds(int seconds, WakeUpCallback cb)
{
    callback = cb;
    period = seconds;
}

void TimeService_CancelPeriodicAlarmInSeconds(int seconds, WakeUpCallback cb)
{
    if (cb == callback && period == seconds){
        callback = NULL;
        period = 0;
    }
}

WakeUpCallback FakeTimeService_GetAlarmCallback(void){
    return callback;
}

int FakeTimeService_GetAlarmPeriod(void){
    return period;
}