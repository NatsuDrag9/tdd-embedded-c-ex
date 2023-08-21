#include <stdio.h>
#include "./inc/LightScheduler.h"

int main(int argc, char const *argv[])
{
    LightScheduler_Create();
    int turnOn = LightScheduler_ScheduleTurnOn(3, 2, 100);
    int turnOff = LightScheduler_ScheduleTurnOff(3, 2, 500);
    printf("\nTurn on return code: %d\n", turnOn);
    printf("Turn off return code: %d\n", turnOff);
    return 0;
}
