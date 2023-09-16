#include "../inc/CircularBuffer.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

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

    return buffer;
}

void CircularBuffer_Put(CircularBuffer *ptrCircularBuffer, size_t value)
{
    if (ptrCircularBuffer->isBufferFull)
    {
        printf("Unable to put as buffer is full");
        return;
    }

    // Wrap when writePtr reaches end of buffer
    if (ptrCircularBuffer->writePtrIncrCount == ptrCircularBuffer->bufferSize)
    {
        ptrCircularBuffer->writePtr = ptrCircularBuffer->elementPtr;
    }

    *(ptrCircularBuffer->writePtr) = value;
    ptrCircularBuffer->writePtr++;
    ptrCircularBuffer->writePtrIncrCount++;
    ptrCircularBuffer->isBufferEmpty = false;

    // Buffer is full when writePtr equals readPtr
    if (ptrCircularBuffer->writePtr == ptrCircularBuffer->readPtr)
    {
        ptrCircularBuffer->isBufferFull = true;
    }
}

size_t CircularBuffer_Get(CircularBuffer *ptrCircularBuffer)
{
    if (ptrCircularBuffer->isBufferEmpty)
    {
        printf("Unable to get as buffer is empty");
        return 999999999;
    }

    size_t value = *(ptrCircularBuffer->readPtr);
    ptrCircularBuffer->readPtr++;
    ptrCircularBuffer->readPtrIncrCount++;
    ptrCircularBuffer->isBufferFull = false;

    // Wrap when readPtr reaches end
    if (ptrCircularBuffer->readPtrIncrCount == ptrCircularBuffer->bufferSize)
    {
        ptrCircularBuffer->readPtr = ptrCircularBuffer->elementPtr;
    }

    // Buffer is empty when readPtr equals writePtr
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

    size_t *tempReadPtr = ptrCircularBuffer->readPtr;
    FormatOutputSpy("Circular buffer content: \n<%zu", *tempReadPtr);
    tempReadPtr++;
    while (tempReadPtr != ptrCircularBuffer->writePtr)
    {
        FormatOutputSpy(", %zu", *tempReadPtr);
        tempReadPtr++;
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