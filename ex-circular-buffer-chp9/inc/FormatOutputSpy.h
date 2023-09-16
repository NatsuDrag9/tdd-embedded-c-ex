#include "./utils.h"

void FormatOutputSpy_Create(int);
int FormatOutputSpy(const char* format, ...);
const char* FormatOutputSpy_GetOutput(void);
void FormatOutputSpy_Destroy(void);