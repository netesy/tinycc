#include "assembler.hpp"
#include "tokenizer.hpp"
#include "symbol.hpp"

#include <vector>
#include <fstream>
#include <stdexcept>
#include <iostream>
#include <map>

namespace CppAssembler {

// A simplified, C++-native Section struct for the refactoring process.
struct Section {
    std::string name;
    std::vector<uint8_t> data;
    long data_offset = 0;

    Section(const std::string& n) : name(n) {}
};

class Assembler::AssemblerImpl {
public:
    AssemblerImpl() :
        m_asm_sec(nullptr),
        m_asm_new_section(0),
        m_cur_text_section(nullptr),
        m_ind(0),
        m_nocode_wanted(0)
    {
        m_text_section = new Section{".text"};
        m_data_section = new Section{".data"};
        m_bss_section = new Section{".bss"};
        m_cur_text_section = m_text_section;
    }

    ~AssemblerImpl() {
        delete m_text_section;
        delete m_data_section;
        delete m_bss_section;
    }

    void setSourceFile(const std::string& filename) {
        m_source_file = filename;
    }

    void setOutputFile(const std::string& filename) {
        m_output_file = filename;
    }

    void assemble() {
        std::ifstream input_file(m_source_file);
        if (!input_file) {
            throw std::runtime_error("Failed to open source file: " + m_source_file);
        }
        Tokenizer tokenizer(input_file);

        while (true) {
            Token token = tokenizer.next();
            if (token.type == TokenType::END_OF_FILE) {
                break;
            }

            if (token.type == TokenType::LABEL) {
                add_symbol(token.value, SymbolType::OBJECT, SymbolBinding::LOCAL);
            } else if (token.type == TokenType::DIRECTIVE) {
                parse_directive(token, tokenizer);
            } else if (token.type == TokenType::IDENTIFIER) {
                // This will be handled later (instructions and labels)
            } else if (token.type == TokenType::SYMBOL && token.value == "\n") {
                // Ignore newlines
            }
        }

        std::cout << "Finished parsing." << std::endl;
        std::cout << "Data section size: " << m_data_section->data.size() << std::endl;
        std::cout << "Symbol table:" << std::endl;
        for (const auto& pair : m_symbol_table) {
            std::cout << "  " << pair.second.getName() << std::endl;
        }
    }

private:
    void parse_directive(const Token& directive_token, Tokenizer& tokenizer) {
        if (directive_token.value == ".text") {
            use_section(m_text_section);
        } else if (directive_token.value == ".data") {
            use_section(m_data_section);
        } else if (directive_token.value == ".bss") {
            use_section(m_bss_section);
        } else if (directive_token.value == ".globl" || directive_token.value == ".global") {
            parse_globl(tokenizer);
        } else if (directive_token.value == ".string" || directive_token.value == ".asciz") {
            parse_string(tokenizer, true);
        } else if (directive_token.value == ".ascii") {
            parse_string(tokenizer, false);
        } else {
            // Ignoring directive
        }
    }

    void parse_globl(Tokenizer& tokenizer) {
        while (true) {
            Token token = tokenizer.next();
            if (token.type != TokenType::IDENTIFIER) {
                break;
            }
            add_symbol(token.value, SymbolType::NOTYPE, SymbolBinding::GLOBAL);

            token = tokenizer.next();
            if (token.type == TokenType::SYMBOL && token.value == ",") {
                continue;
            } else {
                break;
            }
        }
    }

    void parse_string(Tokenizer& tokenizer, bool null_terminated) {
        while (true) {
            Token token = tokenizer.next();
            if (token.type != TokenType::STRING) {
                throw std::runtime_error("Expected string literal after .string/.ascii/.asciz");
            }

            for (char c : token.value) {
                emit_byte(static_cast<uint8_t>(c));
            }
            if (null_terminated) {
                emit_byte(0);
            }

            token = tokenizer.next();
            if (token.type == TokenType::SYMBOL && token.value == ",") {
                continue;
            } else {
                break;
            }
        }
    }

    void use_section(Section* sec) {
        if (m_cur_text_section) {
            m_cur_text_section->data_offset = m_ind;
        }
        m_cur_text_section = sec;
        m_ind = m_cur_text_section->data_offset;
    }

    void add_symbol(const std::string& name, SymbolType type, SymbolBinding binding) {
        if (m_symbol_table.find(name) == m_symbol_table.end()) {
            m_symbol_table.emplace(name, Symbol(name, type, binding));
        }
    }

    void emit_byte(uint8_t byte) {
        m_cur_text_section->data.push_back(byte);
        m_ind++;
    }

    // Sections
    Section* m_text_section;
    Section* m_data_section;
    Section* m_bss_section;

    // Symbol table
    std::map<std::string, Symbol> m_symbol_table;

    // State from tccasm.c
    Section* m_asm_sec;
    int m_asm_new_section;
    std::vector<Section*> m_section_stack;

    // State from tcc_assemble
    Section* m_cur_text_section;
    int m_ind;
    int m_nocode_wanted;

    // Input/output files
    std::string m_source_file;
    std::string m_output_file;
};

Assembler::Assembler() : impl(new AssemblerImpl()) {}

Assembler::~Assembler() {}

void Assembler::addSourceFile(const std::string& filename) {
    impl->setSourceFile(filename);
}

void Assembler::setOutputFile(const std::string& filename) {
    impl->setOutputFile(filename);
}

void Assembler::assemble() {
    impl->assemble();
}

} // namespace CppAssembler
