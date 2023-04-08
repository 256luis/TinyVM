#ifndef TYPES_H
#define TYPES_H

#include <stdint.h>

#define DWORD_ZERO ((Dword){ .u = 0 })

typedef union Dword
{
    float f;
    uint32_t u;
    int32_t s;
    uint8_t bytes[4];
} Dword;

#endif // TYPES_H
