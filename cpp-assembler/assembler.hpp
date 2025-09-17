#pragma once

#include <string>
#include <vector>
#include <memory>

namespace CppAssembler {

class Assembler {
public:
    Assembler();
    ~Assembler();

    void addSourceFile(const std::string& filename);
    void setOutputFile(const std::string& filename);
    void assemble();

private:
    class AssemblerImpl;
    std::unique_ptr<AssemblerImpl> impl;
};

} // namespace CppAssembler
