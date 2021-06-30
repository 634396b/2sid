#include "opcode_branch.h"
#include <stdint.h>

uint8_t getBranchType(struct processor* p){
    return p->IR & 0x07;
}

void branchOp(struct processor* p){
    uint8_t branchType = getBranchType(p);

    switch (branchType){
        case 0x0:
            printf("BRA 0x%04X (%s)", getBitsAfterOpCode16(p), "true");
            setPC(p);
            p->bytesUsed = 0;
            break;
        case 0x1:
            printf("BRZ 0x%04X (%s)", getBitsAfterOpCode16(p), getACC(p) == 0 ? "true" : "false");
            if (getACC(p) == 0){
                setPC(p);
                p->bytesUsed = 0; // Do not increment PC since we branched
            } else{
                p->bytesUsed = 3; // increment PC by 3 because failed branch
            }
            break;
        case 0x2:
            printf("BNE 0x%04X (%s)", getBitsAfterOpCode16(p), getACC(p) != 0 ? "true" : "false");
            if(getACC(p) != 0){
                setPC(p);
                p->bytesUsed = 0;
            } else{
                p->bytesUsed = 3; // increment PC by 3 because failed branch
            }
            break;
        case 0x3:
            printf("BLT 0x%04X (%s)", getBitsAfterOpCode16(p), getACC(p) < 0 ? "true" : "false");
            if(getACC(p) < 0){
                setPC(p);
                p->bytesUsed = 0;
            } else{
                p->bytesUsed = 3; // increment PC by 3 because failed branch
            }
            break;
        case 0x4:
            printf("BLE 0x%04X (%s)", getBitsAfterOpCode16(p), getACC(p) <= 0 ? "true" : "false");
            if (getACC(p) <= 0){
                setPC(p);
                p->bytesUsed = 0;
            } else{
                p->bytesUsed = 3; // increment PC by 3 because failed branch
            }
            break;
        case 0x5:
            printf("BGT 0x%04X (%s)", getBitsAfterOpCode16(p), getACC(p) > 0 ? "true" : "false");
            if(getACC(p) > 0){
                setPC(p);
                p->bytesUsed = 0;
            } else{
                p->bytesUsed = 3; // increment PC by 3 because failed branch
            }
            break;
        case 0x6:
            printf("BGE 0x%04X (%s)", getBitsAfterOpCode16(p), getACC(p) >= 0 ? "true" : "false");
            if(getACC(p) >= 0){
                setPC(p);
                p->bytesUsed = 0;
            } else{
                p->bytesUsed = 3; // increment PC by 3 because failed branch
            }
            break;
    }
}