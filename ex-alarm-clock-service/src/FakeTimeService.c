#include "../inc/FakeTimeService.h"

/* Private variables */
static Time fakeTime;

void TimeService_Create(void){
    fakeTime.dayOfWeek = -1;
    fakeTime.minuteOfDay = -1;
}

/* Implementation of APIs */
void FakeTimeService_SetDay(int day){
    fakeTime.dayOfWeek = day;
}

void FakeTimeService_SetTime(int minute){
    fakeTime.minuteOfDay = minute;
}

void TimeService_GetTime(Time* time){
    time->dayOfWeek = fakeTime.dayOfWeek;
    time->minuteOfDay = fakeTime.minuteOfDay;
}

void TimerService_Destroy(void){
    
}