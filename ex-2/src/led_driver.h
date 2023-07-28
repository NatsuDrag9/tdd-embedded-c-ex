#include <stdint.h>
#include <stdio.h>
#include <stdbool.h>
#include "../RuntimeError.h"

void LedDriver_Create(uint16_t*);

void LedDriver_TurnAllOn();
void LedDriver_TurnAllOff();

void LedDriver_TurnOn(int);
void LedDriver_TurnOff(int);

bool LedDriver_IsOn(int);
bool LedDriver_IsOff(int);

void LedDriver_Destroy(void);