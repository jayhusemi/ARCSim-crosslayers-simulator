#pragma once
#include "simulator.h"
#include "memory.h"
#include "vcd.h"
#include "instruction.h"

class CPU {
public:
    CPU(Simulator& sim, Memory& mem, VCD& vcd);
    void execute(const Instruction& inst);

private:
    Simulator& sim;
    Memory& mem;
    VCD& vcd;
};
