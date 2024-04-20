// memory.cpp
#include "memory.h"
#include <stdexcept>

Memory::Memory() {
    // Constructor, possibly initialize the memory map if needed
}

uint32_t Memory::readWord(uint32_t address) const {
    if (!isAligned(address, 4)) {
        throw std::runtime_error("Memory access error: Address not aligned to 4-byte boundary.");
    }

    auto it = memory.find(address);
    if (it != memory.end()) {
        return it->second;
    } else {
        return 0;  // Return 0 for uninitialized memory
    }
}

void Memory::writeWord(uint32_t address, uint32_t data) {
    if (!isAligned(address, 4)) {
        throw std::runtime_error("Memory access error: Address not aligned to 4-byte boundary.");
    }

    memory[address] = data;
}

bool Memory::isAligned(uint32_t address, uint32_t alignment) const {
    return (address % alignment) == 0;
}
