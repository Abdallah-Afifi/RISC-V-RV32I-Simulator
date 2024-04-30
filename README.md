# RISC-V-RV32I-Simulator

This RISC-V Simulator implements the RV32I base integer instruction set, supporting a comprehensive suite of user-level instructions. Designed for educational purposes, it provides an interactive environment to simulate the execution of RISC-V assembly code.

## Features

- Support for all 40 user-level instructions of the RV32I base set, excluding ECALL, EBREAK, and FENCE.
- Simulation outputs for program counter, register file contents, and memory contents after each instruction execution.

## Getting Started

These instructions will guide you on how to get the simulator up and running on your local machine.

### Prerequisites

What you need to install the software:

- Any standard C++ compiler (GCC recommended)

### Installation

1. Clone the repository:
   ```bash
   git clone https://github.com/Abdallah-Afifi/RISC-V-RV32I-Simulator
   ```
2. Navigate to the project directory:
   ```bash
   cd RISC-V-RV32I-Simulator
   ```
3. Compile the project:
   ```bash
   g++ -o sim g++ B.cpp helper.cpp I.cpp J.cpp R.cpp ru.cpp S.cpp U.cpp
   ```

## Usage

Follow these steps to simulate a RISC-V program:

1. Launch the simulator:
   ```bash
   ./sim
   ```
2. Enter `1` to proceed with the simulator setup.
3. Provide the path to the assembly file you wish to simulate.
4. Input the starting address for your program (program counter).
5. Choose the register output format (hexadecimal, binary, or decimal).
6. Optionally, initialize the memory with starting addresses or enter `no` to skip.
7. The simulator executes the program instruction by instruction. Press `y` to execute the next instruction.
8. The simulation ends when an ECALL or EBREAK instruction is encountered, or upon any input error.

## Output

The simulator provides real-time updates of all register values and memory states after each instruction execution, enhancing understanding of the RISC-V architecture and instruction set.

## Contributing

Feel free to fork the repository and submit pull requests. You can also open issues for bugs or suggestions.

## Suggestions

GUI implementation, assembler integration, and support for pseudoinstructions, directives, and compressed instructions.


