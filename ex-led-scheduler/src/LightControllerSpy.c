#include <memory.h>
#include "../inc/LightControllerSpy.h"

// Private variables
static int lastId;
static int lastState;
static int lightStateArr[MAX_LIGHTS];

// Private helper function definitions
static int isIdInRange(int id){
    if(id > 0 && id <= 31){
        return 1;
    }
    return 0;
}

void LightController_Create(void){
    lastId = LIGHT_ID_UNKNOWN;
    lastState = LIGHT_STATE_UNKNOWN;
    memset(lightStateArr, LIGHT_STATE_UNKNOWN, sizeof(lightStateArr));
}

void LightController_Destroy(void){
    
}

void LightController_On(int id){
    lastId = id;
    if(isIdInRange(id)){
        lightStateArr[id] = LIGHT_ON;
    }
    lastState = LIGHT_ON;
}

void LightController_Off(int id){
    lastId = id;
    if(isIdInRange(id)){
        lightStateArr[id] = LIGHT_OFF;
    }
    lastState = LIGHT_OFF;
}

int LightControllerSpy_GetLastId(void){
    return lastId;
}

int LightControllerSpy_GetLastState(void){
    return lastState;
}

int LightControllerSpy_GetLightState(int id){
    if(!isIdInRange(id)){
        return LIGHT_STATE_UNKNOWN;        
    }
    return lightStateArr[id];
}