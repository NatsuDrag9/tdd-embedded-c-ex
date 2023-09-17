#include "CppUTest/TestHarness.h"

extern "C" {
    #include <stdio.h>
    #include "../inc/FormatOutputSpy.h"
    #include "../inc/CircularBuffer.h"
}

TEST_GROUP(CircularBufferPrint){
    CircularBuffer buffer;
    const char* expectedOutput;
    const char* actualOutput;

    void setup(){
        UT_PTR_SET(FormatOutput, FormatOutputSpy);
        FormatOutputSpy_Create(100);
        actualOutput = FormatOutputSpy_GetOutput();
        buffer = CircularBuffer_Create(5);
    }

    void teardown(){
        CircularBuffer_Destroy(buffer);
        FormatOutputSpy_Destroy();
    }
};

TEST(CircularBufferPrint, PrintEmpty){
    expectedOutput = "Circular buffer content: \n<>\n";
    CircularBuffer_Print(&buffer);
    STRCMP_EQUAL(expectedOutput, actualOutput);
}

TEST(CircularBufferPrint, PrintAfterOneIsPut){
    expectedOutput = "Circular buffer content: \n<17>\n";
    CircularBuffer_Put(&buffer, 17);
    CircularBuffer_Print(&buffer);

    STRCMP_EQUAL(expectedOutput, actualOutput);
}

TEST(CircularBufferPrint, PrintNotYetWrappedOrFull){
    expectedOutput = "Circular buffer content: \n<10, 20, 30>\n";
    CircularBuffer_Put(&buffer, 10);
    CircularBuffer_Put(&buffer, 20);
    CircularBuffer_Put(&buffer, 30);
    CircularBuffer_Print(&buffer);

    STRCMP_EQUAL(expectedOutput, actualOutput);
}

TEST(CircularBufferPrint, PrintNotYetWrappedAndIsFull){
    expectedOutput = "Circular buffer content: \n<31, 41, 59, 26, 53>\n";
    CircularBuffer_Put(&buffer, 31);
    CircularBuffer_Put(&buffer, 41);
    CircularBuffer_Put(&buffer, 59);
    CircularBuffer_Put(&buffer, 26);
    CircularBuffer_Put(&buffer, 53);
    CircularBuffer_Print(&buffer);

    STRCMP_EQUAL(expectedOutput, actualOutput);
}

TEST(CircularBufferPrint, PrintOldToNewWhenWrappedAndFull){
    expectedOutput = "Circular buffer content: \n<202, 203, 204, 205, 999>\n";
    CircularBuffer_Put(&buffer, 201);
    CircularBuffer_Put(&buffer, 202);
    CircularBuffer_Put(&buffer, 203);
    CircularBuffer_Put(&buffer, 204);
    CircularBuffer_Put(&buffer, 205);
    CircularBuffer_Get(&buffer);
    CircularBuffer_Put(&buffer, 999);
    CircularBuffer_Print(&buffer);

    STRCMP_EQUAL(expectedOutput, actualOutput);
}

TEST(CircularBufferPrint, PrintMultipleLines){

}