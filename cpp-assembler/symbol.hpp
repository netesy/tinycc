#pragma once

#include <string>

namespace CppAssembler {

enum class SymbolType {
    NOTYPE,
    OBJECT,
    FUNCTION,
    SECTION,
    FILE
};

enum class SymbolBinding {
    LOCAL,
    GLOBAL,
    WEAK
};

class Symbol {
public:
    Symbol(const std::string& name,
           SymbolType type = SymbolType::NOTYPE,
           SymbolBinding binding = SymbolBinding::LOCAL);
    ~Symbol();

    const std::string& getName() const;
    // ... other getters and setters will be added as needed ...

private:
    std::string m_name;
    SymbolType m_type;
    SymbolBinding m_binding;
    // ... other symbol properties will be added as needed ...
};

} // namespace CppAssembler
