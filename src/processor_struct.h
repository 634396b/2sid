#ifndef processorStructModule
#define processorStructModule
#include <stdint.h>

typedef struct processor{
    uint8_t* memory;
    uint8_t ACC;
    uint8_t IR;
    uint16_t MAR;
    uint16_t PC;
    uint8_t bytesUsed;
} processor;
#endif