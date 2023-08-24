#include "CppUTest/TestHarness.h"

extern "C"{
    #include "../inc/AlarmClockService.h"
    #include "../inc/BuzzerControllerSpy.h"
    #include "../inc/FakeTimeService.h"
}

/**/


/* Implementation of alarm clock service tests */
TEST_GROUP(AlarmClockService){
    void setup(){

    }

    void teardown(){

    }
};

TEST(AlarmClockService, NoBuzzerChangedDuringInitialization){
    LONGS_EQUAL(BUZZER_ID_UNKNOWN, BuzzerControllerSpy_GetLastBuzzerId());
    LONGS_EQUAL(BUZZER_STATE_UNKNOWN, BuzzerControllerSpy_GetLastBuzzerState());
    LONGS_EQUAL(BUZZER_STATE_UNKNOWN, BuzzerControllerSpy_GetBuzzerState(3));
}