#include "CppUTest/TestHarness.h"

extern "C"
{
#include "../../inc/LightControllerSpy.h"
}

TEST_GROUP(LightControllerSpy)
{
    void setup()
    {
        LightController_Create();
    }

    void teardown()
    {
        LightController_Destroy();
    }
};

TEST(LightControllerSpy, Create)
{
    LONGS_EQUAL(LIGHT_ID_UNKNOWN, LightControllerSpy_GetLastId());
    LONGS_EQUAL(LIGHT_ID_UNKNOWN, LightControllerSpy_GetLastState());
}

TEST(LightControllerSpy, RememberTheLastLightIdControlled)
{
    LightController_On(10);
    LONGS_EQUAL(10, LightControllerSpy_GetLastId());
    LONGS_EQUAL(LIGHT_ON, LightControllerSpy_GetLastState());
}

// TEST(LightControllerSpy, CheckIdRange){
//     LightController_On(-1);
//     LightController_On(32);
//     LONGS_EQUAL(LIGHT_ID_UNKNOWN, LightControllerSpy_GetLightState(-1));
//     LONGS_EQUAL(LIGHT_ID_UNKNOWN, LightControllerSpy_GetLightState(32));
// }

TEST(LightControllerSpy, RememberAllLightStates){
    LightController_On(5);
    LightController_Off(31);
    LONGS_EQUAL(LIGHT_ON, LightControllerSpy_GetLightState(5));
    LONGS_EQUAL(LIGHT_OFF, LightControllerSpy_GetLightState(31));
}