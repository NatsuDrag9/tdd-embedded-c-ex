#include "./circular_buffer.h"

/* Declaration of variables private to this file */
const int INITIAL_BUFFER_VALUE = 0;

/* Private helper functions */
static bool Is_Buffer_Full(CircularBuffer **doublePtrCircularBuffer)
{
    if ((*doublePtrCircularBuffer)->writePtr == (*doublePtrCircularBuffer)->readPtr)
    {
        (*doublePtrCircularBuffer)->isBufferFull = true;
        printf("\nFIFO buffer full. Please read from buffer to write a new value\n");
        return true;
    }
    return false;
}

static bool Is_Buffer_Empty(CircularBuffer **doublePtrCircularBuffer)
{
    if ((*doublePtrCircularBuffer)->readPtr == (*doublePtrCircularBuffer)->writePtr)
    {
        (*doublePtrCircularBuffer)->isBufferEmpty = true;
        printf("\n FIFO buffer empty. Please write to buffer to read the last written value\n");
        return true;
    }
    return false;
}

/* Driver implementation */
CircularBuffer *CircularBuffer_Create()
{
    CircularBuffer *ptrCircularBuffer = (CircularBuffer *)malloc(sizeof(CircularBuffer));
    ptrCircularBuffer->readPtr = NULL;
    ptrCircularBuffer->writePtr = NULL;
    return ptrCircularBuffer;
}

void CircularBuffer_Init(CircularBuffer **doublePtrCircularBuffer)
{
    for (int i = 0; i < CIRCULAR_BUFFER_SIZE; i++)
    {
        (*doublePtrCircularBuffer)->arr[i] = INITIAL_BUFFER_VALUE;
    }

    (*doublePtrCircularBuffer)->readPtr = &(*doublePtrCircularBuffer)->arr[0];
    (*doublePtrCircularBuffer)->writePtr = &(*doublePtrCircularBuffer)->arr[0];
    (*doublePtrCircularBuffer)->isBufferFull = false;
    (*doublePtrCircularBuffer)->isBufferEmpty = false;
}

void CircularBuffer_Write(CircularBuffer **doublePtrCircularBuffer, int writeVal)
{
    // Lower and upper check for writePtr
    if ((*doublePtrCircularBuffer)->writePtr < &(*doublePtrCircularBuffer)->arr[0])
    {
        CircularBuffer_Destroy(doublePtrCircularBuffer);
        RUNTIME_ERROR("Incorrect initialization of writePtr. Freeing buffer and exiting... Please restart!", 2);
        return;
    }
    else if ((*doublePtrCircularBuffer)->writePtr > &(*doublePtrCircularBuffer)->arr[CIRCULAR_BUFFER_SIZE - 1])
    {
        CircularBuffer_Destroy(doublePtrCircularBuffer);
        RUNTIME_ERROR("writePtr beyond array scope. Freeing buffer and exiting... Please restart!", 2);
        return;
    }

    *((*doublePtrCircularBuffer)->writePtr) = writeVal;
    // (*doublePtrCircularBuffer)->writePtr++;

    // Wrapping writePtr
    if ((*doublePtrCircularBuffer)->writePtr == &(*doublePtrCircularBuffer)->arr[CIRCULAR_BUFFER_SIZE - 1])
    {
        // printf("\nWrapping writePtr.\n");
        (*doublePtrCircularBuffer)->writePtr = &(*doublePtrCircularBuffer)->arr[0];

        // After wrapping check buffer full condition and update the flag
        if(Is_Buffer_Full(doublePtrCircularBuffer)){
            return;
        }
        return;
    }

    (*doublePtrCircularBuffer)->writePtr++;

    // After every increment of writePtr, check buffer full condition
    // and update the flag
    if(Is_Buffer_Full(doublePtrCircularBuffer)){
        return;
    }

    // FIFO buffer is not empty as long as values are being written
    (*doublePtrCircularBuffer)->isBufferFull = false;
}

int CircularBuffer_Read(CircularBuffer **doublePtrCircularBuffer)
{
    // Lower and upper check for readPtr
    if ((*doublePtrCircularBuffer)->readPtr < &(*doublePtrCircularBuffer)->arr[0])
    {
        CircularBuffer_Destroy(doublePtrCircularBuffer);
        RUNTIME_ERROR("Incorrect initialization of readPtr. Freeing buffer and exiting... Please restart!", 2);
        // returning Error
        return 'E';
    }
    else if ((*doublePtrCircularBuffer)->writePtr > &(*doublePtrCircularBuffer)->arr[CIRCULAR_BUFFER_SIZE - 1])
    {
        CircularBuffer_Destroy(doublePtrCircularBuffer);
        RUNTIME_ERROR("readPtr beyond array scope. Freeing buffer and exiting... Please restart!", 2);
        // returning Error
        return 'E';
    }

    // Check buffer empty condition before reading and update the flag
    if (Is_Buffer_Empty(doublePtrCircularBuffer))
    {
        return '0';
    }

    int readVal = *(*doublePtrCircularBuffer)->readPtr;

    // Wrapping readPtr
    if ((*doublePtrCircularBuffer)->readPtr == &(*doublePtrCircularBuffer)->arr[CIRCULAR_BUFFER_SIZE - 1])
    {
        (*doublePtrCircularBuffer)->readPtr = &(*doublePtrCircularBuffer)->arr[0];

        // Check buffer empty condition after wrapping and update the flag
        if (Is_Buffer_Empty(doublePtrCircularBuffer))
        {
            return '0';
        }

        // return 'W' for wrap
        return 'W';
    }
    (*doublePtrCircularBuffer)->readPtr++;

    // FIFO buffer is not empty as long as values are being read
    (*doublePtrCircularBuffer)->isBufferEmpty = false;

    return readVal;
}

void CircularBuffer_Destroy(CircularBuffer **doublePtrCircularBuffer)
{
    if (*doublePtrCircularBuffer == NULL)
    {
        // printf("\nNULL pointer received in destroy.\n");
        RUNTIME_ERROR("NULL pointer received. Cannot free NULL pointer!", 1);
        return;
    }
    // printf("\nFreeing received ptr.\n");
    free(*doublePtrCircularBuffer);
    *doublePtrCircularBuffer = NULL;
}