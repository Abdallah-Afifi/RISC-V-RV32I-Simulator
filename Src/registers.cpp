// register.cpp
#include "register.h"

RegisterFile::RegisterFile() {
    // Initialize all registers to 0
    registers.fill(0);
}

uint32_t RegisterFile::readRegister(uint8_t reg) const {
    // Register 0 always reads as 0
    if (reg == 0) {
        return 0;
    }

    // Check if register number is valid to avoid out-of-bounds access
    if (reg >= registers.size()) {
        throw std::out_of_range("Register access error: Register index is out of range.");
    }

    return registers[reg];
}

void RegisterFile::writeRegister(uint8_t reg, uint32_t value) {
    // Register 0 cannot be written to, ignore any writes to register 0
    if (reg == 0) {
        return;
    }

    // Check if register number is valid to avoid out-of-bounds access
    if (reg >= registers.size()) {
        throw std::out_of_range("Register access error: Register index is out of range.");
    }

    registers[reg] = value;
}
