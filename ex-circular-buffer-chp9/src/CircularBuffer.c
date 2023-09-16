#include "../inc/CircularBuffer.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

/* Static variables */
static size_t* writePtr = NULL;
static size_t* readPtr = NULL;
static bool isBufferFull = false;
static bool isBufferEmpty = false;

/* API implementation */
CircularBuffer CircularBuffer_Create(size_t size){
    CircularBuffer buffer;
    buffer.ptr = (size_t*)calloc(size, sizeof(size_t));
    // if (buffer.ptr == NULL){
    //     FormatOutputSpy("\nFailed to allocate memory... Exiting!\n");
    //     return buffer;
    // }
    writePtr = buffer.ptr;
    readPtr = buffer.ptr;
    isBufferFull = false;
    isBufferEmpty = true;

    return buffer;
}

void CircularBuffer_Print(CircularBuffer circularBuffer){
    if (isBufferEmpty){
        FormatOutputSpy("Circular buffer content: \n<>\n");
        return;
    }
    FormatOutputSpy("Circular buffer content: \n<%zu>\n", *circularBuffer.ptr);
}

void CircularBuffer_Destroy(CircularBuffer circularBuffer){
    if(circularBuffer.ptr == NULL){
        return;
    }
    free(circularBuffer.ptr);
    circularBuffer.ptr = NULL; 
}