#pragma once
#include <queue>
#include <functional>
#include "common.h"

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
    void schedule(SimTime delay, std::function<void()> cb);
    void run();
    SimTime now() const;

    void set_time_callback(std::function<void(SimTime)> cb);

private:
    SimTime current_time = 0;
    uint64_t next_seq = 0;
    std::priority_queue<Event> event_queue;
    std::function<void(SimTime)> time_callback;
};