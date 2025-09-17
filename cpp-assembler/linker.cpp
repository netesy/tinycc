#include "linker.hpp"
#include <vector>
#include <string>
#include <memory>

namespace CppAssembler {

class Linker::LinkerImpl {
public:
    LinkerImpl() {}
    ~LinkerImpl() {}

    void addObjectFile(const std::string& filename) {
        m_object_files.push_back(filename);
    }

    void setOutputFile(const std::string& filename) {
        m_output_file = filename;
    }

    void link() {
        // This will be implemented later.
    }

private:
    std::vector<std::string> m_object_files;
    std::string m_output_file;
};

Linker::Linker() : impl(new LinkerImpl()) {}
Linker::~Linker() {}
void Linker::addObjectFile(const std::string& filename) { impl->addObjectFile(filename); }
void Linker::setOutputFile(const std::string& filename) { impl->setOutputFile(filename); }
void Linker::link() { impl->link(); }

} // namespace CppAssembler
