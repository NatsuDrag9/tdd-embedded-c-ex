#include "CppUTest/TestHarness.h"

extern "C"
{
// #include <stddef.h>
#include "../inc/flash.h"
#include "../mocks/MockIO.h"
}

TEST_GROUP(FlashERS)
{
    ioAddress randomAddr;
    ioAddress data;
    int result = -1;

    void setup()
    {
        randomAddr = 0x00;
        uint8_t mockSize = 10;
        MockIO_Create(mockSize);
        Flash_Create();
    }

    void teardown()
    {
        Flash_Destroy();
        MockIO_Verify_Complete();
        MockIO_Destroy();
    }
};

TEST(FlashERS, ER_SucceedsImmediately)
{
    MockIO_Expect_Write(0x00, 0xB0);
    MockIO_Expect_Write(0x11, 0x70);
    MockIO_Expect_ReadThenReturn(0x01, 1<<7);   // randomly selected status register address = 0x01
    MockIO_Expect_ReadThenReturn(0x01, 1<<6);   // read bit 6 of status register
    MockIO_Expect_Write(0x12, 0xFF);
    MockIO_Expect_ReadThenReturn(0x10, 0);
    MockIO_Expect_Write(0x13, 0xD0);

    result = Flash_ERS();

    LONGS_EQUAL(0, result);
}