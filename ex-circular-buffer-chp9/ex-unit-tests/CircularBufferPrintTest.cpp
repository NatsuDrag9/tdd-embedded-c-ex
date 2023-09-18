#include "CppUTest/TestHarness.h"

extern "C"
{
#include <stdio.h>
#include "../inc/FormatOutputSpy.h"
#include "../inc/CircularBuffer.h"
}

TEST_GROUP(CircularBufferPrint)
{
    CircularBuffer buffer;
    const char *expectedOutput;
    const char *actualOutput;

    void setup()
    {
        UT_PTR_SET(FormatOutput, FormatOutputSpy);
        FormatOutputSpy_Create(200);
        actualOutput = FormatOutputSpy_GetOutput();
        buffer = CircularBuffer_Create(5);
    }

    void teardown()
    {
        CircularBuffer_Destroy(buffer);
        FormatOutputSpy_Destroy();
    }
};

TEST(CircularBufferPrint, PrintEmpty)
{
    expectedOutput = "Circular buffer content: \n<>\n";
    CircularBuffer_Print(&buffer, 60);
    STRCMP_EQUAL(expectedOutput, actualOutput);
}

TEST(CircularBufferPrint, PrintAfterOneIsPut)
{
    expectedOutput = "Circular buffer content: \n<17>\n";
    CircularBuffer_Put(&buffer, 17);
    CircularBuffer_Print(&buffer, 60);

    STRCMP_EQUAL(expectedOutput, actualOutput);
}

TEST(CircularBufferPrint, PrintNotYetWrappedOrFull)
{
    expectedOutput = "Circular buffer content: \n<10, 20, 30>\n";
    CircularBuffer_Put(&buffer, 10);
    CircularBuffer_Put(&buffer, 20);
    CircularBuffer_Put(&buffer, 30);
    CircularBuffer_Print(&buffer, 60);

    STRCMP_EQUAL(expectedOutput, actualOutput);
}

TEST(CircularBufferPrint, PrintNotYetWrappedAndIsFull)
{
    expectedOutput = "Circular buffer content: \n<31, 41, 59, 26, 53>\n";
    CircularBuffer_Put(&buffer, 31);
    CircularBuffer_Put(&buffer, 41);
    CircularBuffer_Put(&buffer, 59);
    CircularBuffer_Put(&buffer, 26);
    CircularBuffer_Put(&buffer, 53);
    CircularBuffer_Print(&buffer, 60);

    STRCMP_EQUAL(expectedOutput, actualOutput);
}

TEST(CircularBufferPrint, PrintOldToNewWhenWrappedAndFull)
{
    expectedOutput = "Circular buffer content: \n<202, 203, 204, 205, 999>\n";
    CircularBuffer_Put(&buffer, 201);
    CircularBuffer_Put(&buffer, 202);
    CircularBuffer_Put(&buffer, 203);
    CircularBuffer_Put(&buffer, 204);
    CircularBuffer_Put(&buffer, 205);
    CircularBuffer_Get(&buffer);
    CircularBuffer_Put(&buffer, 999);
    CircularBuffer_Print(&buffer, 60);

    STRCMP_EQUAL(expectedOutput, actualOutput);
}

/* Exercises */
// Boundary condition to check exactly 60 characters per line
TEST(CircularBufferPrint, ShiftToNextLineWhenLineExactlyFull)
{
    expectedOutput = "Circular buffer content: \n<10000, 10001, 10002, 10003, 10004, 10005, 10006, 10007, 101\n10008, 10009, 10010>\n";

    CircularBuffer tmpBuffer = CircularBuffer_Create(12);
    for (size_t i = 0; i < 8; i++)
    {
        CircularBuffer_Put(&tmpBuffer, 10000 + i);
    }
    CircularBuffer_Put(&tmpBuffer, 101);
    for (size_t i = 8; i < 11; i++)
    {
        CircularBuffer_Put(&tmpBuffer, 10000 + i);
    }
    CircularBuffer_Print(&tmpBuffer, 60);
    STRCMP_EQUAL(expectedOutput, actualOutput);
    CircularBuffer_Destroy(tmpBuffer);
}

// Checks when line characters exceeds 60
TEST(CircularBufferPrint, ShiftToNextLineWhenLineFull)
{
    expectedOutput = "Circular buffer content: \n<10000, 10001, 10002, 10003, 10004, 10005, 10006, 10007\n10008, 10009, 10010>\n";

    CircularBuffer tmpBuffer = CircularBuffer_Create(11);
    for (size_t i = 0; i < 11; i++)
    {
        CircularBuffer_Put(&tmpBuffer, 10000 + i);
    }
    CircularBuffer_Print(&tmpBuffer, 60);
    STRCMP_EQUAL(expectedOutput, actualOutput);
    CircularBuffer_Destroy(tmpBuffer);
}