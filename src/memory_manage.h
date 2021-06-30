#ifndef memoryModule
#define memoryModule

#include "processor_struct.h"

uint8_t getBitsAfterOpCode8(struct processor*);

uint16_t getBitsAfterOpCode16(struct processor*);

void setMARIndirect(struct processor*, uint8_t);

void setDirectMemory(struct processor*, uint8_t, uint16_t);

void setACC(struct processor*, uint8_t);

uint8_t getDirectMemoryData(struct processor*, uint16_t);

uint8_t getACC(struct  processor*);

uint8_t getMARIndirect(struct processor*);

void setMAR(struct processor* , uint16_t);

uint16_t getMAR(struct processor*);

void setPC(struct processor* );

#endif