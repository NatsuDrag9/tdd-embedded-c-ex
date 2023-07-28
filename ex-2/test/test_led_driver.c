#include "unity_fixture.h"
#include <stdint.h>
#include "RuntimeErrorStub.h"

static uint16_t virtualLeds;

TEST_GROUP(LEDDriver);

TEST_SETUP(LEDDriver){
    LedDriver_Create(&virtualLeds);
}

TEST_TEAR_DOWN(LEDDriver){

}

TEST(LEDDriver, LedsOffAfterCreate){
    uint16_t virtualLeds = 0xFFFF;
    LedDriver_Create(&virtualLeds);
    TEST_ASSERT_EQUAL_HEX16(0, virtualLeds);
}

TEST(LEDDriver,TurnOnAllLeds) {
    LedDriver_TurnAllOn();
    TEST_ASSERT_EQUAL_HEX16(0xFFFF, virtualLeds);
}

TEST(LEDDriver,TurnOffAllLeds) {
    LedDriver_TurnAllOn();
    LedDriver_TurnAllOff();
    TEST_ASSERT_EQUAL_HEX16(0x0, virtualLeds);
}

/* 
* Removed virtualLeds and LedDriver_Create(&virtualLeds)
* from the TurnOnLedOne and TurnOffLedOne and placed them
* in TEST_SETUP() as they are repeated in both tests. 
* 
* The commented lines below indicate that they were previously
* present in the two tests before deletion
*/

TEST(LEDDriver, TurnOnLedOne){
    // uint16_t virtualLeds;
    // LedDriver_Create(&virtualLeds);
    LedDriver_TurnOn(1);
    TEST_ASSERT_EQUAL_HEX16(0x0001, virtualLeds);
}

TEST(LEDDriver, TurnOffLedOne){
    // uint16_t virtualLeds;
    // LedDriver_Create(&virtualLeds);
    LedDriver_TurnOn(1);
    LedDriver_TurnOff(1);
    TEST_ASSERT_EQUAL_HEX16(0x0, virtualLeds);
}

TEST(LEDDriver, TurnOnMultipleLeds){
    LedDriver_TurnOn(9);
    LedDriver_TurnOn(8);
    TEST_ASSERT_EQUAL_HEX16(0x0180, virtualLeds);
}

TEST(LEDDriver, TurnOffMultipleLeds){
    LedDriver_TurnAllOn();
    LedDriver_TurnOff(9);
    LedDriver_TurnOff(8);
    TEST_ASSERT_EQUAL_HEX16((~0x0180)&0xFFFF, virtualLeds);
}

TEST(LEDDriver, TurnOffAnyLed){
    LedDriver_TurnAllOn();
    LedDriver_TurnOff(8);
    TEST_ASSERT_EQUAL_HEX16(0xFF7F, virtualLeds);
}

TEST(LEDDriver, LedMemoryIsNotReadable){
    virtualLeds = 0xFFFF;
    LedDriver_TurnOn(8);
    TEST_ASSERT_EQUAL_HEX16(0x0080, virtualLeds);
}

// Boundary condition test checks the upper and lower bounds of
// the legal LED values
TEST(LEDDriver, UpperAndLowerBounds){
    LedDriver_TurnOn(1);
    LedDriver_TurnOn(16);
    TEST_ASSERT_EQUAL_HEX16(0x8001, virtualLeds);
}

TEST(LEDDriver, OutOfBoundsTurnOnDoesNoHarm){
    LedDriver_TurnOn(-1);
    LedDriver_TurnOn(0);
    LedDriver_TurnOn(17);
    LedDriver_TurnOn(3141);
    TEST_ASSERT_EQUAL_HEX16(0x0, virtualLeds);
}

TEST(LEDDriver, OutOfBoundsTurnOffDoesNoHarm){
    LedDriver_TurnAllOn();
    LedDriver_TurnOff(-1);
    LedDriver_TurnOff(0);
    LedDriver_TurnOff(17);
    LedDriver_TurnOff(3141);
    TEST_ASSERT_EQUAL_HEX16(0xFFFF, virtualLeds);
}

TEST(LEDDriver, OutOfBoundsProducesRuntimeError){
    
    LedDriver_TurnOff(-1);
    TEST_ASSERT_EQUAL_STRING("LED Driver: out-of-bounds LED", RuntimeErrorStub_GetLastError());
    TEST_ASSERT_EQUAL(1, RuntimeErrorStub_GetLastParameter());
}

// Tests the IGNORE_TEST macro
IGNORE_TEST(LEDDriver, OutOfBoundsToDo){
    /* TODO: what should we do during runtime?*/
}

TEST(LEDDriver, IsOn){
    TEST_ASSERT_FALSE(LedDriver_IsOn(11));
    LedDriver_TurnOn(11);
    TEST_ASSERT_TRUE(LedDriver_IsOn(11));
}

TEST(LEDDriver, IsOnOutOfBoundsLedsAreAlwaysOff){
    TEST_ASSERT_FALSE(LedDriver_IsOn(0));
    TEST_ASSERT_FALSE(LedDriver_IsOn(17));
}

TEST(LEDDriver, IsOff){
    TEST_ASSERT_TRUE(LedDriver_IsOff(10));
    LedDriver_TurnOn(10);
    TEST_ASSERT_FALSE(LedDriver_IsOff(10));

    /*
    OR
    First turn ON Led 10 and check whether it's actually ON
    Then turn OFF Led 10 and check whether it's actually OFF

    LedDriver_TurnOn(10);
    TEST_ASSERT_TRUE(LedDriver_IsOff(10));
    LedDriver_TurnOff(10);
    TEST_ASSERT_TRUE(LedDriver_IsOff(10));

    Though this tests whether Led 10 is actually OFF, it also
    gives the impression of testing both, whether Led 10 is ON 
    and OFF because the two asserts. Remember, the tests should 
    be as simple as possible and, each test to check for (only) 
    one problem
    
    Instead, use the uncommented version
    above which initially checks whether Led 10 is turned OFF,
    then turns it ON and finally checks whether it is OFF by 
    asserting FALSE.
    */
}

TEST(LEDDriver, IsOffOutOfBoundsLedsAreAlwaysOff){
    TEST_ASSERT_TRUE(LedDriver_IsOff(0));
    TEST_ASSERT_TRUE(LedDriver_IsOff(17));
    TEST_ASSERT_FALSE(LedDriver_IsOn(0));
    TEST_ASSERT_FALSE(LedDriver_IsOn(17));
}