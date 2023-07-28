#include <stdint.h>
#include "unity_fixture.h"
#include "RuntimeErrorStub.h"
#include "../src/circular_buffer.h"

/* Private variables for this file */
CircularBuffer *ptrCircularBufferTest;
static int arrIdx = 2;
static int firstArrElementIdx = 0;

TEST_GROUP(CircularBuffer);

TEST_SETUP(CircularBuffer)
{
    ptrCircularBufferTest = CircularBuffer_Create();
    CircularBuffer_Init(&ptrCircularBufferTest);
}

TEST_TEAR_DOWN(CircularBuffer)
{
    CircularBuffer_Destroy(&ptrCircularBufferTest);
}

TEST(CircularBuffer, CreateCircularBuffer)
{
    CircularBuffer *ptrCircularBufferTest = NULL;
    ptrCircularBufferTest = CircularBuffer_Create();
    TEST_ASSERT_NOT_NULL(ptrCircularBufferTest);
    TEST_ASSERT_BYTES_EQUAL(sizeof(CircularBuffer), sizeof(*ptrCircularBufferTest));
}

TEST(CircularBuffer, ReadPtrSetToNullAfterCreation)
{
    int readPtrVal = 1;
    ptrCircularBufferTest->readPtr = &readPtrVal;

    ptrCircularBufferTest = CircularBuffer_Create();
    TEST_ASSERT_NULL(ptrCircularBufferTest->readPtr);
}

TEST(CircularBuffer, WritePtrSetToNullAfterCreation)
{
    int writePtrVal = 2;
    ptrCircularBufferTest->writePtr = &writePtrVal;

    ptrCircularBufferTest = CircularBuffer_Create();
    TEST_ASSERT_NULL(ptrCircularBufferTest->writePtr);
}

TEST(CircularBuffer, ArrValSetToZeroAfterInitialization)
{
    int x = 2;
    ptrCircularBufferTest->arr[arrIdx] = x;

    CircularBuffer_Init(&ptrCircularBufferTest);
    TEST_ASSERT_EQUAL(0, ptrCircularBufferTest->arr[arrIdx]);
}

TEST(CircularBuffer, ReadPtrPointsToFirstElementAfterInitialization)
{
    ptrCircularBufferTest->readPtr = &ptrCircularBufferTest->arr[arrIdx];

    CircularBuffer_Init(&ptrCircularBufferTest);
    TEST_ASSERT_EQUAL_PTR(&ptrCircularBufferTest->arr[firstArrElementIdx], ptrCircularBufferTest->readPtr);
}

TEST(CircularBuffer, WritePtrPointsToFirstElementAfterInitialization)
{
    ptrCircularBufferTest->writePtr = &ptrCircularBufferTest->arr[arrIdx];

    CircularBuffer_Init(&ptrCircularBufferTest);
    TEST_ASSERT_EQUAL_PTR(&ptrCircularBufferTest->arr[firstArrElementIdx], ptrCircularBufferTest->writePtr);
}

TEST(CircularBuffer, FlagsAfterInitialization)
{
    CircularBuffer_Init(&ptrCircularBufferTest);
    TEST_ASSERT_EQUAL(false, ptrCircularBufferTest->isBufferFull);
    TEST_ASSERT_EQUAL(false, ptrCircularBufferTest->isBufferEmpty);
}

TEST(CircularBuffer, WriteToCircularBuffer)
{
    int writeVal = 10;
    int *prevWritePtr = ptrCircularBufferTest->writePtr;

    CircularBuffer_Write(&ptrCircularBufferTest, writeVal);
    ptrdiff_t numElements = ptrCircularBufferTest->writePtr - prevWritePtr;
    size_t numBytes = numElements * sizeof(int);

    // Checks whether the pointer incremented by 4 bytes
    TEST_ASSERT_BYTES_EQUAL(sizeof(int), numBytes);

    // Checks whether value written was correct
    TEST_ASSERT_EQUAL(writeVal, CircularBuffer_Read(&ptrCircularBufferTest));
}

TEST(CircularBuffer, ReadFromCircularBuffer)
{
    int nWrite = 3, writeValArr[nWrite];
    int *prevReadPtr = ptrCircularBufferTest->readPtr;

    for (int i = 0; i < nWrite; i++)
    {
        writeValArr[i] = (i + 1) * 5;
        CircularBuffer_Write(&ptrCircularBufferTest, writeValArr[i]);
    }

    CircularBuffer_Read(&ptrCircularBufferTest);
    ptrdiff_t numElements = ptrCircularBufferTest->readPtr - prevReadPtr;
    size_t numBytes = numElements * sizeof(int);

    // Checks whether the read pointer incremented by 4 bytes
    TEST_ASSERT_BYTES_EQUAL(sizeof(int), numBytes);

    // Checks whether correct value is being read
    // i starts from 1 because CircularBuffer_Read()
    // was first called above
    for (int i = 1; i < nWrite; i++)
    {
        TEST_ASSERT_EQUAL(writeValArr[i], CircularBuffer_Read(&ptrCircularBufferTest));
    }
}

TEST(CircularBuffer, WritePtrCircularBufferWrap)
{
    int nWrite = CIRCULAR_BUFFER_SIZE, writeValArr[nWrite];
    for (int i = 0; i < nWrite; i++)
    {
        writeValArr[i] = (i + 1) * 5;
        CircularBuffer_Write(&ptrCircularBufferTest, writeValArr[i]);
    }
    TEST_ASSERT_EQUAL_PTR(&ptrCircularBufferTest->arr[firstArrElementIdx], ptrCircularBufferTest->writePtr);
}

