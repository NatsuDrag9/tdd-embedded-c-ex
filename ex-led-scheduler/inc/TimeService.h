
#ifndef D_TimeService_H
#define D_TimeService_H

typedef struct Time
{
    int minuteOfDay;
    int dayOfWeek;
} Time;

void TimeService_Create(void);
void TimeService_Destroy(void);
void TimeService_GetTime(Time *);

typedef void (*WakeUpCallback)(void);

void TimeService_SetPeriodicAlarmInSeconds(
        int seconds, WakeUpCallback);

void TimeService_CancelPeriodicAlarmInSeconds(
        int seconds, WakeUpCallback);


#endif  /* D_TimeService_H */