// this file is currently being used for testing purposes

#include <stdio.h>
#include "vm.h"
#include "types.h"

#define DWORD_INT(num) (Dword){ .u = num }
#define DWORD_FLOAT(num) (Dword){ .f = num }

/* Dword dword_int(int num) */
/* { */
/*     return (Dword){ .u = num }; */
/* } */

int main()
{
    VM* vm = &(VM){0};

    Instruction program[] = {
        {PUSHL, DWORD_INT('\n')},
        {PUSHL, DWORD_INT('!')},
        {PUSHL, DWORD_INT('d')},
        {PUSHL, DWORD_INT('l')},
        {PUSHL, DWORD_INT('r')},
        {PUSHL, DWORD_INT('o')},
        {PUSHL, DWORD_INT('W')},
        {PUSHL, DWORD_INT(' ')},
        {PUSHL, DWORD_INT(',')},
        {PUSHL, DWORD_INT('o')},
        {PUSHL, DWORD_INT('l')},
        {PUSHL, DWORD_INT('l')},
        {PUSHL, DWORD_INT('e')},
        {PUSHL, DWORD_INT('H')},
        {OUT, DWORD_ZERO},
        {OUT, DWORD_ZERO},
        {OUT, DWORD_ZERO},
        {OUT, DWORD_ZERO},
        {OUT, DWORD_ZERO},
        {OUT, DWORD_ZERO},
        {OUT, DWORD_ZERO},
        {OUT, DWORD_ZERO},
        {OUT, DWORD_ZERO},
        {OUT, DWORD_ZERO},
        {OUT, DWORD_ZERO},
        {OUT, DWORD_ZERO},
        {OUT, DWORD_ZERO},
        {OUT, DWORD_ZERO},
        {HALT, DWORD_ZERO}
    };

    while (!vm->should_halt)
    {
        vm_execute_instruction(vm, program[vm->ip]);
    }
    
    vm_dump(vm);

    return 0;
}
