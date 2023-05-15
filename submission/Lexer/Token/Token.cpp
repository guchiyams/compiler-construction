#ifndef TOKEN_CPP
#define TOKEN_CPP

#include <iostream>
#include <ostream>
#include <string>

using std::cout;
using std::ofstream;
using std::string;

// define token types
enum class TokenType {
    IDENTIFIER,
    KEYWORD,
    INTEGER,
    REAL,
    OPERATOR,
    SEPARATOR,
    END_INPUT
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
        cout <<     "current token: " << type_str << " ,      lexeme: " << lexeme << "\n";
    }

    void print_token_to_outfile (ofstream& output_file) {
        output_file <<     "current token: " << type_str << " ,      lexeme: " << lexeme << "\n";
    }
};

#endif // TOKEN_CPP