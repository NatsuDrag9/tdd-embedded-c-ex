#include "unity_fixture.h"

TEST_GROUP_RUNNER(LEDDriver){
    RUN_TEST_CASE(LEDDriver, LedsOffAfterCreate);
    RUN_TEST_CASE(LEDDriver, TurnOnAllLeds);
    RUN_TEST_CASE(LEDDriver, TurnOffAllLeds);
    RUN_TEST_CASE(LEDDriver, TurnOnLedOne);
    RUN_TEST_CASE(LEDDriver, TurnOffLedOne);
    RUN_TEST_CASE(LEDDriver, TurnOnMultipleLeds);
    RUN_TEST_CASE(LEDDriver, TurnOffMultipleLeds);
    RUN_TEST_CASE(LEDDriver, TurnOffAnyLed);
    RUN_TEST_CASE(LEDDriver, LedMemoryIsNotReadable);
    RUN_TEST_CASE(LEDDriver, UpperAndLowerBounds);
    RUN_TEST_CASE(LEDDriver, OutOfBoundsTurnOnDoesNoHarm);
    RUN_TEST_CASE(LEDDriver, OutOfBoundsTurnOffDoesNoHarm);
    RUN_TEST_CASE(LEDDriver, OutOfBoundsProducesRuntimeError);
    RUN_TEST_CASE(LEDDriver, OutOfBoundsToDo);
    RUN_TEST_CASE(LEDDriver, IsOn);
    RUN_TEST_CASE(LEDDriver, IsOnOutOfBoundsLedsAreAlwaysOff);
    RUN_TEST_CASE(LEDDriver, IsOff);
    RUN_TEST_CASE(LEDDriver, IsOffOutOfBoundsLedsAreAlwaysOff);
}