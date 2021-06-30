#ifndef processorModule
#define processorModule
#include "opcode_math_logic.h"
#include "opcode_memory.h"
#include "opcode_branch.h"

#define HALT_OPCODE 0x19
#define MEMORY_SIZE 0x2 << 15

// Storage (2^16)
extern uint8_t memory[MEMORY_SIZE];

extern struct processor p;

void fetchNextInstruction(void);
/** 
 *  returns single boolean digit if IR is mathematical operator 
 *  Pattern: 1000XXXX
 */
uint8_t isMathematicalOp(uint8_t);

/** 
 *  returns single boolean digit if IR is memory operator 
 *  Pattern: 0000XXXX
 */
uint8_t isMemoryOp(uint8_t);

/** 
 *  returns single boolean digit if IR is mathematical operator 
 *  Pattern: 00010XXX
 */
uint8_t isBranchOp(uint8_t);

uint8_t isNOOP(uint8_t);

void executeInstruction(void);

#endif