TEST(CircularBuffer, ReadPtrCircularBufferWrap)
{
    int nWrite = CIRCULAR_BUFFER_SIZE, writeValArr[nWrite];
    for (int i = 0; i < nWrite; i++)
    {
        writeValArr[i] = (i + 1) * 5;
        CircularBuffer_Write(&ptrCircularBufferTest, writeValArr[i]);
        CircularBuffer_Read(&ptrCircularBufferTest);
    }
    TEST_ASSERT_EQUAL_PTR(&ptrCircularBufferTest->arr[firstArrElementIdx], ptrCircularBufferTest->readPtr);
}

TEST(CircularBuffer, CircularBufferFull)
{
    int nWrite = CIRCULAR_BUFFER_SIZE, writeValArr[nWrite];
    for (int i = 0; i < nWrite; i++)
    {
        writeValArr[i] = (i + 1) * 5;
        // printf("\nTest writePtr: %p and readPtr: %p\n", ptrCircularBufferTest->writePtr, ptrCircularBufferTest->readPtr);
        CircularBuffer_Write(&ptrCircularBufferTest, writeValArr[i]);
    }
    TEST_ASSERT_EQUAL_PTR(ptrCircularBufferTest->readPtr, ptrCircularBufferTest->writePtr);
    TEST_ASSERT_EQUAL(true, ptrCircularBufferTest->isBufferFull);
}

TEST(CircularBuffer, CircularBufferEmpty)
{
    int nWrite = CIRCULAR_BUFFER_SIZE, writeValArr[nWrite];
    for (int i = 0; i < nWrite; i++)
    {
        writeValArr[i] = (i + 1) * 5;
        // printf("\nTest writePtr: %p and readPtr: %p\n", ptrCircularBufferTest->writePtr, ptrCircularBufferTest->readPtr);
        CircularBuffer_Write(&ptrCircularBufferTest, writeValArr[i]);
        CircularBuffer_Read(&ptrCircularBufferTest);
    }
    
    TEST_ASSERT_EQUAL_PTR(ptrCircularBufferTest->readPtr, ptrCircularBufferTest->writePtr);
    TEST_ASSERT_EQUAL(true, ptrCircularBufferTest->isBufferEmpty);
}

TEST(CircularBuffer, WritePtrCircularBufferLowerOutofBound)
{
    int writeVal = 5;
    ptrCircularBufferTest->writePtr = &ptrCircularBufferTest->arr[firstArrElementIdx - 2];
    CircularBuffer_Write(&ptrCircularBufferTest, writeVal);
    TEST_ASSERT_EQUAL_STRING("Incorrect initialization of writePtr. Freeing buffer and exiting... Please restart!", RuntimeErrorStub_GetLastError());
    TEST_ASSERT_EQUAL(2, RuntimeErrorStub_GetLastParameter());
}

TEST(CircularBuffer, WritePtrCircularBufferUpperOutofBound)
{
    int writeVal = 5;
    ptrCircularBufferTest->writePtr = &ptrCircularBufferTest->arr[CIRCULAR_BUFFER_SIZE + 2];
    CircularBuffer_Write(&ptrCircularBufferTest, writeVal);
    TEST_ASSERT_EQUAL_STRING("writePtr beyond array scope. Freeing buffer and exiting... Please restart!", RuntimeErrorStub_GetLastError());
    TEST_ASSERT_EQUAL(2, RuntimeErrorStub_GetLastParameter());
}

TEST(CircularBuffer, ReadPtrCircularBufferLowerOutofBound)
{
    int writeVal = 5;
    ptrCircularBufferTest->readPtr = &ptrCircularBufferTest->arr[firstArrElementIdx - 2];
    CircularBuffer_Write(&ptrCircularBufferTest, writeVal);
    int readVal = CircularBuffer_Read(&ptrCircularBufferTest);
    TEST_ASSERT_EQUAL_STRING("Incorrect initialization of readPtr. Freeing buffer and exiting... Please restart!", RuntimeErrorStub_GetLastError());
    TEST_ASSERT_EQUAL(2, RuntimeErrorStub_GetLastParameter());
    TEST_ASSERT_EQUAL('E', readVal);
}

TEST(CircularBuffer, ReadPtrCircularBufferUpperOutofBound)
{
    int writeVal = 5;
    ptrCircularBufferTest->writePtr = &ptrCircularBufferTest->arr[CIRCULAR_BUFFER_SIZE + 2];
    CircularBuffer_Write(&ptrCircularBufferTest, writeVal);
    int readVal = CircularBuffer_Read(&ptrCircularBufferTest);
    TEST_ASSERT_EQUAL_STRING("readPtr beyond array scope. Freeing buffer and exiting... Please restart!", RuntimeErrorStub_GetLastError());
    TEST_ASSERT_EQUAL(2, RuntimeErrorStub_GetLastParameter());
    TEST_ASSERT_EQUAL('E', readVal);
}

TEST(CircularBuffer, DestroyCreatedCircularBuffer)
{
    CircularBuffer *ptrCircularBufferTest = CircularBuffer_Create();
    CircularBuffer_Destroy(&ptrCircularBufferTest);
    TEST_ASSERT_NULL(ptrCircularBufferTest);
}

TEST(CircularBuffer, NullPtrReceptionProducesRuntimeErrorInDestroy)
{
    CircularBuffer *ptrCircularBufferTest = NULL;
    CircularBuffer_Destroy(&ptrCircularBufferTest);
    TEST_ASSERT_EQUAL_STRING("NULL pointer received. Cannot free NULL pointer!", RuntimeErrorStub_GetLastError());
    TEST_ASSERT_EQUAL(1, RuntimeErrorStub_GetLastParameter());
}