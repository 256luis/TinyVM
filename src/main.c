// this file is currently being used for testing purposes

#define _CRT_SECURE_NO_WARNINGS // stupid microsoft
#include <stdio.h>
#include <stdlib.h>
#include "vm.h"
#include "types.h"

#define DWORD_INT(num) (Dword){ .u = num }
#define DWORD_FLOAT(num) (Dword){ .f = num }

static Instruction* load_program(const char* path)
{
    FILE* file = fopen(path, "rb");
    if (file == NULL)
        return NULL;

    // turn file into array of instructions
    Instruction* program;
    {
        // turn the file into an array of bytes
        uint8_t* program_bytes;
        size_t file_size;
        {
            // find file size
            fseek(file, 0, SEEK_END);
            file_size = ftell(file);
            rewind(file);
            
            // allocate appropriate number of bytes
            program_bytes = malloc(file_size);
            if (program_bytes == NULL)
                return NULL;

            // read file into program_bytes
            fread(program_bytes, 1, file_size, file);
        }

        // how many instructions for that many bytes?
        size_t instruction_count = file_size / INSTRUCTION_SIZE;
        program = malloc(instruction_count * sizeof(Instruction));

        // finally, load the bytes into the instruction array
        for (size_t i = 0, j = 0; i < file_size; i += INSTRUCTION_SIZE, j++)
        {
            Dword operand = {
                .bytes[0] = program_bytes[i + 1],
                .bytes[1] = program_bytes[i + 2],
                .bytes[2] = program_bytes[i + 3],
                .bytes[3] = program_bytes[i + 4],
            };
            
            program[j] = (Instruction){
                .opcode = program_bytes[i],
                .operand = operand
            };
        }
        free(program_bytes);
    }

    return program;
}

int main(int argc, char* argv[])
{
    if (argc < 2)
    {
        printf("No file specified.\n");
        return 1;
    }
    
    Instruction* program = load_program(argv[1]);
    if (program == NULL)
    {
        printf("Error loading file.\n");
        return 1;
    }

    VM* vm = &(VM){0};
    while (!vm->should_halt)
    {
        vm_execute_instruction(vm, program[vm->ip]);
    }

    /* vm_dump(vm); */
    
    return 0;
}
