#ifndef D_FakeTimeService_H
#define D_FakeTimeService_H

#include "TimeService.h"

enum {
    TIME_UNKNOWN = -1
};

void FakeTimeService_SetDay(int);
void FakeTimeService_SetMinute(int);
WakeUpCallback FakeTimeService_GetAlarmCallback(void);
int FakeTimeService_GetAlarmPeriod(void);

#endif /* D_FakeTimeService_H */