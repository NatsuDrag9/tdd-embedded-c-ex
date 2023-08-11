#include "../inc/LightScheduler.h"
#include <stdio.h>

// Private data structures and variables
enum
{
    UNUSED = -1,
    TURN_ON,
    TURN_OFF,
    MAX_EVENTS = 128
};

typedef struct
{
    int id;
    int minuteOfDay;
    Day day;
    int event;
} ScheduledLightEvent;

static ScheduledLightEvent scheduledEvent;
static ScheduledLightEvent scheduledEvents[MAX_EVENTS];

// Local and helper functions declarations
static void processEventDueNow(Time *, ScheduledLightEvent *);
static void operateLight(ScheduledLightEvent *);
static bool doesLightRespondToday(Time *, ScheduledLightEvent *);
static int scheduleEvent(int, Day, int, int);

// Helper function definitions
static bool doesLightRespondToday(Time *ptrTime, ScheduledLightEvent *ptrLightEvent)
{
    int today = ptrTime->dayOfWeek;
    int lightTriggerDay = ptrLightEvent->day;

    if (lightTriggerDay == EVERYDAY)
    {
        return true;
    }
    if (lightTriggerDay == today)
    {
        return true;
    }
    if ((lightTriggerDay == WEEKEND) && ((today == SATURDAY || today == SUNDAY)))
    {
        return true;
    }
    if ((lightTriggerDay == WEEKDAY) && (today >= MONDAY && today <= FRIDAY))
    {
        return true;
    }
    return false;
}

static void operateLight(ScheduledLightEvent *ptrLightEvent)
{
    if (ptrLightEvent->event == TURN_ON)
    {
        LightController_On(ptrLightEvent->id);
    }
    else if (ptrLightEvent->event == TURN_OFF)
    {
        LightController_Off(ptrLightEvent->id);
    }
}

static void processEventDueNow(Time *ptrTime, ScheduledLightEvent *ptrLightEvent)
{

    if (ptrLightEvent->id == UNUSED)
    {
        return;
    }

    // Checks whether the current time matches the scheduled timed
    if (ptrTime->minuteOfDay != ptrLightEvent->minuteOfDay)
    {
        return;
    }

    if (!doesLightRespondToday(ptrTime, ptrLightEvent))
    {
        return;
    }

    operateLight(ptrLightEvent);
}

/* For single event and many events */
static int scheduleEvent(int id, Day day, int minuteOfDay, int event)
{
    int i;

    if (id < 0 || id > MAX_LIGHTS-1)
    {
        return LS_ID_OUT_OF_BOUNDS;
    }

    for (i = 0; i < MAX_EVENTS; i++)
    {

        if (scheduledEvents[i].id == UNUSED)
        {
            scheduledEvents[i].id = id;
            scheduledEvents[i].day = day;
            scheduledEvents[i].minuteOfDay = minuteOfDay;
            scheduledEvents[i].event = event;
            return LS_OK;
        }
    }
    return LS_TOO_MANY_EVENTS;
}

// API implementation
void LightScheduler_Create(void)
{
    int i;
    scheduledEvent.id = UNUSED;

    for (i = 0; i < MAX_EVENTS; i++)
    {
        scheduledEvents[i].id = UNUSED;
    }

    TimeService_SetPeriodicAlarmInSeconds(60, LightScheduler_Wakeup);
}

int LightScheduler_ScheduleTurnOff(int id, Day day, int minuteOfDay)
{
    return scheduleEvent(id, day, minuteOfDay, TURN_OFF);

    /* For single event */
    // scheduledEvent.id = id;
    // scheduledEvent.minuteOfDay = minuteOfDay;
    // scheduledEvent.day = day;
    // scheduledEvent.event = TURN_OFF;
}

int LightScheduler_ScheduleTurnOn(int id, Day day, int minuteOfDay)
{
    return scheduleEvent(id, day, minuteOfDay, TURN_ON);

    /* For single event */
    // scheduledEvent.id = id;
    // scheduledEvent.minuteOfDay = minuteOfDay;
    // scheduledEvent.day = day;
    // scheduledEvent.event = TURN_ON;
}

void LightScheduler_Wakeup(void)
{
    int i;
    Time time;
    TimeService_GetTime(&time);

    /* For single event */
    // processEventDueNow(&time, &scheduledEvent);

    /* For single event and many events */
    for (i = 0; i < MAX_EVENTS; i++)
    {
        processEventDueNow(&time, &scheduledEvents[i]);
    }
}

void LightScheduler_ScheduleRemove(int id, Day day, int minuteOfDay)
{
    int i;
    for (i = 0; i < MAX_EVENTS; i++)
    {
        if (scheduledEvents[i].id == id && scheduledEvents[i].day == day &&
            scheduledEvents[i].minuteOfDay == minuteOfDay)
        {
            scheduledEvents[i].event = UNUSED;
        }
    }
}

void LightScheduler_Destroy(void)
{
    TimeService_CancelPeriodicAlarmInSeconds(60, LightScheduler_Wakeup);
}