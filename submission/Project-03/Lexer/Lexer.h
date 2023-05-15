#ifndef LEXER_H
#define LEXER_H

#include <deque>
#include <fstream>
#include <stdexcept>
#include <unordered_map>
#include <vector>

#include "./Token/Token.cpp"

using std::deque;
using std::unordered_map;
using std::vector;

class Lexer {
    public:
        Lexer() = default;
        Lexer(string& input_file_name);
        ~Lexer() = default;
        
        // print all tokens in order
        void print_tokens();

        // getters
        deque<Token>& get_tokens();
        Token get_next_token();
        Token get_next_token_and_pop();
        const int get_line_count();

        // modifiers
        Token pop_front();

    private:
        int line_count;
        string input_file_name;
        deque<Token> _tokens;
        static const unordered_map<char, int> CHAR_TO_COL;
        static const int TRANSITION_TABLE[128][128];
        
        // runs lexical analysis
        void init();
};

#endif // LEXER_H