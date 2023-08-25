#include <stdio.h>
#include "inc/TimeService.h"
#include "inc/AlarmClockService.h"

int main(int argc, char const *argv[])
{
    /* code */
    AlarmClockService_RunCallback(TICKS_OF_HUNDRED_MS_FOR_SECOND);
    AlarmClockService_RunCallback(TICKS_OF_HUNDRED_MS_FOR_MINUTE);
    AlarmClockService_RunCallback(TICKS_OF_HUNDRED_MS_FOR_HOUR);
    AlarmClockService_RunCallback(TICKS_OF_HUNDRED_MS_FOR_DAY);
    AlarmClockService_RunCallback(TICKS_OF_HUNDRED_MS_FOR_MONTH);
    AlarmClockService_RunCallback(TICKS_OF_HUNDRED_MS_FOR_YEAR);
    return 0;
}
