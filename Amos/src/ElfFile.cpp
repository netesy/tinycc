#include "ElfFile.h"
#include <fstream>
#include <iostream>
#include <vector>

namespace Amos {

ElfFile::ElfFile(State* state) : m_state(state) {
}

ElfFile::~ElfFile() {
}

bool ElfFile::loadObjectFile(const std::string& filename) {
    std::ifstream file(filename, std::ios::binary | std::ios::ate);
    if (!file.is_open()) {
        std::cerr << "Cannot open file: " << filename << std::endl;
        return false;
    }

    std::streamsize size = file.tellg();
    file.seekg(0, std::ios::beg);

    std::vector<char> buffer(size);
    if (!file.read(buffer.data(), size)) {
        std::cerr << "Cannot read file: " << filename << std::endl;
        return false;
    }

    // TODO: Parse the ELF file
    std::cerr << "Amos::ElfFile::loadObjectFile is not fully implemented yet" << std::endl;

    return true;
}

bool ElfFile::writeElfFile(const std::string& /*filename*/) {
    // TODO: Implement this
    std::cerr << "Amos::ElfFile::writeElfFile is not implemented yet" << std::endl;
    return false;
}

} // namespace Amos
