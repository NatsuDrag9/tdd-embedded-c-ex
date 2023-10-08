#ifndef D_M28w160ECT_H
#define D_M28w160ECT_H

typedef enum
{
    StatusRegister = 0x00
} Flash_Registers;

typedef enum
{
    ProgramCommand1 = 0xB0,
    ProgramCommand2 = 0x70,
    ProgramCommand3 = 0xFF,
    ProgramCommand4 = 0xD0
} Flash_Command;

typedef enum
{
    ReadyBit = 1<<7,
    EraseSuspendBit = 1<<6
} StatusRegisterBits;

#endif /*D_M28w160ECT_H*/