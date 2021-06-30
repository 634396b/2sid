#include "processor.h"
#include <stdint.h>
#include <stdio.h>

uint8_t memory[MEMORY_SIZE];

struct processor p = {
    // Memory storage
    memory: memory,
    // Accumulator register (8 bits)
    ACC: 0x0,
    // Instruction register (8 bits)
    IR: 0x0,
    // Memory address register (16 bits)
    MAR: 0x0,
    // Program counter (16 bits)
    PC: 0x0,
    // Last Operation bytes used (8 bits)
    bytesUsed: 0x0,
};

void fetchNextInstruction(void){
    // Next x bytes
    p.PC = p.PC + p.bytesUsed;
    p.IR = p.memory[p.PC];
    char pad[2] = {' '};
    printf("[%2s %04d %2s] %3s 0x%02X %5s", pad, p.PC,pad, pad, p.IR, pad);
}

/** 
 *  returns single boolean digit if IR is mathematical operator 
 *  Pattern: 1XXXXXXX
 */
uint8_t isMathematicalOp(uint8_t IR){
    return (IR & 0x80) == 0x80;
}

/** 
 *  returns single boolean digit if IR is memory operator 
 *  Pattern: 0000XXXX
 */
uint8_t isMemoryOp(uint8_t IR){
    return (IR & 0xF0) == 0x00;
}

/** 
 *  returns single boolean digit if IR is mathematical operator 
 *  Pattern: 00010XXX
 */
uint8_t isBranchOp(uint8_t IR){
    return (IR & 0xF8) == 0x10;
}

uint8_t isNOOP(uint8_t IR){
    return (IR & 0xFF) == 0x18;
}

void executeInstruction(void){
    if (isNOOP(p.IR)) return;
    // Masks 
    uint8_t useMath = isMathematicalOp(p.IR);
    uint8_t useMemory = isMemoryOp(p.IR);
    uint8_t useBranch = isBranchOp(p.IR);
    // Reset used bytes, will always be at least one since op code counts as 1 byte
    p.bytesUsed = 0x1;
    if(useMath == 0x1){
        mathLogicOp(&p);
    } else if (useMemory == 0x1){
        memoryOp(&p);
    } else if (useBranch == 0x1){
        branchOp(&p);
    } else {
        printf("[executeInstruction] Invalid OPCODE instruction type");
    }
    printf("\n");
}

