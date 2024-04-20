// memory.h
#ifndef MEMORY_H
#define MEMORY_H

#include <cstdint>
#include <unordered_map>

class Memory {
public:
    Memory();

    // Function to read a word from memory
    uint32_t readWord(uint32_t address) const;

    // Function to write a word to memory
    void writeWord(uint32_t address, uint32_t data);

private:
    // Internal storage using an unordered map to simulate sparse memory usage
    std::unordered_map<uint32_t, uint32_t> memory;

    // Helper function to check alignment
    bool isAligned(uint32_t address, uint32_t alignment) const;
};

#endif // MEMORY_H
