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

// CHAR TO COLUMN - map char to column number
unordered_map<char, int> CHAR_TO_COL {
    // ALPHA [a-z]
    {'a',  0}, {'b',  1}, {'c',  2}, {'d',  3}, {'e',  4}, {'f',  5}, {'g',  6}, {'h',  7}, {'i',  8}, {'j',  9}, {'k', 10}, {'l', 11}, {'m', 12}, {'n', 13}, {'o', 14}, {'p', 15}, {'q', 16}, {'r', 17}, {'s', 18}, {'t', 19}, {'u', 20}, {'v', 21}, {'w', 22}, {'x', 23}, {'y', 24}, {'z', 25}, {'_', 26},
    // DIGITS [0-9]
    {'0', 27}, {'1', 27}, {'2', 27}, {'3', 27}, {'4', 27}, {'5', 27}, {'6', 27}, {'7', 27}, {'8', 27}, {'9', 27}, {'.', 28},
    // OPERATORS [<, >, =, /, -, +]
    {'<', 29}, {'>', 29}, {'=', 29}, {'/', 29}, {'-', 29}, {'+', 29}, {'%', 29},
    // SEPARATORS [(, ), {, }]
    {'(', 30}, {')', 30}, {'{', 30}, {'}' , 30}, {';', 30},
    // SPACE
    {' ', 31}
};

