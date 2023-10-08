#ifndef D_FLASH_H
#define D_FLASH_H

#include "io.h"
#include "m28w160ect.h"

typedef enum {
    FLASH_ERASE_RESUME = 0,
    FLASH_ERASE_COMPLETE,
    FLASH_TIMEOUT_ERROR
} FlashStatus;

void Flash_Create(void);
void Flash_Destroy(void);
int Flash_ERS(ioAddress addrOffset);

#endif /* D_FLASH_H */