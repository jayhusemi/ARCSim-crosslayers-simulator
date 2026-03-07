#pragma once
#include <fstream>
#include <string>
#include "common.h"

class VCD {
public:
    VCD(const std::string& filename);
    ~VCD();

    void set_time(SimTime t);
    void dump(const std::string& id, int value);

private:
    std::ofstream out;
    void write_header();
};