#include "Symbol.h"

namespace Amos {

Symbol::Symbol(const std::string& name, uint64_t value, uint64_t size,
               unsigned char info, unsigned char other, uint16_t shndx)
    : name(name), value(value), size(size), info(info), other(other), shndx(shndx), index(0) {
}

Symbol::~Symbol() {
}

} // namespace Amos
