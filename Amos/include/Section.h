#ifndef AMOS_SECTION_H
#define AMOS_SECTION_H

#include <string>
#include <vector>
#include <cstdint>
#include "Symbol.h"

namespace Amos {

class State; // Forward declaration

class Section {
public:
    Section(State* state, const std::string& name, int sh_type, int sh_flags);
    ~Section();

    std::string name;
    std::vector<uint8_t> data;
    uint64_t data_offset;
    uint64_t data_allocated;
    std::vector<Symbol*> symbols;

    State* state;
    int sh_name;
    int sh_num;
    int sh_type;
    int sh_flags;
    int sh_info;
    int sh_addralign;
    int sh_entsize;
    uint64_t sh_size;
    uint64_t sh_addr;
    uint64_t sh_offset;

    Section* link;
    Section* reloc;
    Section* hash;
};

} // namespace Amos

#endif // AMOS_SECTION_H
