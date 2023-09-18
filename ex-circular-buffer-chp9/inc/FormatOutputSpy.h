#ifndef FORMAT_OUTPUT_SPY_H
#define FORMAT_OUTPUT_SPY_H

#include "./utils.h"

/* APIs */
void FormatOutputSpy_Create(int size);
int FormatOutputSpy(const char* format, ...);
const char* FormatOutputSpy_GetOutput(void);
void FormatOutputSpy_Destroy(void);

#endif /* FORMAT_OUTPUT_SPY_H */