#include <iostream>
#include <string>

using std::cout;
using std::string;

// define token types
enum class TokenType {
    IDENTIFIER,
    KEYWORD,
    INTEGER,
    REAL,
    OPERATOR,
    SEPARATOR,
};

// define struct to hold lexeme information
struct Token {
    TokenType type;
    string type_str;
    string lexeme;

    Token(TokenType type, string type_str, string lexeme ) {
        this->type = type;
        this->type_str = type_str;
        this->lexeme = lexeme;
    }

    void print_token() {
        cout <<     "token: " << type_str << " ,      lexeme: " << lexeme << "\n";
    }
};