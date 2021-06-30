#ifndef opcode_branch
#define opcode_branch
#include "memory_manage.h"

uint8_t getBranchType(struct processor *);

void branchOp(struct processor *);
#endif