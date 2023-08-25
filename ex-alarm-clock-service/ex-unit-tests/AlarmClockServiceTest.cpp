#include "CppUTest/TestHarness.h"

extern "C"
{
#include "../inc/AlarmClockService.h"
#include "../inc/FakeTimeService.h"
}

/* Helper functions */
static void setAlarmPeriodAndCallback(unsigned long ticksOfHundredms, WakeUpCallback callback){
    TimeService_SetAlarmPeriodAndCallback(ticksOfHundredms, callback);
}

static void resetAlarmPeriodAndCallback(unsigned long ticksOfHundredms, WakeUpCallback callback){
    TimeService_ResetAlarmPeriodAndCallback(ticksOfHundredms, callback);
}

/* Implementation of alarm clock service tests */
TEST_GROUP(AlarmClockServiceCallbacks){};

TEST(AlarmClockServiceCallbacks, CallbackAfterSecond)
{
    setAlarmPeriodAndCallback(TICKS_OF_HUNDRED_MS_FOR_SECOND, AlarmClockService_WakeupAfterSecond);
    POINTERS_EQUAL((void *)AlarmClockService_WakeupAfterSecond, (void *)FakeTimeService_GetAlarmCallback());
    LONGS_EQUAL(10, FakeTimeService_GetAlarmPeriod());
    resetAlarmPeriodAndCallback(TICKS_OF_HUNDRED_MS_FOR_SECOND, AlarmClockService_WakeupAfterSecond);
}

TEST(AlarmClockServiceCallbacks, CallbackAfterMinute)
{

}