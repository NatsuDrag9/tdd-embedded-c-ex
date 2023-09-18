#include "../inc/utils.h"

static int FormatOutput_Impl(const char *format, ...)
{
    /* Implementation code */
    if (*format){
        // Do nothing
        // This block is for the compilation error "unused parameter ‘format’ [-Werror=unused-parameter"
    }
    return 0;
}

int (*FormatOutput)(const char* format, ...) = FormatOutput_Impl;