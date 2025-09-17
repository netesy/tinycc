#ifndef AMOS_SYMBOL_H
#define AMOS_SYMBOL_H

#include <string>
#include <cstdint>

namespace Amos {

class Symbol {
public:
    Symbol(const std::string& name, uint64_t value, uint64_t size,
           unsigned char info, unsigned char other, uint16_t shndx);
    ~Symbol();

    std::string name;
    uint64_t value;
    uint64_t size;
    unsigned char info;
    unsigned char other;
    uint16_t shndx;

    // For linker internal use
    int index;
};

// struct sym_attr from tcc.h
struct SymAttr {
    unsigned got_offset;
    unsigned plt_offset;
    int plt_sym;
    int dyn_index;
};

} // namespace Amos

#endif // AMOS_SYMBOL_H
