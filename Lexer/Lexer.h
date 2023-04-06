#ifndef LEXICAL_ANALYZER
#define LEXICAL_ANALYZER

#include <deque>
#include <fstream>
#include <stdexcept>
#include <unordered_map>
#include <vector>

#include "./Token/Token.cpp"

using std::deque;
using std::unordered_map;
using std::vector;

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