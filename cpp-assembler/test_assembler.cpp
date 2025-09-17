#include "assembler.hpp"
#include <iostream>

int main() {
    try {
        CppAssembler::Assembler assembler;
        assembler.addSourceFile("test_globl.s");
        assembler.assemble();
        std::cout << "Test passed: Assembler ran without errors." << std::endl;
    } catch (const std::exception& e) {
        std::cerr << "Test failed: " << e.what() << std::endl;
        return 1;
    }
    return 0;
}