// TRANSITION TABLE
const int TRANSITION_TABLE[128][128] = {
//    a   b   c   d   e   f   g   h   i   j   k   l   m   n   o   p   q   r   s   t   u   v   w   x   y   z   _   D   .  OP  SP  ' ' endl
    { 0,  1,  2,  3,  4,  5,  6,  7,  8,  9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 28, 29, 30, 31, 32 },      // STATE_00 -> PLACEHOLDER
    { 2,  2,  2,  2, 26, 19,  2,  2, 22,  2,  2,  2,  2,  2,  2,  2,  2, 30,  2,  2,  2,  2, 14,  2,  2,  2,  2,  4,  6,  8, 10,  1, 13 },      // STATE_01 -> STARTING STATE
    { 2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2, 12,  3,  3,  3,  2 },      // STATE_02 -> IN IDENTIFIER
    { 1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  8, 10,  1, 13 },      // STATE_03 -> END IDENTIFIER -> ACCEPTING STATE -> BACK UP
    {12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12,  4,  6,  5,  5,  5,  3 },      // STATE_04 -> IN INTEGER
    { 1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  8, 10,  1, 13 },      // STATE_05 -> END INTEGER -> ACCEPTING STATE -> BACK UP
    {12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12,  6, 12,  7,  7,  7,  7 },      // STATE_06 -> IN REAL
    { 1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  8, 10,  1, 13 },      // STATE_07 -> END REAL NUMBER -> ACCEPTING STATE -> BACK UP
    { 9,  9,  9,  9,  9,  9,  9,  9,  9,  9,  9,  9,  9,  9,  9,  9,  9,  9,  9,  9,  9,  9,  9,  9,  9,  9,  9,  9,  9,  9,  9,  9,  9 },      // STATE_08 -> FOUND operator
    { 1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  4,  1,  8, 10,  1, 13 },      // STATE_09 -> END operator
    {11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11 },      // STATE_10 -> FOUND separator
    { 2,  2,  2,  2,  2, 20,  2,  2, 22,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2, 14,  2,  2,  2,  2,  4,  6,  8, 10,  1, 13 },      // STATE_11 -> END separator -> ACCEPTING STATE -> BACK UP
    { 1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1, 13 },      // STATE_12 -> INVALID STATE -> THROW EXCEPTION -> LOG ERROR
    { 1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1, 13 },      // STATE_13 -> END OF INPUT -> ACCEPTING STATE -> BREAK LOOP
    { 2,  2,  2,  2,  2,  2,  2, 15,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2, 12,  3,  3,  3,  3 },      // STATE_14 -> IN while_w KEYWORD
    { 2,  2,  2,  2,  2,  2,  2,  2, 16,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2, 12,  3,  3,  3,  3 },      // STATE_15 ->      IN while_h KEYWORD
    { 2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2, 17,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2, 12,  3,  3,  3,  3 },      // STATE_16 ->      IN while_i KEYWORD
    { 2,  2,  2,  2, 18,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2, 12,  3,  3,  3,  3 },      // STATE_17 ->      IN while_l KEYWORD
    { 2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2, 12, 12, 36, 36,  3 },      // STATE_18 ->      IN while_e KEYWORD
    { 2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2, 20,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2, 12,  3,  3,  3,  3 },      // STATE_19 -> IN for_f KEYWORD
    { 2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2, 21,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2, 12,  3,  3,  3,  3 },      // STATE_20 ->      IN for_o KEYWORD
    { 2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2, 12, 12, 36, 36,  3 },      // STATE_21 ->      IN for_r KEYWORD
    { 2,  2,  2,  2,  2, 23,  2,  2,  2,  2,  2,  2,  2, 24,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2, 12,  3,  3,  3,  3 },      // STATE_22 -> IN i_ KEYWORD
    { 2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2, 12, 12, 36, 36,  3 },      // STATE_23 ->      IN if_f KEYWORD
    { 2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2, 25,  2,  2,  2,  2,  2,  2,  2,  2, 12,  3,  3,  3,  3 },      // STATE_24 ->      IN int_n KEYWORD
    { 2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2, 12, 12, 36, 36,  3 },      // STATE_25 ->      IN int_t KEYWORD
    { 2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2, 27,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2, 12,  3,  3,  3,  3 },      // STATE_26 -> IN else_e KEYWORD
    { 2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2, 28,  2,  2,  2,  2,  2,  2,  2,  2,  2, 12,  3,  3,  3,  3 },      // STATE_27 ->      IN else_l
    { 2,  2,  2,  2, 29,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2, 12,  3,  3,  3,  3 },      // STATE_28 ->      IN else_s KEYWORD
    { 2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2, 12, 12, 36, 36,  3 },      // STATE_29 ->      IN else_e KEYWORD
    { 2,  2,  2,  2, 31,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2, 12,  3,  3,  3,  3 },      // STATE_30 -> IN return_r KEYWORD
    { 2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2, 32,  2,  2,  2,  2,  2,  2,  2,  2, 12,  3,  3,  3,  3 },      // STATE_31 ->      IN return_e KEYWORD
    { 2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2, 33,  2,  2,  2,  2,  2,  2,  2, 12,  3,  3,  3,  3 },      // STATE_32 ->      IN return_t KEYWORD
    { 2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2, 34,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2, 12,  3,  3,  3,  3 },      // STATE_33 ->      IN return_u KEYWORD
    { 2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2, 35,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2, 12,  3,  3,  3,  3 },      // STATE_34 ->      IN return_r KEYWORD
    { 2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2, 12, 12, 36, 36,  3 },      // STATE_35 ->      IN return_n KEYWORD
    { 1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  8, 10,  1, 13 },      // STATE_36 -> END KEYWORD
};

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

