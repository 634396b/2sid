#include "memory_manage.h"
#include <stdint.h>

uint8_t getBitsAfterOpCode8(struct processor* p){
    return (p ->memory[p->PC+1]);
}

uint16_t getBitsAfterOpCode16(struct processor* p){
    uint16_t a = (uint16_t) p->memory[p->PC + 1] << 8;
    uint16_t b = (uint16_t) p->memory[p->PC + 2];
    return a|b;
}

void setMARIndirect(struct processor* p, uint8_t value){
    p->memory[p->MAR] = value;
}

void setDirectMemory(struct processor* p, uint8_t value, uint16_t address){
    p->memory[address] = value;
}

void setACC(struct processor* p, uint8_t value){
    p->ACC = value;
}

uint8_t getDirectMemoryData(struct processor*p, uint16_t address){
    return p->memory[address];
}

uint8_t getACC(struct  processor*p){
    return p->ACC;
}

uint8_t getMARIndirect(struct processor*p){
    return p->memory[p->MAR];
}

void setMAR(struct processor* p, uint16_t value){
    p->MAR = value;
}

uint16_t getMAR(struct processor*p){
    return p->MAR;
}

void setPC(struct processor* p){
    p->PC = getBitsAfterOpCode16(p);
}