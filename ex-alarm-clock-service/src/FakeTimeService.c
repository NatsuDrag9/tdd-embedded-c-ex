#include <stddef.h>
#include "../inc/FakeTimeService.h"

/* Private variables */
static unsigned long alarmPeriod;
static WakeUpCallback callback;

/* Implementation of APIs */
void TimeService_Create(void){
    alarmPeriod = 0;
    callback = NULL;
}

void TimeService_SetAlarmPeriodAndCallback(unsigned long ticksOfHundredms, WakeUpCallback cb){
    alarmPeriod = ticksOfHundredms;
    callback = cb;
}

void TimeService_ResetAlarmPeriodAndCallback(unsigned long noOfHundredms, WakeUpCallback cb){
    if (noOfHundredms == alarmPeriod && cb == callback){
        alarmPeriod = 0;
        cb = NULL;
    }
}

WakeUpCallback FakeTimeService_GetAlarmCallback(void){
    return callback;
}

unsigned long FakeTimeService_GetAlarmPeriod(void){
    return alarmPeriod;
}

void TimerService_Destroy(void){
    
}