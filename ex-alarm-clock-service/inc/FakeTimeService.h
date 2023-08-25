#ifndef D_FAKE_TIME_SERVICE_H
#define D_FAKE_TIME_SERVICE_H

#include "TimeService.h"

enum {
    TIME_UNKNOWN = -1
};

/* API prototypes */
void FakeTimeService_SetDay(int);
void FakeTimeService_SetTime(int);

#endif /* D_FAKE_TIME_SERVICE */