#include "simulator.h"
#include "vcd.h"
#include "memory.h"
#include "cpu.h"
#include "instruction.h"
#include <iostream>

int main() {

    VCD vcd("wave.vcd");
    Simulator sim;


    // connect time hook
    sim.set_time_callback([&vcd](SimTime t) {
    vcd.set_time(t);
    });


    Memory mem(sim, vcd);
    CPU cpu(sim, mem, vcd);

    mem.write(100, 42);

    cpu.execute({OpCode::ADD, 10, 20, 0});
    cpu.execute({OpCode::MUL, 3, 5, 0});
    cpu.execute({OpCode::LOAD, 0, 0, 100});
    cpu.execute({OpCode::STORE, 99, 0, 200});

    sim.run();

    std::cout << "Simulation complete.\n";
    return 0;
}