vector<Token> lexicalAnalyzer(const string& input_file_name, const string& output_file_name) {

    // open input and output files
    std::ifstream in_file("./input/" + input_file_name);
    std::ofstream out_file("./output/" + output_file_name, std::ios::trunc);

    // initialize vector of tokens
    vector<Token> tokens;

    // check if input file and output file is successfully open
    if (in_file.is_open() && out_file.is_open()) {
        // while not end of input file, retreive input line
        string input = "";
        while (std::getline(in_file, input)) {
            vector<Token> tokens;
            int curr_state = 1;
            string lexeme = "";
            bool isEnd = false;

            // for each line, traverse character by character
            for (int i = 0; i < input.length(); i++) {
                char c = input[i];
                int next_state = 0;

                if (isEnd == false) {
                    // get column -> get next state
                    int col = CHAR_TO_COL[c];
                    next_state = TRANSITION_TABLE[curr_state][col];
                } else {
                    // don't go to next state - stay on current state
                    next_state = curr_state;
                }

                // print to file for debugging:
                    // out_file << "CURRENT CHAR: \"" << c << "\"\n";
                    // out_file << "CURRENT STATE: " << curr_state << "\n";
                    // out_file << "NEXT STATE:    " << next_state << "\n\n";
                
                // check for error state 12
                if (next_state == 12) {
                    // throw type error exception
                    throw std::invalid_argument("In invalid state - " + std::to_string(next_state) + " - coming from state: " + std::to_string(curr_state) + "\n");
                }

                // if next_state is accepting state, write into output file
                switch (next_state) {
                    // is an identifier
                    case 3:
                        if (isEnd == true) {
                            out_file << "token: IDENTIFIER,      lexeme: " << lexeme << "\n"; 
                            tokens.push_back({TokenType::IDENTIFIER, lexeme});
                            continue;
                        }
                        out_file <<     "token: IDENTIFIER,      lexeme: " << lexeme << "\n"; 
                        tokens.push_back({TokenType::IDENTIFIER, lexeme});
                        curr_state = 1;
                        lexeme = "";
                        i--;
                        break;

                    // is a keyword
                    case 36:
                        if (isEnd == true) {
                            out_file << "token: KEYWORD   ,      lexeme: " << lexeme << "\n"; 
                            tokens.push_back({TokenType::KEYWORD, lexeme});
                            continue;
                        }
                        out_file <<     "token: KEYWORD   ,      lexeme: " << lexeme << "\n"; 
                        tokens.push_back({TokenType::KEYWORD, lexeme});
                        curr_state = 1;
                        lexeme = "";
                        i--;
                        break;

                    // is an integer
                    case 5:
                        if (isEnd == true) {
                            out_file << "token: INTEGER   ,      lexeme: " << lexeme << "\n"; 
                            tokens.push_back({TokenType::INTEGER, lexeme});
                            continue;
                        }
                        out_file <<     "token: INTEGER   ,      lexeme: " << lexeme << "\n"; 
                        tokens.push_back({TokenType::INTEGER, lexeme});
                        curr_state = 1;
                        lexeme = "";
                        i--;
                        break;
                    
                    // is a real
                    case 7:
                        if (isEnd == true) {
                            out_file << "token: REAL      ,      lexeme: " << lexeme << "\n"; 
                            tokens.push_back({TokenType::REAL, lexeme});
                            continue;
                        }
                        out_file <<     "token: REAL      ,      lexeme: " << lexeme << "\n"; 
                        tokens.push_back({TokenType::REAL, lexeme});
                        curr_state = 1;
                        lexeme = "";
                        i--;
                        break;

                    // is an operator
                    case 9:
                        if (isEnd == true) {
                            out_file << "token: OPERATOR  ,      lexeme: " << lexeme << "\n"; 
                            tokens.push_back({TokenType::OPERATOR, lexeme});
                            continue;
                        }
                        out_file <<     "token: OPERATOR  ,      lexeme: " << lexeme << "\n"; 
                        tokens.push_back({TokenType::OPERATOR, lexeme});
                        curr_state = 1;
                        lexeme = "";
                        i--;
                        break;

                    // is a separator
                    case 11:
                        if (isEnd == true) {
                            out_file << "token: SEPARATOR ,      lexeme: " << lexeme << "\n"; 
                            tokens.push_back({TokenType::SEPARATOR, lexeme});
                            continue;
                        }
                        out_file <<     "token: SEPARATOR ,      lexeme: " << lexeme << "\n"; 
                        tokens.push_back({TokenType::SEPARATOR, lexeme});
                        curr_state = 1;
                        lexeme = "";
                        i--;
                        break;

                    default:
                        if (c != ' ') {
                            lexeme += c;
                        }
                        if (i == input.length() - 1) {
                            if (isEnd == true) {
                                continue;
                            } else {
                                // last token:
                                //      1. set next state to current state's end of input state (column index 32)
                                //      2. set isEnd bool variable to true, then decrement iteragot to run again

                                curr_state = TRANSITION_TABLE[next_state][32];
                                isEnd = true;
                                i--;

                                continue;
                            }

                        }
                }
                // go to next state
                curr_state = next_state;
            }
        }
    } else {
        cout << "Files not open. Aborting..." << std::endl;
        abort();
    }

    // close opened files
    in_file.close();
    out_file.close();

    return tokens;
}

#endif // LEXICAL_ANALYZER