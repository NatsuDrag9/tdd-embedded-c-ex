#include "CppUTest/TestHarness.h"

extern "C"
{
#include "../inc/AlarmClockService.h"
#include "../inc/BuzzerControllerSpy.h"
#include "../inc/FakeTimeService.h"
}

/* Helper functions */
static void setDayAndTime(Day day, int time)
{
    FakeTimeService_SetDay(day);
    FakeTimeService_SetMinute(time);
}

static void checkBuzzerState(int buzzerId, int buzzerState)
{
    if (buzzerId == BUZZER_ID_UNKNOWN)
    {
        LONGS_EQUAL(buzzerId, BuzzerControllerSpy_GetLastBuzzerId());
        LONGS_EQUAL(buzzerState, BuzzerControllerSpy_GetLastBuzzerState());
    }
    LONGS_EQUAL(buzzerState, BuzzerControllerSpy_GetBuzzerState(buzzerId));
}

/* Implementation of alarm clock service tests */
TEST_GROUP(AlarmClockService){
    void setup(){

    }

    void teardown(){

    }};

TEST(AlarmClockService, NoBuzzerChangedDuringInitialization)
{
    checkBuzzerState(2, BUZZER_STATE_UNKNOWN);
}

TEST(AlarmClockService, DailyAlarmNotYetTime)
{

    // Schedules the light with id 1 to to turn on everyday at the
    // 1,200th minute of the day (8:00 pm)
    AlarmClockService_CreateAlarm(1, DAILY, 1200);
    AlarmClockService_Wakeup();

    setDayAndTime(MONDAY, 1199);
    // It's not time yet so the buzzer 1's state should be unknown
    checkBuzzerState(1, BUZZER_STATE_UNKNOWN);
}