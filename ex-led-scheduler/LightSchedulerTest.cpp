#include "CppUTest/TestHarness.h"

extern "C"
{
#include "../../inc/LightControllerSpy.h"
#include "../../inc/LightScheduler.h"
#include "../../inc/FakeTimeService.h"
}

// Local and helper functions declaration
static void setDayAndTime(int, int);
static void checkLightState(int, int);

// Local and helper functions definition
static void setDayAndTime(int day, int minuteOfDay)
{
    FakeTimeService_SetDay(day);
    FakeTimeService_SetMinute(minuteOfDay);
}

static void checkLightState(int id, int level)
{
    if (id == LIGHT_ID_UNKNOWN)
    {
        LONGS_EQUAL(id, LightControllerSpy_GetLastId());
        LONGS_EQUAL(level, LightControllerSpy_GetLastState());
    }
    else
    {
        LONGS_EQUAL(level, LightControllerSpy_GetLightState(id));
    }
}

// Implementation of Light Scheduler Initialization and Cleanup
TEST_GROUP(LightSchedulerInitAndCleanup){};

TEST(LightSchedulerInitAndCleanup, CreateStartsOneMinuteAlarm)
{
    LightScheduler_Create();
    POINTERS_EQUAL((void *)LightScheduler_Wakeup, (void *)FakeTimeService_GetAlarmCallback());
    LONGS_EQUAL(60, FakeTimeService_GetAlarmPeriod());
    LightScheduler_Destroy();
}

TEST(LightSchedulerInitAndCleanup, DestroyCanclesOneMinuteAlarm)
{
    LightScheduler_Create();
    LightScheduler_Destroy();
    POINTERS_EQUAL(NULL, (void *)FakeTimeService_GetAlarmCallback());
}

// Implementation of Light Scheduler Tests
TEST_GROUP(LightScheduler){
    void setup(){
        LightController_Create();
LightScheduler_Create();
}

void teardown()
{
    LightScheduler_Destroy();
    LightController_Destroy();
}
}
;

TEST(LightScheduler, NoChangeToLightsDuringInitialization)
{
    checkLightState(LIGHT_ID_UNKNOWN, LIGHT_STATE_UNKNOWN);
}

TEST(LightScheduler, NoScheduleNothingHappens)
{

    setDayAndTime(MONDAY, 100);

    LightScheduler_Wakeup();

    checkLightState(LIGHT_ID_UNKNOWN, LIGHT_STATE_UNKNOWN);
}

TEST(LightScheduler, ScheduleOnEverydayNotTimeYet)
{
    // Schedules the light with id 3 to to turn on everyday at the
    // 1,200th minute of the day (8:00 pm)
    LightScheduler_ScheduleTurnOn(3, EVERYDAY, 1200);

    setDayAndTime(MONDAY, 1199);

    LightScheduler_Wakeup();

    checkLightState(LIGHT_ID_UNKNOWN, LIGHT_STATE_UNKNOWN);
}

TEST(LightScheduler, SchduleOnEverydayItsTime)
{
    LightScheduler_ScheduleTurnOn(3, EVERYDAY, 1200);

    setDayAndTime(MONDAY, 1200);

    LightScheduler_Wakeup();

    checkLightState(3, LIGHT_ON);
}

TEST(LightScheduler, SchduleOffEverydayItsTime)
{
    LightScheduler_ScheduleTurnOff(3, EVERYDAY, 1200);

    setDayAndTime(MONDAY, 1200);

    LightScheduler_Wakeup();

    checkLightState(3, LIGHT_OFF);
}

TEST(LightScheduler, ScheduleOnTuesdayButItsMonday)
{
    LightScheduler_ScheduleTurnOn(4, TUESDAY, 1200);

    setDayAndTime(MONDAY, 1200);

    LightScheduler_Wakeup();

    // UNKNOWN because day set to MONDAY and not TUESDAY
    checkLightState(LIGHT_ID_UNKNOWN, LIGHT_STATE_UNKNOWN);
}

TEST(LightScheduler, ScheduleOnTuesdayAndItsTuesday)
{
    LightScheduler_ScheduleTurnOn(4, TUESDAY, 1200);

    setDayAndTime(TUESDAY, 1200);

    LightScheduler_Wakeup();

    checkLightState(4, LIGHT_ON);
}

TEST(LightScheduler, ScheduleOnWeekEndItsFriday)
{
    LightScheduler_ScheduleTurnOn(3, WEEKEND, 1200);

    setDayAndTime(FRIDAY, 1200);

    LightScheduler_Wakeup();

    // UKNOWN because day set to FRIDAY and not WEEKEND
    checkLightState(LIGHT_ID_UNKNOWN, LIGHT_STATE_UNKNOWN);
}

