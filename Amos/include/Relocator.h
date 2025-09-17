#ifndef AMOS_RELOCATOR_H
#define AMOS_RELOCATOR_H

#include "State.h"
#include "elf.h"

namespace Amos {

class Relocator {
public:
    Relocator(State& state);
    ~Relocator();

    void relocate(Section* section, const Elf64_Rela& rel);

private:
    State& m_state;
};

} // namespace Amos

#endif // AMOS_RELOCATOR_H
