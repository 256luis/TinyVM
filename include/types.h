#ifndef TYPES_H
#define TYPES_H

#include <stdint.h>

#define DWORD_ZERO ((Dword){ .u = 0 })

typedef union Dword
{
    float f;
    uint32_t u;
} Dword;

#endif // TYPES_H
