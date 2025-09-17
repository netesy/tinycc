#include "assembler.hpp"
#include <iostream>

int main() {
    try {
        CppAssembler::Assembler assembler;
        assembler.addSourceFile("test_string.s");
        assembler.assemble();
    } catch (const std::exception& e) {
        std::cerr << "Test failed: " << e.what() << std::endl;
        return 1;
    }
    return 0;
}
