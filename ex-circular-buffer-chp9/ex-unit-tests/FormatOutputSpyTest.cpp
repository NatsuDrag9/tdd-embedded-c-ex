#include "CppUTest/TestHarness.h"

extern "C" {
    #include "../inc/FormatOutputSpy.h"
}

TEST_GROUP(FormatOutputSpy){
    void setup(){
        UT_PTR_SET(FormatOutput, FormatOutputSpy);
    }

    void teardown(){
        FormatOutputSpy_Destroy();
    }
};

TEST(FormatOutputSpy, HelloWorld){
    FormatOutputSpy_Create(20);
    FormatOutput("Hello, World\n");
    STRCMP_EQUAL("Hello, World\n", FormatOutputSpy_GetOutput());
}

TEST(FormatOutputSpy, LimitTheOutputBufferSize){
    FormatOutputSpy_Create(4);
    FormatOutput("Hello, World\n");
    STRCMP_EQUAL("Hell", FormatOutputSpy_GetOutput());
}

TEST(FormatOutputSpy, PrintMultipleTimes){
    FormatOutputSpy_Create(25);
    FormatOutput("Hello 1");
    FormatOutput(" World");
    FormatOutput("\n");
    STRCMP_EQUAL("Hello 1 World\n", FormatOutputSpy_GetOutput());
}