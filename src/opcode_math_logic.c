#include "opcode_math_logic.h"
#include <stdint.h>
#include <stdio.h>

struct opCodeMethod functionOpCodeMap[8] = {
    { AND },
    { OR  },
    { XOR },
    { ADD },
    { SUB },
    { INC },
    { DEC },
    { NOT }
};

/** 
 *  returns the value of source bits 
 *  Pattern: XXXXXX11
 */
uint8_t getSrcType(uint8_t IR){
    return IR&0x03;
}

/** 
 *  returns the value of destination bits 
 *  Pattern: XXXX11XX
 */
uint8_t getDestType(uint8_t IR){
    return (IR&0x0C) >> 2;
}

/** 
 *  returns the value of function bits 
 *  Pattern: X111XXXX
 */
uint8_t getFunctionType(uint8_t IR){
    return (IR&0x70) >> 4;
}

void mathLogicOp(struct processor* p){
    uint8_t functionType = getFunctionType(p->IR);
    // Execute the function mapped
    functionOpCodeMap[functionType].fn(p);
}

void destSrcOp(struct processor* p, uint16_t operation(uint16_t, uint16_t), char* opStr){
    uint8_t srcType = getSrcType(p->IR);
    uint8_t destType = getDestType(p->IR);
    // MAR Indirect
    if (destType == 0x0){
        if(srcType == 0x0){ // indirect MAR & indirect MAR
            printf("%s [MAR (0x%04X)], [MAR (0x%04X)]", opStr, p->MAR, p->MAR);
            setMARIndirect(p, (uint8_t) operation((uint16_t) getMARIndirect(p), (uint16_t) getMARIndirect(p)));
            p->bytesUsed = 1;
        }else if (srcType == 0x1){ // MAR Indirect & ACC
            printf("%s [MAR (0x%04X)], ACC (0x%04X)", opStr, p->MAR, p->ACC);
            setMARIndirect(p, (uint8_t) operation((uint16_t) getMARIndirect(p), (uint16_t) getACC(p)));
            p->bytesUsed = 1;
        } else if (srcType == 0x2){ // Indirect & constant
            printf("%s [MAR (0x%04X)], 0x%04X", opStr, p->MAR, getBitsAfterOpCode16(p));
            setMARIndirect(p, (uint8_t) operation((uint16_t) getMARIndirect(p), (uint16_t) getBitsAfterOpCode8(p)));
            p->bytesUsed = 2;
        } else if (srcType == 0x3){ // Indirect & memory
            printf("%s [MAR (0x%04X)], [0x%04X] (0x%04X)", opStr, p->MAR, getBitsAfterOpCode16(p), getDirectMemoryData(p, getBitsAfterOpCode16(p)));
            setMARIndirect(p, (uint8_t) operation((uint16_t) getMARIndirect(p), (uint16_t) getDirectMemoryData(p, getBitsAfterOpCode16(p))));
            p->bytesUsed = 3;
        } else {
            printf("[%s - MAR indirect] INVALID OPCODE %d %d", opStr, destType, srcType);
        }
    } else if (destType == 0x1){ // ACC
        if(srcType == 0x0){ // ACC & MAR indirect
            printf("%s ACC (0x%04X), [MAR 0x%04X]", opStr, p->ACC, p->MAR);
            setACC(p, (uint8_t) operation((uint16_t) getACC(p), (uint16_t) getMARIndirect(p)));
            p->bytesUsed = 1;
        } else if (srcType == 0x1){ // ACC & ACC
            printf("%s ACC (0x%04X), ACC (0x%04X)", opStr, p->ACC, p->ACC);
            setACC(p, (uint8_t) operation((uint16_t) getACC(p), (uint16_t) getACC(p)));
            p->bytesUsed = 1;
        } else if (srcType == 0x2){ // ACC & constant
            printf("%s ACC (0x%04X), 0x%04X", opStr, p->ACC, getBitsAfterOpCode8(p));
            setACC(p, (uint8_t) operation((uint16_t) getACC(p),(uint16_t) getBitsAfterOpCode8(p)));
            p->bytesUsed = 2;
        } else if (srcType == 0x3) { // ACC & memory
            printf("%s ACC (0x%04X), [0x%04X] (0x%04X)", opStr, p->ACC, getBitsAfterOpCode16(p), getDirectMemoryData(p, getBitsAfterOpCode16(p)));
            setACC(p, (uint8_t) operation((uint16_t) getACC(p), (uint16_t) getDirectMemoryData(p, getBitsAfterOpCode16(p))));
            p->bytesUsed = 3;
        } else {
            printf("[%s - ACC] INVALID OPCODE %d %d", opStr,destType, srcType);
        }
    } else if (destType == 0x2){ // MAR
        if(srcType == 0x0){ // MAR & memory indirect operation on 16 bit and 8 bit number?
            printf("%s MAR (0x%04X), [MAR 0x%04X]", opStr, p->MAR, p->MAR);
            setMAR(p, operation(getMAR(p), (uint16_t) getMARIndirect(p)));
            p->bytesUsed = 1;
        } else if (srcType == 0x1){ // MAR & ACC
            printf("%s MAR (0x%04X), ACC (0x%04X)", opStr, p->MAR, p->ACC);
            setMAR(p, operation(getMAR(p), (uint16_t) getACC(p)));
            p->bytesUsed = 1;
        } else if (srcType == 0x2){ // MAR & constant (has to be 16 bits since MAR is 16 bits)
            printf("%s MAR (0x%04X), 0x%04X", opStr, p->MAR, getBitsAfterOpCode16(p));
            setMAR(p, operation(getMAR(p), getBitsAfterOpCode16(p)));
            p->bytesUsed = 3;
        }else if (srcType == 0x3){ // Memory
            printf("%s MAR (0x%04X), [0x%04X] (0x%04X)", opStr, p->MAR, getBitsAfterOpCode16(p), getDirectMemoryData(p, getBitsAfterOpCode16(p)));
            setMAR(p, operation(getMAR(p), (uint16_t) getDirectMemoryData(p, getBitsAfterOpCode16(p))));
            p->bytesUsed = 3;
        } else { 
            printf("[%s - MAR]INVALID OPCODE %d %d",opStr, destType, srcType);
        }
    } else if (destType == 0x3){ 
        if(srcType == 0x0){ // memory & MAR  indirect
            printf("%s [0x%04X], [MAR 0x%04X]", opStr, getBitsAfterOpCode16(p), p->MAR);
            setDirectMemory(p, (uint8_t) operation((uint16_t) getDirectMemoryData(p, getBitsAfterOpCode16(p)), (uint16_t) getMARIndirect(p)), getBitsAfterOpCode16(p));
            p->bytesUsed = 3;
        } else if (srcType == 0x1){ // memory & ACC
            printf("%s [0x%04X], 0x%04X", opStr, getBitsAfterOpCode16(p), p->ACC);
            setDirectMemory(p, (uint8_t) operation((uint16_t) getDirectMemoryData(p, getBitsAfterOpCode16(p)), (uint16_t) getACC(p)), getBitsAfterOpCode16(p));
            p->bytesUsed = 3;
        // 0x2 (constant) and 0x3 (memory) are not valid since it would require additional space after OP code.
        } else {
            printf("[%s - Memory]INVALID OPCODE %d %d", opStr, destType, srcType);
        }
    }
}

