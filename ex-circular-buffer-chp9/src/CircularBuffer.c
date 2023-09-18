#include "../inc/CircularBuffer.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

/* Helper functions */
static int countDigits(size_t num)
{
    int count = 0;

    // Handle the case when num is 0
    if (num == 0)
    {
        return 1; // 0 has one digit
    }

    while (num != 0)
    {
        num /= 10;
        count++;
    }

    return count;
}

/* API implementation */
CircularBuffer CircularBuffer_Create(size_t size)
{
    CircularBuffer buffer;
    buffer.bufferSize = (int)size;

    // Initializing with zeros to remove garbage values
    buffer.elementPtr = (size_t *)calloc(size, sizeof(size_t));
    // if (buffer.ptr == NULL){
    //     FormatOutputSpy("\nFailed to allocate memory... Exiting!\n");
    //     return buffer;
    // }

    buffer.writePtr = buffer.elementPtr;
    buffer.readPtr = buffer.elementPtr;
    buffer.isBufferEmpty = true;
    buffer.isBufferFull = false;
    buffer.readPtrIncrCount = 0;
    buffer.writePtrIncrCount = 0;

    return buffer;
}

void CircularBuffer_Put(CircularBuffer *ptrCircularBuffer, size_t value)
{
    if (ptrCircularBuffer->isBufferFull)
    {
        printf("\nUnable to put as buffer is full!!\n");
        return;
    }

    *(ptrCircularBuffer->writePtr) = value;
    ptrCircularBuffer->writePtr++;
    ptrCircularBuffer->isBufferEmpty = false;

    // Wrap when write pointer reaches end of buffer
    if (ptrCircularBuffer->writePtr == ptrCircularBuffer->elementPtr + ptrCircularBuffer->bufferSize)
    {
        ptrCircularBuffer->writePtr = ptrCircularBuffer->elementPtr;
    }

    // Buffer is full when writeptr equals readptr
    // Set flag and return
    if (ptrCircularBuffer->writePtr == ptrCircularBuffer->readPtr)
    {
        ptrCircularBuffer->isBufferFull = true;
        return;
    }
}

size_t CircularBuffer_Get(CircularBuffer *ptrCircularBuffer)
{
    if (ptrCircularBuffer->isBufferEmpty)
    {
        printf("\nUnable to get as buffer is empty!!\n");
        return 999999;
    }

    size_t value = *ptrCircularBuffer->readPtr;
    ptrCircularBuffer->readPtr++;
    ptrCircularBuffer->isBufferFull = false;

    // Wrap when read pointer reaches end of buffer
    if (ptrCircularBuffer->readPtr == ptrCircularBuffer->elementPtr + ptrCircularBuffer->bufferSize)
    {
        ptrCircularBuffer->readPtr = ptrCircularBuffer->elementPtr;
    }

    // Buffer is empty when readptr equals writeptr
    if (ptrCircularBuffer->readPtr == ptrCircularBuffer->writePtr)
    {
        ptrCircularBuffer->isBufferEmpty = true;
    }
    return value;
}

void CircularBuffer_Print(CircularBuffer *ptrCircularBuffer)
{
    if (ptrCircularBuffer->isBufferEmpty)
    {
        FormatOutputSpy("Circular buffer content: \n<>\n");
        return;
    }

    // Variables to print neatly in a column
    int lineLength = 60;    // Maximum of 60 characters in one line
    size_t value = CircularBuffer_Get(ptrCircularBuffer);
    int nDigits = countDigits(value);
    int nColSeparator = 2;  // Comma and space are the two characters used as separator
    int nCharPerLine = nDigits;

    FormatOutputSpy("Circular buffer content: \n<%zu", value);
    size_t *tempReadPtr = ptrCircularBuffer->readPtr;
    while (tempReadPtr != ptrCircularBuffer->writePtr)
    {
        value = CircularBuffer_Get(ptrCircularBuffer);
        nDigits = countDigits(value);
        nCharPerLine += nColSeparator + nDigits;
        if (nCharPerLine > lineLength){
            FormatOutputSpy("\n%zu", value);
            nCharPerLine = 0;   // Reset when switched to new line
        }
        else{
            FormatOutputSpy(", %zu", value);
        }
        // FormatOutputSpy(", %zu", value);
        tempReadPtr++;
        if (tempReadPtr == ptrCircularBuffer->elementPtr + ptrCircularBuffer->bufferSize)
        {
            tempReadPtr = ptrCircularBuffer->elementPtr;
        }
    }
    FormatOutputSpy(">\n");
    tempReadPtr = NULL;
}

void CircularBuffer_Destroy(CircularBuffer circularBuffer)
{
    if (circularBuffer.elementPtr == NULL)
    {
        return;
    }
    free(circularBuffer.elementPtr);
    circularBuffer.elementPtr = NULL;
    circularBuffer.writePtr = NULL;
    circularBuffer.readPtr = NULL;
    circularBuffer.isBufferEmpty = false;
    circularBuffer.isBufferFull = false;
}