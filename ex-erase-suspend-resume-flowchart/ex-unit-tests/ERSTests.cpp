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
    int result = -1;

    void setup()
    {
        randomAddr = 0x01;
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
    MockIO_Expect_Write(randomAddr, ProgramCommand1);
    MockIO_Expect_Write(randomAddr, ProgramCommand2);
    MockIO_Expect_ReadThenReturn(StatusRegister, ReadBit);
    MockIO_Expect_ReadThenReturn(StatusRegister, EraseSuspendBit);
    MockIO_Expect_Write(randomAddr, ProgramCommand3);
    MockIO_Expect_ReadThenReturn(randomAddr, 0);
    MockIO_Expect_Write(randomAddr, ProgramCommand4);

    result = Flash_ERS(randomAddr);

    LONGS_EQUAL(0, result);
}