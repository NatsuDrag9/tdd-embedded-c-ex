#include "CppUTest/TestHarness.h"

extern "C"
{
#include "../inc/AlarmClockService.h"
#include "../inc/FakeTimeService.h"
}

/* Helper functions */
static void setAlarmPeriodAndCallback(unsigned long ticksOfHundredms, WakeUpCallback callback)
{
    TimeService_SetAlarmPeriodAndCallback(ticksOfHundredms, callback);
}

static void resetAlarmPeriodAndCallback(unsigned long ticksOfHundredms, WakeUpCallback callback)
{
    TimeService_ResetAlarmPeriodAndCallback(ticksOfHundredms, callback);
}

/*
 * Implementation of alarm clock service initial tests
 * that check whether appropriate callback is returned
 */
TEST_GROUP(AlarmClockServiceInitAndCleanup){};

TEST(AlarmClockServiceInitAndCleanup, CallbackAfterSecond)
{
    setAlarmPeriodAndCallback(TICKS_OF_HUNDRED_MS_FOR_SECOND, AlarmClockService_WakeupAfterSecond);
    POINTERS_EQUAL((void *)AlarmClockService_WakeupAfterSecond, (void *)FakeTimeService_GetAlarmCallback());
    LONGS_EQUAL(TICKS_OF_HUNDRED_MS_FOR_SECOND, FakeTimeService_GetAlarmPeriod());
    resetAlarmPeriodAndCallback(TICKS_OF_HUNDRED_MS_FOR_SECOND, AlarmClockService_WakeupAfterSecond);
}

TEST(AlarmClockServiceInitAndCleanup, CallbackAfterMinute)
{
    setAlarmPeriodAndCallback(TICKS_OF_HUNDRED_MS_FOR_MINUTE, AlarmClockService_WakeupAfterMinute);
    POINTERS_EQUAL((void *)AlarmClockService_WakeupAfterMinute, (void *)FakeTimeService_GetAlarmCallback());
    LONGS_EQUAL(TICKS_OF_HUNDRED_MS_FOR_MINUTE, FakeTimeService_GetAlarmPeriod());
    resetAlarmPeriodAndCallback(TICKS_OF_HUNDRED_MS_FOR_MINUTE, AlarmClockService_WakeupAfterMinute);
}

TEST(AlarmClockServiceInitAndCleanup, CallbackAfterHour)
{
    setAlarmPeriodAndCallback(TICKS_OF_HUNDRED_MS_FOR_HOUR, AlarmClockService_WakeupAfterHour);
    POINTERS_EQUAL((void *)AlarmClockService_WakeupAfterHour, (void *)FakeTimeService_GetAlarmCallback());
    LONGS_EQUAL(TICKS_OF_HUNDRED_MS_FOR_HOUR, FakeTimeService_GetAlarmPeriod());
    resetAlarmPeriodAndCallback(TICKS_OF_HUNDRED_MS_FOR_HOUR, AlarmClockService_WakeupAfterHour);
}

TEST(AlarmClockServiceInitAndCleanup, CallbackAfterDay)
{
    setAlarmPeriodAndCallback(TICKS_OF_HUNDRED_MS_FOR_DAY, AlarmClockService_WakeupAfterDay);
    POINTERS_EQUAL((void *)AlarmClockService_WakeupAfterDay, (void *)FakeTimeService_GetAlarmCallback());
    LONGS_EQUAL(TICKS_OF_HUNDRED_MS_FOR_DAY, FakeTimeService_GetAlarmPeriod());
    resetAlarmPeriodAndCallback(TICKS_OF_HUNDRED_MS_FOR_DAY, AlarmClockService_WakeupAfterDay);
}

TEST(AlarmClockServiceInitAndCleanup, CallbackAfterMonth)
{
    setAlarmPeriodAndCallback(TICKS_OF_HUNDRED_MS_FOR_MONTH, AlarmClockService_WakeupAfterMonth);
    POINTERS_EQUAL((void *)AlarmClockService_WakeupAfterMonth, (void *)FakeTimeService_GetAlarmCallback());
    LONGS_EQUAL(TICKS_OF_HUNDRED_MS_FOR_MONTH, FakeTimeService_GetAlarmPeriod());
    resetAlarmPeriodAndCallback(TICKS_OF_HUNDRED_MS_FOR_MONTH, AlarmClockService_WakeupAfterMonth);
}

TEST(AlarmClockServiceInitAndCleanup, CallbackAfterYear)
{
    setAlarmPeriodAndCallback(TICKS_OF_HUNDRED_MS_FOR_YEAR, AlarmClockService_WakeupAfterYear);
    POINTERS_EQUAL((void *)AlarmClockService_WakeupAfterYear, (void *)FakeTimeService_GetAlarmCallback());
    LONGS_EQUAL(TICKS_OF_HUNDRED_MS_FOR_YEAR, FakeTimeService_GetAlarmPeriod());
    resetAlarmPeriodAndCallback(TICKS_OF_HUNDRED_MS_FOR_YEAR, AlarmClockService_WakeupAfterYear);
}

/* Implementation of alarm clock service tests */
TEST_GROUP(AlarmClockService)
{
};

TEST(AlarmClockService, CallbackAfterSecond){
    LONGS_EQUAL(CALLED_WAKEUP_AFTER_SECOND, AlarmClockService_RunCallback(TICKS_OF_HUNDRED_MS_FOR_SECOND));
}

TEST(AlarmClockService, CallbackAfterMinute){
    LONGS_EQUAL(CALLED_WAKEUP_AFTER_MINUTE, AlarmClockService_RunCallback(TICKS_OF_HUNDRED_MS_FOR_MINUTE));
}

TEST(AlarmClockService, CallbackAfterHour){
    LONGS_EQUAL(CALLED_WAKEUP_AFTER_HOUR, AlarmClockService_RunCallback(TICKS_OF_HUNDRED_MS_FOR_HOUR));
}

TEST(AlarmClockService, CallbackAfterDay){
    LONGS_EQUAL(CALLED_WAKEUP_AFTER_DAY, AlarmClockService_RunCallback(TICKS_OF_HUNDRED_MS_FOR_DAY));
}

TEST(AlarmClockService, CallbackAfterMonth){
    LONGS_EQUAL(CALLED_WAKEUP_AFTER_MONTH, AlarmClockService_RunCallback(TICKS_OF_HUNDRED_MS_FOR_MONTH));
}

TEST(AlarmClockService, CallbackAfterYear){
    LONGS_EQUAL(CALLED_WAKEUP_AFTER_YEAR, AlarmClockService_RunCallback(TICKS_OF_HUNDRED_MS_FOR_YEAR));
}