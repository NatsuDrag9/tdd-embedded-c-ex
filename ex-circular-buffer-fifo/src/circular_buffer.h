#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <stdbool.h>
#include "RuntimeError.h"

/* Buffer declarations*/
// Forward declaration of structure of FIFO circular buffer
typedef struct CircularBuffer CircularBuffer;

// Structure of FIFO circular buffer
#define CIRCULAR_BUFFER_SIZE 5

struct CircularBuffer{
    int* readPtr;
    int* writePtr;
    bool isBufferFull;  // for the user to know
    bool isBufferEmpty; // for the user to know
    int arr[CIRCULAR_BUFFER_SIZE];
};

/* API prototypes */
CircularBuffer* CircularBuffer_Create();

void CircularBuffer_Init(CircularBuffer**);
void CircularBuffer_Write(CircularBuffer**, int);
int CircularBuffer_Read(CircularBuffer**);

void CircularBuffer_Destroy(CircularBuffer**);