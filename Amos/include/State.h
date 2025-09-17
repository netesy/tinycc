#ifndef AMOS_STATE_H
#define AMOS_STATE_H

#include <vector>
#include "Section.h"
#include "Symbol.h"

namespace Amos {

class State {
public:
    State();
    ~State();

    // Output type, see TCC_OUTPUT_XXX
    int output_type;
    // Output format, see TCC_OUTPUT_FORMAT_xxx
    int output_format;

    // Sections
    std::vector<Section*> sections;
    std::vector<Section*> priv_sections;

    // Predefined sections
    Section* text_section;
    Section* data_section;
    Section* rodata_section;
    Section* bss_section;
    Section* common_section;
    Section* symtab_section;
    Section* dynsymtab_section;
    Section* dynsym;
    Section* got;
    Section* plt;

    // Extra attributes (eg. GOT/PLT value) for symtab symbols
    std::vector<SymAttr> sym_attrs;
};

} // namespace Amos

#endif // AMOS_STATE_H
