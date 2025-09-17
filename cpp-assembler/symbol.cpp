#include "symbol.hpp"

namespace CppAssembler {

Symbol::Symbol(const std::string& name, SymbolType type, SymbolBinding binding)
    : m_name(name), m_type(type), m_binding(binding) {}

Symbol::~Symbol() {}

const std::string& Symbol::getName() const {
    return m_name;
}

} // namespace CppAssembler
