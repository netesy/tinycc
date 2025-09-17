#ifndef AMOS_LINKER_H
#define AMOS_LINKER_H

#include "State.h"
#include <string>
#include <vector>

namespace Amos {

class Linker {
public:
    Linker(State& state);
    ~Linker();

    bool run(int argc, char* argv[]);

private:
    void relocate_sections();
    State& m_state;
};

} // namespace Amos

#endif // AMOS_LINKER_H
