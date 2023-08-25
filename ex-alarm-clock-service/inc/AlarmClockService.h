#ifndef D_Alarm_Clock_Service_H
#define D_Alarm_Clock_Service_H

#include "TimeService.h"

/* Interface variables and macros */
#define CALL_FAILED -1
#define CALLED_WAKEUP_AFTER_SECOND 3
#define CALLED_WAKEUP_AFTER_MINUTE 4
#define CALLED_WAKEUP_AFTER_HOUR 5
#define CALLED_WAKEUP_AFTER_DAY 6
#define CALLED_WAKEUP_AFTER_MONTH 7
#define CALLED_WAKEUP_AFTER_YEAR 8

/* Function prototypes */
int AlarmClockService_RunCallback(unsigned long ticksOfHundredms);
void AlarmClockService_WakeupAfterSecond(void);
void AlarmClockService_WakeupAfterMinute(void);
void AlarmClockService_WakeupAfterHour(void);
void AlarmClockService_WakeupAfterDay(void);
void AlarmClockService_WakeupAfterMonth(void);
void AlarmClockService_WakeupAfterYear(void);

#endif /* D_Alarm_Clock_Service_H */