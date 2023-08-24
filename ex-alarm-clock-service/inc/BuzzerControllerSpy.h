#ifndef D_Buzzer_Controller_H
#define D_Buzzer_Controller_H

#include "BuzzerController.h"

enum
{
    BUZZER_ID_UNKNOWN = -1,
    BUZZER_STATE_UNKNOWN = -1,
    BUZZER_OFF = 0,
    BUZZER_ON = 1,
};

int BuzzerControllerSpy_GetLastBuzzerId(void);
int BuzzerControllerSpy_GetLastBuzzerState(void);
int BuzzerControllerSpy_GetBuzzerState(int buzzerId);

#endif /* D_Buzzer_Controller*/