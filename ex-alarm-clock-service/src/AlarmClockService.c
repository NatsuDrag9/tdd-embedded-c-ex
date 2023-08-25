#include <stdio.h>
#include "../inc/AlarmClockService.h"

/* Private data structures and variables */

/* Helper functions */
static int runCallback(unsigned long ticksOfHundredms)
{
    if (ticksOfHundredms == TICKS_OF_HUNDRED_MS_FOR_SECOND)
    {
        TimeService_SetAlarmPeriodAndCallback(ticksOfHundredms, AlarmClockService_WakeupAfterSecond);
        AlarmClockService_WakeupAfterSecond();
        return CALLED_WAKEUP_AFTER_SECOND;
    }
    else if (ticksOfHundredms == TICKS_OF_HUNDRED_MS_FOR_MINUTE)
    {
        TimeService_SetAlarmPeriodAndCallback(ticksOfHundredms, AlarmClockService_WakeupAfterMinute);
        AlarmClockService_WakeupAfterMinute();
        return CALLED_WAKEUP_AFTER_MINUTE;
    }
    else if (ticksOfHundredms == TICKS_OF_HUNDRED_MS_FOR_HOUR)
    {
        TimeService_SetAlarmPeriodAndCallback(ticksOfHundredms, AlarmClockService_WakeupAfterHour);
        AlarmClockService_WakeupAfterHour();
        return CALLED_WAKEUP_AFTER_HOUR;
    }
    else if (ticksOfHundredms == TICKS_OF_HUNDRED_MS_FOR_DAY)
    {
        TimeService_SetAlarmPeriodAndCallback(ticksOfHundredms, AlarmClockService_WakeupAfterDay);
        AlarmClockService_WakeupAfterDay();
        return CALLED_WAKEUP_AFTER_DAY;
    }
    else if (ticksOfHundredms == TICKS_OF_HUNDRED_MS_FOR_MONTH)
    {
        TimeService_SetAlarmPeriodAndCallback(ticksOfHundredms, AlarmClockService_WakeupAfterMonth);
        AlarmClockService_WakeupAfterMonth();
        return CALLED_WAKEUP_AFTER_MONTH;
    }
    else if (ticksOfHundredms == TICKS_OF_HUNDRED_MS_FOR_YEAR)
    {
        TimeService_SetAlarmPeriodAndCallback(ticksOfHundredms, AlarmClockService_WakeupAfterYear);
        AlarmClockService_WakeupAfterYear();
        return CALLED_WAKEUP_AFTER_YEAR;
    }
    return CALL_FAILED;
}

/* API Implementation */
int AlarmClockService_RunCallback(unsigned long ticksOfHundredms)
{
    // Call the appropriate callback
    return runCallback(ticksOfHundredms);
}

void AlarmClockService_WakeupAfterSecond(void)
{
    printf("\nWakeupAfterSecond called\n");
}

void AlarmClockService_WakeupAfterMinute(void)
{
    printf("\nWakeupAfterMinute called\n");
}

void AlarmClockService_WakeupAfterHour(void)
{
    printf("\nWakeupAfterHour called\n");
}

void AlarmClockService_WakeupAfterDay(void)
{
    printf("\nWakeupAfterDay called\n");
}

void AlarmClockService_WakeupAfterMonth(void)
{
    printf("\nWakeupAfterMonth called\n");
}

void AlarmClockService_WakeupAfterYear(void)
{
    printf("\nWakeupAfterYear called\n");
}