void destOp(struct processor*p, uint16_t operation(uint16_t), char*opStr){
    uint8_t destType = getDestType(p->IR);
    if(destType == 0x0){ // MAR indirect
        printf("%s [MAR 0x%04X]", opStr, p->MAR);
        setMARIndirect(p, (uint8_t) operation((uint16_t) getMARIndirect(p)));
        p-> bytesUsed = 1;
    } else if (destType == 0x1){ //ACC
        printf("%s ACC (0x%04X)", opStr, p->ACC);
        setACC(p, (uint8_t) operation((uint16_t) getACC(p)));
        p->bytesUsed = 1;
    } else if (destType == 0x2){// MAR
        printf("%s MAR (0x%04X)", opStr, p->MAR);
        setMAR(p, operation(getMAR(p)));
        p->bytesUsed = 1;
    } else if (destType == 0x3){ // Direct
        printf("%s [0x%04X]", opStr, getBitsAfterOpCode16(p));
        setDirectMemory(p, (uint8_t) operation((( (uint16_t) getDirectMemoryData(p, getBitsAfterOpCode16(p))))), getBitsAfterOpCode16(p));
        p->bytesUsed = 3;
    }
}

void AND(struct processor* p){
    destSrcOp(p, bAND, "AND");
}

void OR(struct processor *p){
    destSrcOp(p, bOR, "OR");
}

void XOR(struct processor *p){
    destSrcOp(p, bXOR, "XOR");
}

void ADD(struct processor *p){
    destSrcOp(p, aADD, "ADD");
}

void SUB(struct processor *p){
    destSrcOp(p, aSUB, "SUB");
}

void INC(struct processor *p){
    destOp(p, bINC, "INC");
}

void DEC(struct processor *p){
    destOp(p, bDEC, "DEC");
}

void NOT(struct processor *p){
    destOp(p, bNOT, "NOT");
}