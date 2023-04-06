#ifndef LEXICAL_ANALYZER
#define LEXICAL_ANALYZER

#include <deque>
#include <fstream>
#include <iostream>
#include <stdexcept>
#include <string>
#include <unordered_map>
#include <vector>

using std::cout;
using std::deque;
using std::string;
using std::unordered_map;
using std::vector;

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

class Lexer
{
private:
    string input_file_name;
    string output_file_name;
    deque<Token> _tokens;
    static const unordered_map<char, int> CHAR_TO_COL;
    static const int TRANSITION_TABLE[128][128];
    
    void init();
public:
    Lexer() = default;
    Lexer(string& input_file_name, string& output_file_name);
    ~Lexer();
    void print_tokens();
    deque<Token> get_tokens();
    Token get_next_token();
};

#endif // LEXICAL_ANALYZER