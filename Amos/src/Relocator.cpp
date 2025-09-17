#include "Relocator.h"
#include <iostream>

namespace Amos {

Relocator::Relocator(State& state) : m_state(state) {
}

Relocator::~Relocator() {
}

void Relocator::relocate(Section* section, const Elf64_Rela& rel) {
    uint8_t* ptr = section->data.data() + rel.r_offset;
    uint64_t addr = section->sh_addr + rel.r_offset;

    int type = ELF64_R_TYPE(rel.r_info);
    int sym_index = ELF64_R_SYM(rel.r_info);

    Symbol* sym = m_state.symtab_section->symbols[sym_index];
    uint64_t val = sym->value + rel.r_addend;

    switch (type) {
        case R_X86_64_NONE:
            break;
        case R_X86_64_64:
            *(uint64_t*)ptr = val;
            break;
        case R_X86_64_PC32:
            *(uint32_t*)ptr = val - addr;
            break;
        case R_X86_64_32:
        case R_X86_64_32S:
            *(uint32_t*)ptr = val;
            break;
        default:
            std::cerr << "Unsupported relocation type: " << type << std::endl;
            break;
    }
}

} // namespace Amos
