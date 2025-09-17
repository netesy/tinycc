#include "Section.h"
#include "State.h"

namespace Amos {

Section::Section(State* state, const std::string& name, int sh_type, int sh_flags)
    : name(name),
      data(),
      data_offset(0),
      data_allocated(0),
      symbols(),
      state(state),
      sh_name(0),
      sh_num(0),
      sh_type(sh_type),
      sh_flags(sh_flags),
      sh_info(0),
      sh_addralign(0),
      sh_entsize(0),
      sh_size(0),
      sh_addr(0),
      sh_offset(0),
      link(nullptr),
      reloc(nullptr),
      hash(nullptr) {
}

Section::~Section() {
    for (auto symbol : symbols) {
        delete symbol;
    }
}

} // namespace Amos
