#include "Linker.h"
#include "ElfFile.h"
#include "Relocator.h"
#include <iostream>

namespace Amos {

Linker::Linker(State& state) : m_state(state) {
}

Linker::~Linker() {
}

void Linker::relocate_sections() {
    Relocator relocator(m_state);
    for (auto section : m_state.sections) {
        if (section->reloc) {
            Section* reloc_section = section->reloc;
            for (size_t i = 0; i < reloc_section->data.size() / sizeof(Elf64_Rela); ++i) {
                Elf64_Rela* rel = (Elf64_Rela*)reloc_section->data.data() + i;
                relocator.relocate(section, *rel);
            }
        }
    }
}

bool Linker::run(int argc, char* argv[]) {
    if (argc < 3) {
        std::cerr << "Usage: " << argv[0] << " -o <output_file> <input_files...>" << std::endl;
        return false;
    }

    std::string output_file;
    std::vector<std::string> input_files;

    for (int i = 1; i < argc; ++i) {
        std::string arg = argv[i];
        if (arg == "-o") {
            if (i + 1 < argc) {
                output_file = argv[++i];
            } else {
                std::cerr << "Missing argument for -o" << std::endl;
                return false;
            }
        } else {
            input_files.push_back(arg);
        }
    }

    if (output_file.empty()) {
        std::cerr << "Output file not specified" << std::endl;
        return false;
    }

    if (input_files.empty()) {
        std::cerr << "No input files specified" << std::endl;
        return false;
    }

    ElfFile elf_file(&m_state);

    for (const auto& input_file : input_files) {
        if (!elf_file.loadObjectFile(input_file)) {
            std::cerr << "Failed to load object file: " << input_file << std::endl;
            return false;
        }
    }

    // TODO: Resolve symbols

    relocate_sections();

    if (!elf_file.writeElfFile(output_file)) {
        std::cerr << "Failed to write output file: " << output_file << std::endl;
        return false;
    }

    return true;
}

} // namespace Amos
