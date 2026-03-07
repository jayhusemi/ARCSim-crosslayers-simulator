#pragma once
#include <unordered_map>
#include <functional>
#include "simulator.h"
#include "vcd.h"

class Memory {
public:
    Memory(Simulator& sim, VCD& vcd);

    void read(uint64_t addr, std::function<void(int)> cb);
    void write(uint64_t addr, int value);

private:
    Simulator& sim;
    VCD& vcd;
    std::unordered_map<uint64_t, int> mem;
};
