#include "../inc/AlarmClockService.h"

// Private data structures and variables
typedef struct {
    int minuteOfDay;
    Day day;
    AlarmState state;
} AlarmStruct;