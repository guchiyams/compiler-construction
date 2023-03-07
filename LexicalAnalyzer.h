#ifndef LEXICAL_ANALYZER
#define LEXICAL_ANALYZER

#include <fstream>
#include <iostream>
#include <stdexcept>
#include <string>
#include <unordered_map>
#include <vector>

using std::cout;
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
    SEPARATOR
};

// define struct to hold lexeme information
struct Token {
    TokenType type;
    string lexeme;
};


class Lexer
{
private:
    string input_file_name;
    string output_file_name;
    static const unordered_map<char, int> CHAR_TO_COL;
    static const int TRANSITION_TABLE[128][128];
public:
    Lexer(string& input_file_name, string& output_file_name );
    ~Lexer();
    vector<Token> parser();

};

#endif // LEXICAL_ANALYZER