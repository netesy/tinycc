#pragma once

#include <string>
#include <istream>
#include <memory>

namespace CppAssembler {

enum class TokenType {
    IDENTIFIER,
    NUMBER,
    SYMBOL,
    DIRECTIVE,
    STRING,
    END_OF_FILE,
    UNKNOWN
};

struct Token {
    TokenType type;
    std::string value;
    int line_num;
};

class Tokenizer {
public:
    Tokenizer(std::istream& input);
    ~Tokenizer();

    Token next();

private:
    class TokenizerImpl;
    std::unique_ptr<TokenizerImpl> impl;
};

} // namespace CppAssembler
