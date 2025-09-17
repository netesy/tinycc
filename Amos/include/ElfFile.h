#ifndef AMOS_ELFFILE_H
#define AMOS_ELFFILE_H

#include <string>
#include <vector>
#include "elf.h"
#include "State.h"

namespace Amos {

class ElfFile {
public:
    ElfFile(State* state);
    ~ElfFile();

    bool loadObjectFile(const std::string& filename);
    bool writeElfFile(const std::string& filename);

private:
    State* m_state;
};

} // namespace Amos

#endif // AMOS_ELFFILE_H
