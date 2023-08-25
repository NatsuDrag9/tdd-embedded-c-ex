#ifndef D_TIME_SERVICE_H
#define D_TIME_SERVICE_H

/* Interface variables */
typedef struct Time {
    int dayOfWeek;
    int minuteOfDay;
} Time;


/* API prototypes */
void TimeService_Create(void);
void TimerService_Destroy(void);
void TimeService_GetTime(Time*);

#endif /* D_TIME_SERVICE_H */