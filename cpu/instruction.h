#pragma once
#include <cstdint>

enum class OpCode { ADD, MUL, LOAD, STORE };

struct Instruction {
    OpCode op;
    int op1;
    int op2;
    uint64_t addr;
};
