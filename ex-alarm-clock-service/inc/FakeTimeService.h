#ifndef D_FAKE_TIME_SERVICE_H
#define D_FAKE_TIME_SERVICE_H

#include "TimeService.h"

/* API prototypes */
WakeUpCallback FakeTimeService_GetAlarmCallback(void);
unsigned long FakeTimeService_GetAlarmPeriod(void);

#endif /* D_FAKE_TIME_SERVICE */