#include "module/fpu.h"


void fpu_enable(void)
{
    // Enable the FPU by setting bits 20-23 in the CPACR register
    SCB->CPACR |= (0xF << 20);

}