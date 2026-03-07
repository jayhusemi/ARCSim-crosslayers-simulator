#include "cpu.h"

CPU::CPU(Simulator& sim, Memory& mem, VCD& vcd)
    : sim(sim), mem(mem), vcd(vcd) {}

void CPU::execute(const Instruction& inst) {

    switch (inst.op) {

    case OpCode::ADD:
        sim.schedule(10, [this, inst]() {
            int result = inst.op1 + inst.op2;
            vcd.dump("r", result);
        });
        break;

    case OpCode::MUL:
        sim.schedule(10, [this, inst]() {
            int result = inst.op1 * inst.op2;
            vcd.dump("r", result);
        });
        break;

    case OpCode::LOAD:
        mem.read(inst.addr, [this](int value) {
            vcd.dump("r", value);
        });
        break;

    case OpCode::STORE:
        mem.write(inst.addr, inst.op1);
        break;
    }
}
