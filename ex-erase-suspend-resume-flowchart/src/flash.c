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
    statusRegValue = IO_Read(StatusRegister);
    statusRegValue = IO_Read(StatusRegister);
    if (statusRegValue & EraseSuspendBit)
    {
        IO_Write(addrOffset, ProgramCommand3);
        IO_Read(addrOffset);
        IO_Write(addrOffset, ProgramCommand4);
        return FLASH_ERASE_RESUME;
    }
    IO_Write(addrOffset, ProgramCommand3);
    IO_Read(addrOffset);
    return FLASH_ERASE_COMPLETE;
}