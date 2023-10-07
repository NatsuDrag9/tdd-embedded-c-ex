#include "CppUTest/TestHarness.h"

extern "C"
{
#include <stdio.h>
#include "../inc/cfi.h"
#include "../mocks/MockIO.h"
}

TEST_GROUP(CFIMockIO)
{
    ioAddress addr;
    ioData data;
    int result;

    void setup()
    {
        addr = 0x00;    // taken from table 3 in 
    }

    void teardown()
    {
    }
};

TEST(CFIMockIo, PrintEmpty)
{
}