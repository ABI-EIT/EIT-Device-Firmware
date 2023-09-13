#include "fsl_common.h"

__attribute__((weak, noreturn)) 
void __assertion_failed(char *failedExpr)
{
    for (;;)
    {
        __BKPT(0);
    }
    __builtin_unreachable();
}

__attribute__((weak, noreturn)) 
void __assert_func(const char *file, int line, const char *func, const char *failedExpr)
{
    for (;;)
    {
        __BKPT(0);
    }
    __builtin_unreachable();
}
