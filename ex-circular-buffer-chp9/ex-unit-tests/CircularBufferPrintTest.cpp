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
    expectedOutput = "Circular buffer content: \n<10,   20,   30>\n";
    CircularBuffer_Put(&buffer, 10);
    CircularBuffer_Put(&buffer, 20);
    CircularBuffer_Put(&buffer, 30);
    CircularBuffer_Print(&buffer, 60);

    STRCMP_EQUAL(expectedOutput, actualOutput);
}

TEST(CircularBufferPrint, PrintNotYetWrappedAndIsFull)
{
    expectedOutput = "Circular buffer content: \n<31,   41,   59,   26,   53>\n";
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
    expectedOutput = "Circular buffer content: \n<202,    203,    204,    205,    999>\n";
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
/* Ex-1 */
// Boundary condition to check exactly 60 characters per line
TEST(CircularBufferPrint, ShiftToNextLineWhenLineExactlyFull)
{
    expectedOutput = "Circular buffer content: \n<10000,      10001,      10002,      10003,      10004\n10005,      10006,      10007,      10008,      10009\n10010>\n";

    CircularBuffer tmpBuffer = CircularBuffer_Create(11);
    for (size_t i = 0; i < 11; i++)
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
    expectedOutput = "Circular buffer content: \n<10000,      10001,      10002,      10003,      10004\n10005,      10006,      10007>\n";

    CircularBuffer tmpBuffer = CircularBuffer_Create(8);
    for (size_t i = 0; i < 8; i++)
    {
        CircularBuffer_Put(&tmpBuffer, 10000 + i);
    }
    CircularBuffer_Print(&tmpBuffer, 60);
    STRCMP_EQUAL(expectedOutput, actualOutput);
    CircularBuffer_Destroy(tmpBuffer);
}

/* Ex-2 */
// Adjust column width to two characters wider than the largest number
// in the buffer
// Largest number here is 100000 = 6 characters.
// So, column width = 1 comma and 1 space + length of largest number = 8 characters
TEST(CircularBufferPrint, ColumnWidth)
{
    expectedOutput = "Circular buffer content: \n<1000,       100,       100000,       1,       12345>\n";
    CircularBuffer_Put(&buffer, 1000);
    CircularBuffer_Put(&buffer, 100);
    CircularBuffer_Put(&buffer, 100000);
    CircularBuffer_Put(&buffer, 1);
    CircularBuffer_Put(&buffer, 12345);
    CircularBuffer_Print(&buffer, 60);

    STRCMP_EQUAL(expectedOutput, actualOutput);
}