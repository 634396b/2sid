#ifndef opcode_math_logic
#define opcode_math_logic
#include "ops.h"
#include "memory_manage.h"

struct opCodeMethod
{
    void (*fn)(struct processor *);
};

extern struct opCodeMethod functionOpCodeMap[8];

/** 
 *  returns the value of source bits 
 *  Pattern: XXXXXX11
 */
uint8_t getSrcType(uint8_t);

/** 
 *  returns the value of destination bits 
 *  Pattern: XXXX11XX
 */
uint8_t getDestType(uint8_t);
/** 
 *  returns the value of function bits 
 *  Pattern: X111XXXX
 */
uint8_t getFunctionType(uint8_t);
void mathLogicOp(struct processor *);

void destSrcOp(struct processor *, uint16_t operation(uint16_t, uint16_t), char *);

void destOp(struct processor *, uint16_t operation(uint16_t), char*);

void AND(struct processor *);

void OR(struct processor *);

void XOR(struct processor *);

void ADD(struct processor *);

void SUB(struct processor *);

void INC(struct processor *);

void DEC(struct processor *);

void NOT(struct processor *);

#endif