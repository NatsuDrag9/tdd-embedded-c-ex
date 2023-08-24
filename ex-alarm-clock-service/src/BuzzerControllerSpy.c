#include "../inc/BuzzerControllerSpy.h"

/* Private variables for this file */
static int lastBuzzerId;
static int lastBuzzerState;
static int buzzerState;

int BuzzerControllerSpy_GetLastBuzzerId(void){
    return lastBuzzerId;
}

int BuzzerControllerSpy_GetLastBuzzerState(void){
    return lastBuzzerState;
}

int BuzzerControllerSpy_GetBuzzerState(int buzzerId){
    if(buzzerId){
        /* Temporary block to prevent compiler error unused-variable */
    }
    return buzzerState;
}