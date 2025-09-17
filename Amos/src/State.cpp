#include "State.h"

namespace Amos {

State::State()
    : output_type(0), output_format(0),
      text_section(nullptr), data_section(nullptr), rodata_section(nullptr),
      bss_section(nullptr), common_section(nullptr), symtab_section(nullptr),
      dynsymtab_section(nullptr), dynsym(nullptr), got(nullptr), plt(nullptr) {
}

State::~State() {
    for (auto section : sections) {
        delete section;
    }
    for (auto section : priv_sections) {
        delete section;
    }
}

} // namespace Amos
