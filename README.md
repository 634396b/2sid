# Two-Stage Instuction Decoder

## Goal
* Simulation for fetching of next instruction cycle, `fetchNextInstruction()`,
* Simulation of execute instruction cycle, `executeInstruction()`.

Neither of these functions has parameters nor do they return values. They operate on global data meant to simulate the registers and memory of the processor. This simulated machine consists of four registers that represented with four global variables.

* PC -- Program counter (16 bit) used to hold the address of the next instruction to execute. It is initialized to zero.
* IR -- Instruction register (8 bit) used to hold the current instruction being executed.
* MAR -- Memory Address Register (16 bit) used to hold an address being used as a pointer, i.e., an indirect reference to data in memory.
* ACC -- Accumulator (8 bit) used to operate on data. Memory is simulated with an array `memory[65536]`.

The function `fetchNextInstruction()` performs the following steps:
* Use the program counter (PC) as an index to retrieve an instruction from the array `memory[]`.
* Store the retrieved instruction to the instruction register (IR).
* Determine from the instruction how much to increment PC so that it points to the next instruction in `memory[]` and perform the increment.

The function `executeInstruction()` examines the IR to determine which operation to perform and it performs this operation on the data contained in the registers and in the array `memory[]`.