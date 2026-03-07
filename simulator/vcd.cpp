#include "vcd.h"

VCD::VCD(const std::string& filename) {
    out.open(filename);
    write_header();
}

VCD::~VCD() {
    out.close();
}

void VCD::write_header() {
    out << "$date\n Today\n$end\n";
    out << "$version\n Simple Simulator\n$end\n";
    out << "$timescale 1ns $end\n";
    out << "$scope module sim $end\n";
    out << "$var wire 32 r cpu_result $end\n";
    out << "$var wire 32 m mem_data $end\n";
    out << "$upscope $end\n";
    out << "$enddefinitions $end\n";

    out << "#0\n";
    out << "b0 r\n";
    out << "b0 m\n";
}

void VCD::set_time(SimTime t) {
    out << "#" << t << "\n";
}

void VCD::dump(const std::string& id, int value) {
    std::string bin;
    for (int i = 31; i >= 0; --i)
        bin += ((value >> i) & 1) ? '1' : '0';

    out << "b" << bin << " " << id << "\n";
}
