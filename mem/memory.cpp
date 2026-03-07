#include "memory.h"

Memory::Memory(Simulator& sim, VCD& vcd)
    : sim(sim), vcd(vcd) {}

void Memory::read(uint64_t addr, std::function<void(int)> cb) {
    sim.schedule(50, [this, addr, cb]() {
        int value = mem[addr];
        vcd.dump("m", value);
        cb(value);
    });
}

void Memory::write(uint64_t addr, int value) {
    sim.schedule(50, [this, addr, value]() {
        mem[addr] = value;
        vcd.dump("m", value);
    });
}
