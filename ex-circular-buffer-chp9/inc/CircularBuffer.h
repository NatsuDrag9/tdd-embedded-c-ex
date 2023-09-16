#ifndef CIRCULAR_BUFFER_H
#define CIRCULAR_BUFFER_H

#include <stdbool.h>
#include "FormatOutputSpy.h"

/* Structure */
typedef struct {
    size_t* elementPtr;     // points to first element of dynamically created array
    size_t* writePtr;
    size_t* readPtr;
    bool isBufferFull;
    bool isBufferEmpty;
    int bufferSize;
    int readPtrIncrCount;
    int writePtrIncrCount;
} CircularBuffer;

/* APIs*/
CircularBuffer CircularBuffer_Create(size_t size);
void CircularBuffer_Print(CircularBuffer* ptrCircularBuffer);
void CircularBuffer_Put(CircularBuffer* ptrCircularBuffer, size_t value);
size_t CircularBuffer_Get(CircularBuffer* ptrCircularBuffer);
void CircularBuffer_Destroy(CircularBuffer circularBuffer);

#endif /* CIRCULAR_BUFFER_H */