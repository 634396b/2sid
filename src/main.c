#include "processor.h"
#include "file_io.h"

int main(void) {
    readMemoryIn(p.memory);
    printf("%4s PC %9s IR %5s Instructions\n", " ", " ", " ");
    while (p.memory[p.PC] != HALT_OPCODE){
        fetchNextInstruction();
        executeInstruction();
    }
    writeMemoryOut(p.memory);
    return 0;
}
