#ifndef D_LightScheduler_H
#define D_LightScheduler_H

#include <stdbool.h>
#include "TimeService.h"
#include "LightController.h"

enum Day{
    NONE = -1,
    EVERYDAY = 10,
    WEEKDAY,
    WEEKEND,
    SUNDAY = 1,
    MONDAY,
    TUESDAY,
    WEDNESDAY,
    THURSDAY,
    FRIDAY,
    SATURDAY
};

enum {
    LS_ID_OUT_OF_BOUNDS = -1,
    LS_OK,
    LS_TOO_MANY_EVENTS
};

typedef enum Day Day;

void LightScheduler_Create(void);
void LightScheduler_Destroy(void);
int LightScheduler_ScheduleTurnOn(int id, Day day, int minuteOfDay);
int LightScheduler_ScheduleTurnOff(int id, Day day, int minuteOfDay);
void LightScheduler_Wakeup(void);
void LightScheduler_ScheduleRemove(int id, Day day, int minuteOfDay);

#endif /* D_LightScheduler_H */