#include "tokenizer.hpp"
#include <cctype>
#include <stdexcept>

namespace CppAssembler {

class Tokenizer::TokenizerImpl {
public:
    TokenizerImpl(std::istream& input) : input(input), line_num(1) {}

    Token next() {
        int c;
        // Skip whitespace and comments
        while ((c = input.peek()), input.good()) {
            if (c == '\n') {
                input.get();
                line_num++;
                return {TokenType::SYMBOL, "\n", line_num - 1};
            }
            if (c == '#') {
                // Comment, skip to end of line
                while ((c = input.peek()), input.good() && c != '\n') {
                    input.get();
                }
                continue;
            }
            if (std::isspace(c)) {
                input.get();
                continue;
            }
            break; // Not whitespace or comment, break to process token
        }

        if (!input.good()) {
            return {TokenType::END_OF_FILE, "", line_num};
        }

        c = input.peek();

        if (std::isalpha(c) || c == '_') {
            Token token = read_identifier();
            if (input.peek() == ':') {
                input.get(); // consume the ':'
                token.type = TokenType::LABEL;
            }
            return token;
        }

        if (std::isdigit(c)) {
            return read_number();
        }

        if (c == '.') {
            return read_directive();
        }

        if (c == '"') {
            return read_string();
        }

        // Single character symbols
        input.get();
        return {TokenType::SYMBOL, std::string(1, c), line_num};
    }

private:
    Token read_identifier() {
        std::string value;
        while (input.good() && (std::isalnum(input.peek()) || input.peek() == '_')) {
            value += input.get();
        }
        return {TokenType::IDENTIFIER, value, line_num};
    }

    Token read_number() {
        std::string value;
        while (input.good() && std::isdigit(input.peek())) {
            value += input.get();
        }
        return {TokenType::NUMBER, value, line_num};
    }

    Token read_directive() {
        std::string value;
        while (input.good() && (std::isalnum(input.peek()) || input.peek() == '.')) {
            value += input.get();
        }
        return {TokenType::DIRECTIVE, value, line_num};
    }

    Token read_string() {
        std::string value;
        input.get(); // consume the opening '"'
        bool in_escape = false;
        while (input.good()) {
            char c = input.get();
            if (in_escape) {
                value += c;
                in_escape = false;
            } else if (c == '\\') {
                in_escape = true;
            } else if (c == '"') {
                break;
            } else {
                value += c;
            }
        }
        return {TokenType::STRING, value, line_num};
    }

    std::istream& input;
    int line_num;
};

Tokenizer::Tokenizer(std::istream& input) : impl(new TokenizerImpl(input)) {}

Tokenizer::~Tokenizer() {}

Token Tokenizer::next() {
    return impl->next();
}

} // namespace CppAssembler
