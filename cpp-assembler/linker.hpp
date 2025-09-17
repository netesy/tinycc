#pragma once

#include <string>
#include <vector>
#include <memory>

namespace CppAssembler {

class Linker {
public:
    Linker();
    ~Linker();

    void addObjectFile(const std::string& filename);
    void setOutputFile(const std::string& filename);
    void link();

private:
    class LinkerImpl;
    std::unique_ptr<LinkerImpl> impl;
};

} // namespace CppAssembler
