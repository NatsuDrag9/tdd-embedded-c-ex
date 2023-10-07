#include "../inc/flash.h"

/* No implementation */
void Flash_Create()
{
}

/* No implementation */
void Flash_Destroy()
{
}

int Flash_ERS(ioAddress addrOffset){
    IO_Write(addrOffset, ProgramCommand1);
    IO_Write(addrOffset, ProgramCommand2);
    IO_Read(StatusRegister);
    IO_Read(StatusRegister);
    IO_Write(addrOffset, ProgramCommand3);
    IO_Read(addrOffset);
    IO_Write(addrOffset, ProgramCommand4);
    return FLASH_ERASE_RESUME;
}