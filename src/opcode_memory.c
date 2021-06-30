#include "opcode_memory.h"
#include <stdint.h>
#include <stdio.h>

uint8_t getMemoryFunctionType(uint8_t IR){
    return (IR & 0x08) >> 3;
}

uint8_t getMemoryRegisterType(uint8_t IR){
    return (IR & 0x04) >> 2;
}

uint8_t getMemoryMethodType(uint8_t IR){
    return (IR & 0x03);
}

void memoryOp(struct processor* p){
    uint8_t functionType = getMemoryFunctionType(p->IR);
    uint8_t registerType = getMemoryRegisterType(p->IR);
    uint8_t methodType = getMemoryMethodType(p->IR);
    if (registerType == 0x0){ // ACC register
        if(methodType == 0x0){ // direct memory
            if(functionType== 0x1){ // LOAD into ACC
                printf("LOAD ACC, [0x%04X] (0x%04X)", getBitsAfterOpCode16(p), getDirectMemoryData(p, getBitsAfterOpCode16(p)));
                setACC(p, getDirectMemoryData(p,getBitsAfterOpCode16(p)));
            } else { // STORE into memory
                printf("STORE ACC (0x%04X), [0x%04X]",p->ACC, getBitsAfterOpCode16(p));
                setDirectMemory(p, getACC(p),getBitsAfterOpCode16(p));
            }
            p->bytesUsed = 3;
        } else if (methodType == 0x1){ // constant
            if(functionType == 0x1){ // LOAD into ACC
                printf("LOAD ACC, 0x%04X", getBitsAfterOpCode8(p));
                setACC(p, getBitsAfterOpCode8(p));
            } else {
                printf("INVALID OP CODE CANNOT LOAD ACC INTO CONSTANT");
                p->bytesUsed = 1; // Error happened, but increment PC by 1 byte
            }
            p->bytesUsed = 2;
        } else if (methodType == 0x2){ // register indirect (MAR)
            if(functionType == 0x1){ // LOAD into ACC
                printf("LOAD ACC, [MAR 0x%04X] (0x%04X)", p->MAR, getMARIndirect(p));
                setACC(p, getMARIndirect(p));
            } else { // STORE into memory (register indirect)
                printf("STORE ACC (0x%04X), [MAR 0x%04X]",p->ACC, p->MAR);
                setMARIndirect(p, getACC(p));
            }
            p->bytesUsed = 1;
        }
    } else if (registerType == 0x1){ // MAR register
        if(methodType == 0x0){ // memory address
            if(functionType == 0x1){ //load
                printf("LOAD MAR, [0x%04X]", getBitsAfterOpCode16(p));
                // Set MAR to the memory data (16 bits), shift over and get the next (+1) memory data and OR with previous memory data to produce 16 bits MAR 
                setMAR(p, (((uint16_t) getDirectMemoryData(p, getBitsAfterOpCode16(p))) << 8) | ((uint16_t)getDirectMemoryData(p, getBitsAfterOpCode16(p)+1)));
            } else{
                printf("STORE MAR (0x%04X), [0x%04X]",p->MAR, getBitsAfterOpCode16(p));
                setDirectMemory(p, (uint8_t) (getMAR(p)>>8), getBitsAfterOpCode16(p));
                setDirectMemory(p, getMAR(p)&0x00FF, getBitsAfterOpCode16(p) + 1);
            }
            p->bytesUsed = 3;
        } else if (methodType == 0x01){ // constant
            if(functionType == 0x1){  // LOAD constant INTO MAR
                printf("LOAD MAR, 0x%04X", getBitsAfterOpCode16(p));
                setMAR(p, getBitsAfterOpCode16(p));
                p->bytesUsed = 3;
            } else {
                printf("INVALID OP CODE CANNOT STORE MAR INTO CONSTANT");
            }
        } else if (methodType == 0x02){ // register indirect (MAR)
            if(functionType == 0x1){ // load indirect into MAR
                printf("LOAD MAR, [MAR 0x%04X] (0x%04X)", p->MAR, getMARIndirect(p));
                setMAR(p, (((uint16_t) getMARIndirect(p)) << 8) | ((uint16_t) p->memory[p->MAR + 1]));
            } else { // store MAR into indirect
                printf("STORE MAR, [MAR 0x%04X] (0x%04X)", p->MAR, getMARIndirect(p));
                p->memory[p->MAR] = (uint8_t) (p->MAR >> 8);
                p->memory[p->MAR+1] = p->MAR & 0x00FF;
            }
            p->bytesUsed = 1;
        }

    }
}