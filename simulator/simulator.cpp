#include "simulator.h"

Simulator::Simulator(VCD& vcd)
    : vcd(vcd) {}

void Simulator::schedule(SimTime delay, std::function<void()> cb) {
    event_queue.push({current_time + delay, next_seq++, std::move(cb)});
}

void Simulator::run() {
    while (!event_queue.empty()) {
        Event ev = event_queue.top();
        event_queue.pop();

        current_time = ev.time;

          // IMPORTANT
        vcd.set_time(current_time);

        ev.callback();
    }
}

SimTime Simulator::now() const {
    return current_time;
}
