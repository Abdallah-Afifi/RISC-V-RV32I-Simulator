// register.h
#ifndef REGISTER_H
#define REGISTER_H

#include <array>
#include <cstdint>

class RegisterFile {
public:
    RegisterFile();

    // Function to get the value of a register
    uint32_t readRegister(uint8_t reg) const;

    // Function to set the value of a register
    void writeRegister(uint8_t reg, uint32_t value);

private:
    std::array<uint32_t, 32> registers;
};

#endif // REGISTER_H
