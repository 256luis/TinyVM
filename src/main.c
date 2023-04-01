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

    vm_execute_instruction(vm, PUSHL, DWORD_INT('\n'));
    vm_execute_instruction(vm, PUSHL, DWORD_INT('!'));
    vm_execute_instruction(vm, PUSHL, DWORD_INT('D'));
    vm_execute_instruction(vm, PUSHL, DWORD_INT('L'));
    vm_execute_instruction(vm, PUSHL, DWORD_INT('R'));
    vm_execute_instruction(vm, PUSHL, DWORD_INT('O'));
    vm_execute_instruction(vm, PUSHL, DWORD_INT('W'));
    vm_execute_instruction(vm, PUSHL, DWORD_INT(' '));
    vm_execute_instruction(vm, PUSHL, DWORD_INT('O'));
    vm_execute_instruction(vm, PUSHL, DWORD_INT('L'));
    vm_execute_instruction(vm, PUSHL, DWORD_INT('L'));
    vm_execute_instruction(vm, PUSHL, DWORD_INT('E'));
    vm_execute_instruction(vm, PUSHL, DWORD_INT('H'));

    vm_execute_instruction(vm, OUT, DWORD_INT('H'));
    vm_execute_instruction(vm, OUT, DWORD_INT('E'));
    vm_execute_instruction(vm, OUT, DWORD_INT('L'));
    vm_execute_instruction(vm, OUT, DWORD_INT('L'));
    vm_execute_instruction(vm, OUT, DWORD_INT('0'));
    vm_execute_instruction(vm, OUT, DWORD_INT(' '));
    vm_execute_instruction(vm, OUT, DWORD_INT('W'));
    vm_execute_instruction(vm, OUT, DWORD_INT('O'));
    vm_execute_instruction(vm, OUT, DWORD_INT('R'));
    vm_execute_instruction(vm, OUT, DWORD_INT('L'));
    vm_execute_instruction(vm, OUT, DWORD_INT('D'));
    vm_execute_instruction(vm, OUT, DWORD_INT('!'));
    vm_execute_instruction(vm, OUT, DWORD_INT('\n'));
    
    vm_dump(vm);

    return 0;
}