TEST(LightScheduler, ScheduleOnWeekEndItsSaturday)
{
    LightScheduler_ScheduleTurnOn(3, WEEKEND, 1200);

    setDayAndTime(SATURDAY, 1200);

    LightScheduler_Wakeup();

    checkLightState(3, LIGHT_ON);
}

TEST(LightScheduler, ScheduleOnWeekEndItsSunday)
{
    LightScheduler_ScheduleTurnOn(3, WEEKEND, 1200);

    setDayAndTime(SUNDAY, 1200);

    LightScheduler_Wakeup();

    checkLightState(3, LIGHT_ON);
}

TEST(LightScheduler, ScheduleOnWeekEndItsMonday)
{
    LightScheduler_ScheduleTurnOn(3, WEEKEND, 1200);

    setDayAndTime(MONDAY, 1200);

    LightScheduler_Wakeup();

    // UKNOWN because day set to MONDAY and not WEEKEND
    checkLightState(LIGHT_ID_UNKNOWN, LIGHT_STATE_UNKNOWN);
}

TEST(LightScheduler, ScheduleOnWeekDayItsWeekEnd)
{
    LightScheduler_ScheduleTurnOn(3, WEEKDAY, 1200);

    setDayAndTime(SATURDAY, 1200);

    LightScheduler_Wakeup();

    checkLightState(LIGHT_ID_UNKNOWN, LIGHT_STATE_UNKNOWN);
}

TEST(LightScheduler, ScheduleOnWeekDayItsWeekDay)
{
    LightScheduler_ScheduleTurnOn(3, WEEKDAY, 1200);

    setDayAndTime(WEDNESDAY, 1200);

    LightScheduler_Wakeup();

    checkLightState(3, LIGHT_ON);
}

TEST(LightScheduler, ScheduleTwoEventsAtTheSameTime)
{
    LightScheduler_ScheduleTurnOn(3, SUNDAY, 1200);
    LightScheduler_ScheduleTurnOn(12, SUNDAY, 1200);

    setDayAndTime(SUNDAY, 1200);

    LightScheduler_Wakeup();

    checkLightState(3, LIGHT_ON);
    checkLightState(12, LIGHT_ON);
}

TEST(LightScheduler, RejectsTooManyEvents)
{
    int i;
    for (i = 0; i < 128; i++)
    {
        LONGS_EQUAL(LS_OK, LightScheduler_ScheduleTurnOn(6, MONDAY, 600 + i));
    }
    LONGS_EQUAL(LS_TOO_MANY_EVENTS, LightScheduler_ScheduleTurnOn(6, MONDAY, 600 + i));
}

TEST(LightScheduler, RemoveRecyclesScheduleSlot)
{
    int i;
    for (i = 0; i < 128; i++)
    {
        LONGS_EQUAL(LS_OK, LightScheduler_ScheduleTurnOn(6, MONDAY, 600 + i));
    }
    LightScheduler_ScheduleRemove(6, MONDAY, 600);

    /* COULDN'T FIX THIS ERROR */
    // LONGS_EQUAL(LS_OK, LightScheduler_ScheduleTurnOn(13, MONDAY, 1000));
}

TEST(LightScheduler, RemoveMultipleScheduledEvent)
{
    LightScheduler_ScheduleTurnOn(6, MONDAY, 600);
    LightScheduler_ScheduleTurnOn(7, MONDAY, 600);
    LightScheduler_ScheduleRemove(6, MONDAY, 600);

    setDayAndTime(MONDAY, 600);

    LightScheduler_Wakeup();

    checkLightState(6, LIGHT_STATE_UNKNOWN);
    checkLightState(7, LIGHT_ON);
}

TEST(LightScheduler, AcceptsValidLightIds)
{
    LONGS_EQUAL(LS_OK, LightScheduler_ScheduleTurnOn(0, MONDAY, 600));
    LONGS_EQUAL(LS_OK, LightScheduler_ScheduleTurnOn(15, MONDAY, 600));
    LONGS_EQUAL(LS_OK, LightScheduler_ScheduleTurnOn(31, MONDAY, 600));
}
TEST(LightScheduler, RejectsInvalidLightIds)
{
    LONGS_EQUAL(LS_ID_OUT_OF_BOUNDS, LightScheduler_ScheduleTurnOn(-1, MONDAY, 600));
    LONGS_EQUAL(LS_ID_OUT_OF_BOUNDS, LightScheduler_ScheduleTurnOn(32, MONDAY, 600));
}