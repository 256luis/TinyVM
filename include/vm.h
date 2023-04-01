#ifndef VM_H
#define VM_H

#include <stdint.h>
#include <stdbool.h>
#include <assert.h>
#include "types.h"

#define DATA_STACK_SIZE 512
#define RETURN_STACK_SIZE 128
#define MEMORY_SIZE 1024

typedef struct VM
{
    // main memory
    Dword memory[MEMORY_SIZE];

    // stack to do operations in
    Dword data_stack[DATA_STACK_SIZE];
    int dsp; // register that stores a pointer to the top of the data stack

    // stack that exclusively stores return addresses for when a procedure is called
    uint32_t return_stack[RETURN_STACK_SIZE];
    int rsp; // register that stores a pointer to the top of the return stack

    // register that stores a pointer to the current instruction
    int ip;
} VM;

typedef enum Opcode
{
    PUSHL, PUSHA, POP,
    ADDI, ADDF,
    SUBI, SUBF,
    MULI, MULF,
    DIVI, DIVF,
    JMP, JZ, JNZ, JG, JGE, JL, JLE,
    AND, OR, NOT, XOR,

    OUT,
    
    OPCODE_COUNT
} Opcode;

typedef struct Instruction
{
    Opcode opcode;
    Dword operand;
} Instruction;

void vm_execute_instruction(VM* vm, Instruction inst);
void vm_dump(VM* vm);
    
#endif // VM_H
