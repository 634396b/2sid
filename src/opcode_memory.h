#ifndef opcode_memory
#define opcode_memory
#include "memory_manage.h"

uint8_t getMemoryFunctionType(uint8_t);

uint8_t getMemoryRegisterType(uint8_t);

uint8_t getMemoryMethodType(uint8_t);

void memoryOp(struct processor* );

#endif