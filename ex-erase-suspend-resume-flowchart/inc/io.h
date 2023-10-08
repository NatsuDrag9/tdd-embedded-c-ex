#ifndef D_IO_H
#define D_IO_H

#include <stdio.h>
#include <stdint.h>

typedef volatile uint32_t ioAddress;
typedef uint16_t ioData;

void IO_Write(ioAddress addrOffset, ioData data);
ioData IO_Read(ioAddress addrOffset);

#endif /* D_IO_H */