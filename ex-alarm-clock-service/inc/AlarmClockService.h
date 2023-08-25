#ifndef D_Alarm_Clock_Service_H
#define D_Alarm_Clock_Service_H

enum Day
{
    NONE = -1,
    DAILY = 10,
    WEEKLY,
    WEEKEND,
    WEEKDAY,
    MONTHLY,
    YEARLY,
    SUNDAY = 1,
    MONDAY,
    TUESDAY,
    WEDNESDAY,
    THURSDAY,
    FRIDAY,
    SATURDAY
};

enum AlarmState
{
    DELETE = 0,
    SNOOZE
};

typedef enum Day Day;
typedef enum AlarmState AlarmState;

/* Function prototypes */
void AlarmClockService_CreateAlarm(int id, Day day, int minute);
void AlarmClockService_Wakeup(void);

#endif /* D_Alarm_Clock_Service_H */