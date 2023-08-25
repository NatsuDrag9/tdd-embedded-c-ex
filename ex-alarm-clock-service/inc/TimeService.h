#ifndef D_TIME_SERVICE_H
#define D_TIME_SERVICE_H

/* Interface variables and macros */
#define TICKS_OF_HUNDRED_MS_FOR_SECOND 10
#define TICKS_OF_HUNDRED_MS_FOR_MINUTE 60000
#define TICKS_OF_HUNDRED_MS_FOR_HOUR 3600000UL
#define TICKS_OF_HUNDRED_MS_FOR_DAY 86400000UL
#define TICKS_OF_HUNDRED_MS_FOR_WEEK 604800000UL
#define TICKS_OF_HUNDRED_MS_FOR_MONTH 2629056000UL
#define TICKS_OF_HUNDRED_MS_FOR_YEAR 315360000000UL

#define NO_OF_CALLBACKS 6

/* Typedefs */
typedef void (*WakeUpCallback)(void);

/* API prototypes */
void TimeService_Create(void);
void TimerService_Destroy(void);
void TimeService_SetAlarmPeriodAndCallback(unsigned long ticksOfHundredms, WakeUpCallback cb);
void TimeService_ResetAlarmPeriodAndCallback(unsigned long ticksOfHundredms, WakeUpCallback cb);

#endif /* D_TIME_SERVICE_H */