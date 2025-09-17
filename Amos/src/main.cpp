#include <iostream>
#include "State.h"
#include "Linker.h"

int main(int argc, char* argv[]) {
    Amos::State state;
    Amos::Linker linker(state);

    if (!linker.run(argc, argv)) {
        return 1;
    }

    return 0;
}
