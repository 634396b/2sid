#include "ops.h"
#include <stdint.h>

uint16_t bAND(uint16_t c1, uint16_t c2){
    return c1 & c2;
}

uint16_t bOR(uint16_t c1, uint16_t c2){
    return c1 | c2;
}

uint16_t bXOR(uint16_t c1, uint16_t c2){
    return c1 | c2;
}

uint16_t aADD(uint16_t c1, uint16_t c2){
    return c1 + c2;
}

uint16_t aSUB(uint16_t c1, uint16_t c2){
    return c1 - c2;
}

uint16_t bINC(uint16_t value){
    return value + 1;
}

uint16_t bDEC(uint16_t value){
    return value - 1;
}

uint16_t bNOT(uint16_t value){
    return ~value;
}