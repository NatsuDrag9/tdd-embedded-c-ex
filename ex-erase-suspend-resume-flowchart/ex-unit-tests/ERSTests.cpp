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
    MockIO_Expect_ReadThenReturn(StatusRegister, ReadyBit);
    MockIO_Expect_ReadThenReturn(StatusRegister, EraseSuspendBit);
    MockIO_Expect_Write(randomAddr, ProgramCommand3);
    MockIO_Expect_ReadThenReturn(randomAddr, 0);
    MockIO_Expect_Write(randomAddr, ProgramCommand4);

    result = Flash_ERS(randomAddr);

    LONGS_EQUAL(FLASH_ERASE_RESUME, result);
}

TEST(FlashERS, ES_SucceedsImmediately)
{
    MockIO_Expect_Write(randomAddr, ProgramCommand1);
    MockIO_Expect_Write(randomAddr, ProgramCommand2);
    MockIO_Expect_ReadThenReturn(StatusRegister, ReadyBit);
    MockIO_Expect_ReadThenReturn(StatusRegister, !((uint8_t)EraseSuspendBit));
    MockIO_Expect_Write(randomAddr, ProgramCommand3);
    MockIO_Expect_ReadThenReturn(randomAddr, 0);

    result = Flash_ERS(randomAddr);

    LONGS_EQUAL(FLASH_ERASE_COMPLETE, result);
}

TEST(FlashERS, ER_DoesNotSucceedImmediately)
{
    MockIO_Expect_Write(randomAddr, ProgramCommand1);
    MockIO_Expect_Write(randomAddr, ProgramCommand2);
    MockIO_Expect_ReadThenReturn(StatusRegister, 0);
    MockIO_Expect_ReadThenReturn(StatusRegister, 0);
    MockIO_Expect_ReadThenReturn(StatusRegister, 0);
    MockIO_Expect_ReadThenReturn(StatusRegister, ReadyBit);
    MockIO_Expect_ReadThenReturn(StatusRegister, EraseSuspendBit);
    MockIO_Expect_Write(randomAddr, ProgramCommand3);
    MockIO_Expect_ReadThenReturn(randomAddr, 0);
    MockIO_Expect_Write(randomAddr, ProgramCommand4);

    result = Flash_ERS(randomAddr);

    LONGS_EQUAL(FLASH_ERASE_RESUME, result);
}