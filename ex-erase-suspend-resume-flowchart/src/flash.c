#include "../inc/flash.h"

/* No implementation */
void Flash_Create()
{
}

/* No implementation */
void Flash_Destroy()
{
}

int Flash_ERS(ioAddress addrOffset)
{
    ioData statusRegValue = 0;
    IO_Write(addrOffset, ProgramCommand1);
    IO_Write(addrOffset, ProgramCommand2);
    
    // Read status register until b7 = 1
    while ((statusRegValue & ReadyBit) == 0)
    {
        statusRegValue = IO_Read(StatusRegister);
    }

    // Check bit 6 of status register
    statusRegValue = IO_Read(StatusRegister);
    if (statusRegValue & EraseSuspendBit)
    {
        // Erase resume operation
        IO_Write(addrOffset, ProgramCommand3);
        IO_Read(addrOffset);
        IO_Write(addrOffset, ProgramCommand4);
        return FLASH_ERASE_RESUME;
    }

    // Erase complete
    IO_Write(addrOffset, ProgramCommand3);
    IO_Read(addrOffset);
    return FLASH_ERASE_COMPLETE;
}