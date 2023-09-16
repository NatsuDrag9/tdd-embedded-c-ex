#ifndef CIRCULAR_BUFFER_H
#define CIRCULAR_BUFFER_H

#include "FormatOutputSpy.h"

/* Structure */
typedef struct {
    size_t* ptr;
} CircularBuffer;

/* APIs*/
CircularBuffer CircularBuffer_Create(size_t size);
void CircularBuffer_Print(CircularBuffer circularBuffer);
void CircularBuffer_Destroy(CircularBuffer circularBuffer);

#endif /* CIRCULAR_BUFFER_H */