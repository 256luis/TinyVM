#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include "types.h"
#include "vm.h"

// helper functions
static Dword data_stack_peek(VM* vm)
{
    return vm->data_stack[vm->dsp];
}

static Dword data_stack_pop(VM* vm)
{
    Dword top = data_stack_peek(vm);
    vm->dsp--;
    return top;
}

static void data_stack_push(VM* vm, Dword value)
{
    vm->dsp++;
    vm->data_stack[vm->dsp] = value;
}

void vm_execute_instruction(VM* vm, Instruction inst)
{
    switch (inst.opcode)
    {
        // push literal value to the data stack
        // the inst.operand is the literal value
        case PUSHL: {
            data_stack_push(vm, inst.operand);
        } break;

        // get value stored at memory address and push it to the data stack
        // the inst.operand is the memory address
        case PUSHA: {
            Dword value = vm->memory[inst.operand.u];
            data_stack_push(vm, value);
        } break;

        // pop top of the stack to a specified memory address
        // the inst.operand is the memory address where the popped value will be stored
        case POP:{
            vm->memory[inst.operand.u] = data_stack_pop(vm);
        } break;

        // add the top two values from the top of the stack as integers
        case ADDI: {
            // pop two values from the stack
            uint32_t addend = data_stack_pop(vm).u;
            uint32_t augend = data_stack_pop(vm).u;

            // add them
            Dword sum = { .u = addend + augend };

            // push the sum to the stack
            data_stack_push(vm, sum);
        } break;

        // add the top two values from the top of the stack as floats
        case ADDF: {
            // pop two values from the stack
            float addend = data_stack_pop(vm).f;
            float augend = data_stack_pop(vm).f;

            // add them
            Dword sum = { .f = addend + augend };

            // push the sum to the stack
            data_stack_push(vm, sum);
        }
      
        // subtract the top two values from the top of the stack as integers
        case SUBI: {
            // pop two values from the stack
            uint32_t subtrahend = data_stack_pop(vm).u;
            uint32_t minuend = data_stack_pop(vm).u;
            
            // get two's complement of minuend
            minuend = (minuend ^ 0xFFFFFFFF) + 1;
            
            // add the subtrahend and the minuend
            Dword difference = { .u = subtrahend + minuend };
            
            // push difference to the stack
            data_stack_push(vm, difference);
        } break;

        // subtract the top two values from the top of the stack as integers
        case SUBF: {
            // pop two values from the stack
            float subtrahend = data_stack_pop(vm).f;
            float minuend = data_stack_pop(vm).f;

            // subtract
            Dword difference = { .f = subtrahend - minuend };

            // push difference to the stack
            data_stack_push(vm, difference);
        } break;

        // multiply the top two values from the top of the stack as integers
        case MULI: {
            // pop two values from the stack
            uint32_t multiplier = data_stack_pop(vm).u;
            uint32_t mutiplicand = data_stack_pop(vm).u;

            // multiply
            Dword product = { .u = multiplier * mutiplicand };

            // push product to stack
            data_stack_push(vm, product);
        } break;

        // multiply the top two values from the top of the stack as integers
        case MULF: {
            // pop two values from the stack
            float multiplier = data_stack_pop(vm).f;
            float mutiplicand = data_stack_pop(vm).f;

            // multiply
            Dword product = { .f = multiplier * mutiplicand };

            // push product to stack
            data_stack_push(vm, product);
        } break;
        
        // divide the top two values from the top of the stack as integers
        case DIVI: {
            // pop two values from the stack
            uint32_t divisor = data_stack_pop(vm).u;
            uint32_t dividend = data_stack_pop(vm).u;

            // divide
            Dword quotient = { .u = divisor / dividend };

            // push quotient to the stack
            data_stack_push(vm, quotient);
        } break;
        
        // divide the top two values from the top of the stack as integers
        case DIVF: {
            // pop two values from the stack
            float divisor = data_stack_pop(vm).f;
            float dividend = data_stack_pop(vm).f;

            // divide
            Dword quotient = { .f = divisor / dividend };

            // push quotient to the stack
            data_stack_push(vm, quotient);
        } break;

        // unconditional jump to instruction address
        case JMP: {
            vm->ip = inst.operand.u;
        } break;

        // jump if top of stack == 0
        case JZ: {
            if (data_stack_peek(vm).u == 0)
            {
                vm->ip = inst.operand.u;
            }
        } break;

        // jump if top of stack != 0
        case JNZ: {
            if (data_stack_peek(vm).u != 0)
            {
                vm->ip = inst.operand.u;
            }
        } break;
        
        // jump if top of stack > 0
        case JG: {
            if (data_stack_peek(vm).u > 0)
            {
                vm->ip = inst.operand.u;
            }
        } break;

        // jump if top of stack >= 0
        case JGE: {
            if (data_stack_peek(vm).u >= 0)
            {
                vm->ip = inst.operand.u;
            }
        } break;

        // jump if top of stack < 0
        case JL: {
            if (data_stack_peek(vm).u < 0)
            {
                vm->ip = inst.operand.u;
            }
        }

        // jump if top of stack <= 0
        case JLE: {
            if (data_stack_peek(vm).u <= 0)
            {
                vm->ip = inst.operand.u;
            }
        } break;

        // perform bitwise AND to top two items on the stack
        case AND: {
            // pop top two items from top of stack
            uint32_t operand_1 = data_stack_pop(vm).u;
            uint32_t operand_2 = data_stack_pop(vm).u;

            // perform bitwise AND
            Dword result = { .u = operand_1 & operand_2};

            // push result to stack
            data_stack_push(vm, result);
        } break;

        // perform bitwise OR to top two items on the stack
        case OR: {
            // pop top two items from top of stack
            uint32_t operand_1 = data_stack_pop(vm).u;
            uint32_t operand_2 = data_stack_pop(vm).u;

            // perform bitwise OR
            Dword result = { .u = operand_1 | operand_2};

            // push result to stack
            data_stack_push(vm, result);
        } break;

        // perform bitwise NOT on top item on the stack
        case NOT: {
            // pop from top of stack
            uint32_t top = data_stack_pop(vm).u;

            // perform bitwise NOT
            Dword result = { .u = ~top};

            // push result to stack
            data_stack_push(vm, result);
        } break;
        
        // perform bitwise XOR on top item on the stack
        case XOR: {
            // pop top two items from top of stack
            uint32_t operand_1 = data_stack_pop(vm).u;
            uint32_t operand_2 = data_stack_pop(vm).u;

            // perform bitwise XOR
            Dword result = { .u = operand_1 ^ operand_2};

            // push result to stack
            data_stack_push(vm, result);
        } break;

        // pop top of stack then print it as char 
        case OUT: {
            char c = data_stack_pop(vm).u;
            putchar(c);
        } break;
        
        default: {
            assert(0 && "unimplemented or invalid");
        }
    }

    vm->ip++;
}

void vm_dump(VM* vm)
{
    // print data stack
    puts("Data Stack:");
    for (int i = vm->dsp; i > 0; i--)
    {
        // TODO: check if this is UB
        printf("%08X\n", vm->data_stack[i].u);
    }

    // print return stack
    puts("\nReturn Stack:");
    for (int i = vm->rsp; i > 0; i--)
    {
        // TODO: check if this is UB
        printf("%08X\n", vm->return_stack[i]);
    }

    // print the first 10 dwords of main memory
    puts("\nMain Memory:");
    for (int i = 0; i < 10; i++)
    {
        printf("%08X\n", vm->memory[i].u);
    }
    
    // print dsp and rsp and ip
    printf("\nDSP: %04X\nRSP: %04X\nIP: %04X\n\n", vm->dsp, vm->rsp, vm->ip);
}
