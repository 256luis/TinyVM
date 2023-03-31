// this file is currently being used for testing purposes

#include <stdio.h>
#include "vm.h"
#include "types.h"

Dword dword_int(int num)
{
    return (Dword){ .u = num };
}

int main()
{
    VM* vm = &(VM){0};
    
    vm_execute_instruction(vm, PUSHL, dword_int(1));
    vm_execute_instruction(vm, PUSHL, dword_int(2));
    vm_execute_instruction(vm, PUSHL, dword_int(3));
    vm_execute_instruction(vm, PUSHL, dword_int(4));
    vm_execute_instruction(vm, POP, dword_int(0x09));
    vm_execute_instruction(vm, ADDI, DWORD_ZERO);
    vm_execute_instruction(vm, SUBI, DWORD_ZERO);
    vm_execute_instruction(vm, PUSHL, dword_int(2));
    vm_execute_instruction(vm, SUBI, DWORD_ZERO);    
    vm_execute_instruction(vm, PUSHL, dword_int(0xFFFFFFFF));
    vm_execute_instruction(vm, PUSHL, dword_int(0xFF00F0FF));
    vm_execute_instruction(vm, AND, DWORD_ZERO);
    vm_execute_instruction(vm, AND, DWORD_ZERO);
    vm_execute_instruction(vm, PUSHL, dword_int(0xFF000000));
    vm_execute_instruction(vm, PUSHL, dword_int(0x00FF0000));
    vm_execute_instruction(vm, OR, DWORD_ZERO);    
    
    vm_dump(vm);

    return 0;
}
