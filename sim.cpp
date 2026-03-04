#include <iostream>
#include <queue>
#include <functional>
#include <unordered_map>
#include <fstream>

using SimTime = uint64_t;

/* ============================= */
/*         VCD Writer            */
/* ============================= */

class VCD {
public:
    VCD(const std::string& filename) {
        out.open(filename);
        write_header();
    }

    ~VCD() {
        out.close();
    }

    void set_time(SimTime t) {
        out << "#" << t << "\n";
    }


    void dump(const std::string& id, int value) {
    std::string bin = "";

    for (int i = 31; i >= 0; --i) {
        bin += ((value >> i) & 1) ? '1' : '0';
    }

    out << "b" << bin << " " << id << "\n";
}
private:
    std::ofstream out;

   void write_header() {
    out << "$date\n   Today\n$end\n";
    out << "$version\n   Simple Simulator\n$end\n";
    out << "$timescale 1ns $end\n";
    out << "$scope module sim $end\n";

    out << "$var wire 32 r cpu_result $end\n";
    out << "$var wire 32 m mem_data $end\n";

    out << "$upscope $end\n";
    out << "$enddefinitions $end\n";

    // IMPORTANT: initial values
    out << "#0\n";
    out << "b0 r\n";
    out << "b0 m\n";
    }
};

/* ============================= */
/*         Event System          */
/* ============================= */

struct Event {
    SimTime time;
    uint64_t seq;
    std::function<void()> callback;

    bool operator<(const Event& other) const {
        if (time == other.time)
            return seq > other.seq;
        return time > other.time;
    }
};

class Simulator {
public:
    Simulator(VCD& vcd) : vcd(vcd) {}

    void schedule(SimTime delay, std::function<void()> cb) {
        event_queue.push(
            {current_time + delay, next_seq++, std::move(cb)}
        );
    }

    void run() {
        while (!event_queue.empty()) {
            Event ev = event_queue.top();
            event_queue.pop();

            current_time = ev.time;
            vcd.set_time(current_time);
            ev.callback();
        }
    }

    SimTime now() const { return current_time; }

private:
    SimTime current_time = 0;
    uint64_t next_seq = 0;
    std::priority_queue<Event> event_queue;
    VCD& vcd;
};

/* ============================= */
/*            Memory             */
/* ============================= */

class Memory {
public:
    Memory(Simulator& sim, VCD& vcd)
        : sim(sim), vcd(vcd) {}

    void read(uint64_t addr, std::function<void(int)> cb) {
        sim.schedule(50, [this, addr, cb]() {
            int value = mem[addr];
            vcd.dump("m", value);
            cb(value);
        });
    }

    void write(uint64_t addr, int value) {
        sim.schedule(50, [this, addr, value]() {
            mem[addr] = value;
            vcd.dump("m", value);
        });
    }

private:
    Simulator& sim;
    VCD& vcd;
    std::unordered_map<uint64_t, int> mem;
};

/* ============================= */
/*              CPU              */
/* ============================= */

enum class OpCode { ADD, MUL, LOAD, STORE };

struct Instruction {
    OpCode op;
    int op1;
    int op2;
    uint64_t addr;
};

class CPU {
public:
    CPU(Simulator& sim, Memory& mem, VCD& vcd)
        : sim(sim), mem(mem), vcd(vcd) {}

    void execute(const Instruction& inst) {

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
            mem.read(inst.addr,
                [this](int value) {
                    vcd.dump("r", value);
                });
            break;

        case OpCode::STORE:
            mem.write(inst.addr, inst.op1);
            break;
        }
    }

private:
    Simulator& sim;
    Memory& mem;
    VCD& vcd;
};

/* ============================= */
/*              MAIN             */
/* ============================= */

int main() {

    VCD vcd("wave.vcd");
    Simulator sim(vcd);
    Memory mem(sim, vcd);
    CPU cpu(sim, mem, vcd);

    mem.write(100, 42);

    cpu.execute({OpCode::ADD, 10, 20, 0});
    cpu.execute({OpCode::MUL, 3, 5, 0});
    cpu.execute({OpCode::LOAD, 0, 0, 100});
    cpu.execute({OpCode::STORE, 99, 0, 200});

    sim.run();

    std::cout << "Waveform written to wave.vcd\n";

    return 0;
}