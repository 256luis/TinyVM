#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include "types.h"
#include "vm.h"

// helper functions
static Dword stack_peek(VM* vm, Dword* stack)
{
    return stack[vm->dsp];
}

static Dword stack_pop(VM* vm, Dword* stack)
{
    Dword top = stack_peek(vm, stack);
    vm->dsp--;
    return top;
}

static void stack_push(VM* vm, Dword* stack, Dword value)
{
    vm->dsp++;
    stack[vm->dsp] = value;
}

void vm_execute_instruction(VM* vm, Opcode opcode, Dword operand)
{
    switch (opcode)
    {
        // push literal value to the data stack
        // the operand is the literal value
        case PUSHL: {
            stack_push(vm, vm->data_stack, operand);
        } break;

        // get value stored at memory address and push it to the data stack
        // the operand is the memory address
        case PUSHA: {
            Dword value = vm->memory[operand.u];
            stack_push(vm, vm->data_stack, value);
        } break;

        // pop top of the stack to a specified memory address
        // the operand is the memory address where the popped value will be stored
        case POP:{
            vm->memory[operand.u] = stack_pop(vm, vm->data_stack);
        } break;

        // add the top two values from the top of the stack as integers
        case ADDI: {
            // pop two values from the stack
            uint32_t addend = stack_pop(vm, vm->data_stack).u;
            uint32_t augend = stack_pop(vm, vm->data_stack).u;

            // add them
            Dword sum = { .u = addend + augend };

            // push the sum to the stack
            stack_push(vm, vm->data_stack, sum);
        } break;

        // add the top two values from the top of the stack as floats
        case ADDF: {
            // pop two values from the stack
            float addend = stack_pop(vm, vm->data_stack).f;
            float augend = stack_pop(vm, vm->data_stack).f;

            // add them
            Dword sum = { .f = addend + augend };

            // push the sum to the stack
            stack_push(vm, vm->data_stack, sum);
        }
      
        // subtract the top two values from the top of the stack as integers
        case SUBI: {
            // pop two values from the stack
            uint32_t subtrahend = stack_pop(vm, vm->data_stack).u;
            uint32_t minuend = stack_pop(vm, vm->data_stack).u;
            
            // get two's complement of minuend
            minuend = (minuend ^ 0xFFFFFFFF) + 1;
            
            // add the subtrahend and the minuend
            Dword difference = { .u = subtrahend + minuend };
            
            // push difference to the stack
            stack_push(vm, vm->data_stack, difference);
        } break;

        // subtract the top two values from the top of the stack as integers
        case SUBF: {
            // pop two values from the stack
            float subtrahend = stack_pop(vm, vm->data_stack).f;
            float minuend = stack_pop(vm, vm->data_stack).f;

            // subtract
            Dword difference = { .f = subtrahend - minuend };

            // push difference to the stack
            stack_push(vm, vm->data_stack, difference);
        } break;

        // multiply the top two values from the top of the stack as integers
        case MULI: {
            // pop two values from the stack
            uint32_t multiplier = stack_pop(vm, vm->data_stack).u;
            uint32_t mutiplicand = stack_pop(vm, vm->data_stack).u;

            // multiply
            Dword product = { .u = multiplier * mutiplicand };

            // push product to stack
            stack_push(vm, vm->data_stack, product);
        } break;

        // multiply the top two values from the top of the stack as integers
        case MULF: {
            // pop two values from the stack
            float multiplier = stack_pop(vm, vm->data_stack).f;
            float mutiplicand = stack_pop(vm, vm->data_stack).f;

            // multiply
            Dword product = { .f = multiplier * mutiplicand };

            // push product to stack
            stack_push(vm, vm->data_stack, product);
        } break;
        
        // divide the top two values from the top of the stack as integers
        case DIVI: {
            // pop two values from the stack
            uint32_t divisor = stack_pop(vm, vm->data_stack).u;
            uint32_t dividend = stack_pop(vm, vm->data_stack).u;

            // divide
            Dword quotient = { .u = divisor / dividend };

            // push quotient to the stack
            stack_push(vm, vm->data_stack, quotient);
        } break;
        
        // divide the top two values from the top of the stack as integers
        case DIVF: {
            // pop two values from the stack
            float divisor = stack_pop(vm, vm->data_stack).f;
            float dividend = stack_pop(vm, vm->data_stack).f;

            // divide
            Dword quotient = { .f = divisor / dividend };

            // push quotient to the stack
            stack_push(vm, vm->data_stack, quotient);
        } break;

        // unconditional jump to instruction address
        case JMP: {
            vm->ip = operand.u;
        }

        // jump if top of stack == 0
        case JZ: {
            if (stack_peek(vm, vm->data_stack).u == 0)
            {
                vm->ip = operand.u;
            }
        }

        // jump if top of stack != 0
        case JNZ: {
            if (stack_peek(vm, vm->data_stack).u != 0)
            {
                vm->ip = operand.u;
            }
        }
        
        // jump if top of stack > 0
        case JG: {
            if (stack_peek(vm, vm->data_stack).u > 0)
            {
                vm->ip = operand.u;
            }
        }

        // jump if top of stack >= 0
        case JGE: {
            if (stack_peek(vm, vm->data_stack).u >= 0)
            {
                vm->ip = operand.u;
            }
        }

        // jump if top of stack < 0
        case JL: {
            if (stack_peek(vm, vm->data_stack).u < 0)
            {
                vm->ip = operand.u;
            }
        }

        // jump if top of stack <= 0
        case JLE: {
            if (stack_peek(vm, vm->data_stack).u <= 0)
            {
                vm->ip = operand.u;
            }
        }
        
        default: {
            assert(0 && "unimplemented");
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
