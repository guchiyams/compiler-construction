#ifndef LEXER_CPP
#define LEXER_CPP

#include "./Lexer.h"

Lexer::Lexer(string& input_file_name)
{   
    this->line_count = 0;
    this->input_file_name = input_file_name;
    this->init();
}

void Lexer::init(){
    // open input and output files
    std::ifstream in_file("./input/" + this->input_file_name);
    // std::ofstream out_file("./output/" + this->output_file_name, std::ios::trunc);

    // check if input file and output file is successfully open
    if (in_file.is_open() /*&& out_file.is_open()*/) {
        // while not end of input file, retreive input line
        string input = "";
        while (std::getline(in_file, input)) {
            // set current state to initial state - 1
            int curr_state = 1;
            string lexeme = "";
            bool isEnd = false;

            // for each line, traverse character by character
            for (int i = 0; i < input.length(); i++) {
                // retrieve char and initialize next_state
                char c = input[i];
                int next_state = 0;
                
                // if not end of file, get column -> get next state
                if (isEnd == false) {
                    int col = this->CHAR_TO_COL.at(c);
                    next_state = TRANSITION_TABLE[curr_state][col];
                } 
                // if end of file, don't go to next state - stay on current state
                else {
                    next_state = curr_state;
                }

                // print to file for debugging:
                    // out_file << "CURRENT CHAR: \"" << c << "\"\n";
                    // out_file << "CURRENT STATE: " << curr_state << "\n";
                    // out_file << "NEXT STATE:    " << next_state << "\n\n";

                // if next_state is accepting state, write into output file
                switch (next_state) {
                    // check for error state 12 - throw exception
                    case 12:
                        throw std::invalid_argument("In invalid state - " + std::to_string(next_state) + " - coming from state: " + std::to_string(curr_state) + "\n");

                    // is an identifier
                    case 3:
                        // out_file <<     "token: IDENTIFIER,      lexeme: " << lexeme << "\n";
                        _tokens.push_back(Token(TokenType::IDENTIFIER, "IDENTIFIER", lexeme));
                        if (isEnd == true) continue;
                        curr_state = 1;
                        lexeme = "";
                        i--;
                        break;

                    // is a keyword
                    case 36:
                        // out_file <<     "token: KEYWORD   ,      lexeme: " << lexeme << "\n"; 
                        _tokens.push_back({TokenType::KEYWORD, "KEYWORD", lexeme});
                        if (isEnd == true) continue;
                        curr_state = 1;
                        lexeme = "";
                        i--;
                        break;

                    // is an integer
                    case 5:
                        // out_file <<     "token: INTEGER   ,      lexeme: " << lexeme << "\n"; 
                        _tokens.push_back({TokenType::INTEGER, "INTEGER", lexeme});
                        if (isEnd == true) continue;
                        curr_state = 1;
                        lexeme = "";
                        i--;
                        break;
                    
                    // is a real
                    case 7:
                        // out_file <<     "token: REAL      ,      lexeme: " << lexeme << "\n"; 
                        _tokens.push_back({TokenType::REAL, "REAL", lexeme});
                        if (isEnd == true) continue;
                        curr_state = 1;
                        lexeme = "";
                        i--;
                        break;

                    // is an operator
                    case 9:
                        // out_file <<     "token: OPERATOR  ,      lexeme: " << lexeme << "\n"; 
                        _tokens.push_back({TokenType::OPERATOR, "OPERATOR", lexeme});
                        if (isEnd == true) continue;
                        curr_state = 1;
                        lexeme = "";
                        i--;
                        break;

                    // is a separator
                    case 11:
                        // out_file <<     "token: SEPARATOR ,      lexeme: " << lexeme << "\n"; 
                        _tokens.push_back({TokenType::SEPARATOR, "SEPARATOR", lexeme});
                        if (isEnd == true) continue;
                        curr_state = 1;
                        lexeme = "";
                        i--;
                        break;
                    
                    // is a comment
                    case 51:
                        if (isEnd == true) continue;
                        curr_state = 1;
                        lexeme = "";
                        // i--;
                        break;

                    default:
                        // don't add white spaces to lexeme
                        if (c != ' ') {
                            lexeme += c;
                        }

                        // if end of file
                        //      -> set next state to current state's end of input state (column index 32)
                        //      -> set isEnd bool variable to true, then decrement iterator to run again
                        if (i == input.length() - 1) {
                            if (isEnd == true) {
                                continue;
                            } 
                            else {
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
            line_count++;
        }

        // push the end of input token
        _tokens.push_back(Token(TokenType::END_INPUT, "END_INPUT", "$"));
    }
    else {
        cout << "Files not open. Aborting..." << std::endl;
        exit(1);
    }

    // close opened files
    in_file.close();
    // out_file.close();
}

void Lexer::print_tokens() {
    for (auto token : _tokens) {
        token.print_token();
    }
}

deque<Token>& Lexer::get_tokens() {
    return this->_tokens;
}

Token Lexer::get_next_token() {
    Token next_token = this->_tokens.front();
    return next_token;
}

Token Lexer::get_next_token_and_pop() {
    Token next_token = this->_tokens.front();
    this->_tokens.pop_front();
    return next_token;
}

const int Lexer::get_line_count() {
    return line_count;
}


Token Lexer::pop_front() {
    Token next_token = this->_tokens.front();
    this->_tokens.pop_front();
    return next_token;
}


const unordered_map<char, int> Lexer::CHAR_TO_COL {
    // ALPHA [a-z]
    {'a',  0}, {'b',  1}, {'c',  2}, {'d',  3}, {'e',  4}, {'f',  5}, {'g',  6}, {'h',  7}, {'i',  8}, {'j',  9}, {'k', 10}, {'l', 11}, {'m', 12}, {'n', 13}, {'o', 14}, {'p', 15}, {'q', 16}, {'r', 17}, {'s', 18}, {'t', 19}, {'u', 20}, {'v', 21}, {'w', 22}, {'x', 23}, {'y', 24}, {'z', 25}, {'_', 26}, {'$', 33},
    // DIGITS [0-9]
    {'0', 27}, {'1', 27}, {'2', 27}, {'3', 27}, {'4', 27}, {'5', 27}, {'6', 27}, {'7', 27}, {'8', 27}, {'9', 27}, {'.', 28},
    // OPERATORS [<, >, =, /, -, +]
    {'<', 29}, {'>', 29}, {'=', 29}, {'/', 29}, {'-', 29}, {'+', 29}, {'*', 29}, {'^', 29},
    // SEPARATORS [(, ), {, }]
    {'(', 30}, {')', 30}, {'{', 30}, {'}' , 30}, {';', 30}, {':', 30}, {',', 30}, {'%', 30}, {'[', 30}, {']', 30},
    // COMMENT SEARATOR
    {'!', 34},
    // SPACE
    {' ', 31}, {'\n', 31},
};

// TRANSITION TABLE
const int Lexer::TRANSITION_TABLE[128][128] = {
//    a   b   c   d   e   f   g   h   i   j   k   l   m   n   o   p   q   r   s   t   u   v   w   x   y   z   _   D   .  OP  SP  ' ' endl $  !
    { 0,  1,  2,  3,  4,  5,  6,  7,  8,  9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 28, 29, 30, 31, 32, 33, 34 },      // STATE_00 -> PLACEHOLDER
    { 2, 52,  2,  2, 26, 19, 44,  2, 22,  2,  2,  2,  2,  2,  2, 47,  2, 30,  2,  2,  2,  2, 14,  2,  2,  2,  2,  4,  6,  8, 10,  1, 13, 12, 50 },      // STATE_01 -> STARTING STATE
    { 2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2, 12,  3,  3,  3,  3,  2, 50 },      // STATE_02 -> IN IDENTIFIER
    { 1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  8, 10,  1, 13,  1, 50 },      // STATE_03 -> END IDENTIFIER -> ACCEPTING STATE -> BACK UP
    {12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12,  4,  6,  5,  5,  5,  3, 12, 50 },      // STATE_04 -> IN INTEGER
    { 1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  8, 10,  1, 13,  1, 50 },      // STATE_05 -> END INTEGER -> ACCEPTING STATE -> BACK UP
    {12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12,  6, 12,  7,  7,  7,  7, 12, 50 },      // STATE_06 -> IN REAL
    { 1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  8, 10,  1, 13,  1, 50 },      // STATE_07 -> END REAL NUMBER -> ACCEPTING STATE -> BACK UP
    { 9,  9,  9,  9,  9,  9,  9,  9,  9,  9,  9,  9,  9,  9,  9,  9,  9,  9,  9,  9,  9,  9,  9,  9,  9,  9,  9,  9,  9,  8,  9,  9,  9,  9, 50 },      // STATE_08 -> FOUND operator
    { 1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  4,  1,  8, 10,  1, 13,  1, 50 },      // STATE_09 -> END operator
    {11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 50 },      // STATE_10 -> FOUND separator
    { 2,  2,  2,  2,  2, 20,  2,  2, 22,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2, 14,  2,  2,  2,  2,  4,  6,  8, 10,  1, 13, 12, 50 },      // STATE_11 -> END separator -> ACCEPTING STATE -> BACK UP
    { 1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1, 13,  1, 50 },      // STATE_12 -> INVALID STATE -> THROW EXCEPTION -> LOG ERROR
    { 1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1, 13,  1, 50 },      // STATE_13 -> END OF INPUT -> ACCEPTING STATE -> BREAK LOOP
    { 2,  2,  2,  2,  2,  2,  2, 15,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2, 12,  3,  3,  3,  3,  2, 50 },      // STATE_14 -> IN while_w KEYWORD
    { 2,  2,  2,  2,  2,  2,  2,  2, 16,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2, 12,  3,  3,  3,  3,  2, 50 },      // STATE_15 ->      IN while_h KEYWORD
    { 2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2, 17,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2, 12,  3,  3,  3,  3,  2, 50 },      // STATE_16 ->      IN while_i KEYWORD
    { 2,  2,  2,  2, 18,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2, 12,  3,  3,  3,  3,  2, 50 },      // STATE_17 ->      IN while_l KEYWORD
    { 2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2, 12, 12, 36, 36,  3,  2, 50 },      // STATE_18 ->      IN while_e KEYWORD
    { 2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2, 20,  2,  2,  2,  2,  2, 37,  2,  2,  2,  2,  2,  2,  2, 12,  3,  3,  3,  3,  2, 50 },      // STATE_19 -> IN f_ KEYWORD
    { 2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2, 21,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2, 12,  3,  3,  3,  3,  2, 50 },      // STATE_20 ->      IN for_o KEYWORD
    { 2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2, 12, 12, 36, 36,  3,  2, 50 },      // STATE_21 ->      IN for_r KEYWORD
    { 2,  2,  2,  2,  2, 23,  2,  2,  2,  2,  2,  2,  2, 24,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2, 12,  3,  3,  3,  3,  2, 50 },      // STATE_22 -> IN i_ KEYWORD
    { 2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2, 12, 12, 36, 36, 36,  2, 50 },      // STATE_23 ->      IN if_f KEYWORD
    { 2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2, 25,  2,  2,  2,  2,  2,  2,  2,  2, 12,  3,  3,  3,  3,  2, 50 },      // STATE_24 ->      IN int_n KEYWORD
    { 2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2, 12, 12, 36, 36,  3,  2, 50 },      // STATE_25 ->      IN int_t KEYWORD
    { 2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2, 27,  2, 59,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2, 12,  3,  3,  3,  3,  2, 50 },      // STATE_26 -> IN e_ KEYWORD
    { 2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2, 28,  2,  2,  2,  2,  2,  2,  2,  2,  2, 12,  3,  3,  3,  3,  2, 50 },      // STATE_27 ->      IN else_l
    { 2,  2,  2,  2, 29,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2, 12,  3,  3,  3,  3,  2, 50 },      // STATE_28 ->      IN else_s KEYWORD
    { 2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2, 12, 12, 36, 36, 36,  2, 50 },      // STATE_29 ->      IN else_e KEYWORD
    { 2,  2,  2,  2, 31,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2, 12,  3,  3,  3,  3,  2, 50 },      // STATE_30 -> IN return_r KEYWORD
    {61,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2, 32,  2,  2,  2,  2,  2,  2,  2,  2, 12,  3,  3,  3,  3,  2, 50 },      // STATE_31 ->      IN return_e KEYWORD
    { 2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2, 33,  2,  2,  2,  2,  2,  2,  2, 12,  3,  3,  3,  3,  2, 50 },      // STATE_32 ->      IN return_t KEYWORD
    { 2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2, 34,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2, 12,  3,  3,  3,  3,  2, 50 },      // STATE_33 ->      IN return_u KEYWORD
    { 2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2, 35,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2, 12,  3,  3,  3,  3,  2, 50 },      // STATE_34 ->      IN return_r KEYWORD
    { 2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2, 12, 12, 36, 36,  3,  2, 50 },      // STATE_35 ->      IN return_n KEYWORD
    { 1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  8, 10,  1, 13,  1, 50 },      // STATE_36 -> END KEYWORD
    { 2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2, 38,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2, 12,  3,  3,  3,  3,  2, 50 },      // STATE_37 ->      IN function_u KEYWORD
    { 2,  2, 39,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2, 12,  3,  3,  3,  3,  2, 50 },      // STATE_38 ->      IN function_n KEYWORD
    { 2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2, 40,  2,  2,  2,  2,  2,  2,  2,  2, 12,  3,  3,  3,  3,  2, 50 },      // STATE_39 ->      IN function_c KEYWORD
    { 2,  2,  2,  2,  2,  2,  2,  2, 41,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2, 12,  3,  3,  3,  3,  2, 50 },      // STATE_40 ->      IN function_t KEYWORD
    { 2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2, 42,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2, 12,  3,  3,  3,  3,  2, 50 },      // STATE_41 ->      IN function_i KEYWORD
    { 2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2, 43,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2, 12,  3,  3,  3,  3,  2, 50 },      // STATE_42 ->      IN function_o KEYWORD
    { 2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2, 12, 12, 36, 36,  3,  2, 50 },      // STATE_43 ->      IN function_n KEYWORD
    { 2,  2,  2,  2, 45,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2, 37,  2,  2,  2,  2,  2,  2,  2, 12,  3,  3,  3,  3,  2, 50 },      // STATE_44 -> IN g_ KEYWORD
    { 2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2, 46,  2,  2,  2,  2,  2,  2,  2,  2, 12,  3,  3,  3,  3,  2, 50 },      // STATE_45 ->      IN get_e KEYWORD
    { 2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2, 12, 12, 36, 36,  3,  2, 50 },      // STATE_46 ->      IN get_t KEYWORD
    { 2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2, 48,  2,  2,  2,  2,  2,  2,  2, 12,  3,  3,  3,  3,  2, 50 },      // STATE_47 -> IN p_ KEYWORD
    { 2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2, 49,  2,  2,  2,  2,  2,  2,  2,  2, 12,  3,  3,  3,  3,  2, 50 },      // STATE_48 ->      IN put_u KEYWORD
    { 2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2, 12, 12, 36, 36,  3,  2, 50 },      // STATE_49 ->      IN put_t KEYWORD
    {50, 50, 50, 50, 50, 50, 50, 50, 50, 50, 50, 50, 50, 50, 50, 50, 50, 50, 50, 50, 50, 50, 50, 50, 50, 50, 50, 50, 50, 50, 50, 50, 50, 50, 51 },      // STATE_50 -> IN COMMENT
    { 1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1, 50 },      // STATE_51 -> END COMMENT -> ACCEPTING STATE
    { 2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2, 53,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2, 12,  3,  3,  3,  3,  2, 50 },      // STATE_52 -> IN b_ KEYWORD
    { 2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2, 54,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2, 12,  3,  3,  3,  3,  2, 50 },      // STATE_53 ->      IN boolean_o KEYWORD
    { 2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2, 55,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2, 12,  3,  3,  3,  3,  2, 50 },      // STATE_54 ->      IN boolean_o KEYWORD
    { 2,  2,  2,  2, 56,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2, 12,  3,  3,  3,  3,  2, 50 },      // STATE_55 ->      IN boolean_l KEYWORD
    {57,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2, 12,  3,  3,  3,  3,  2, 50 },      // STATE_56 ->      IN boolean_e KEYWORD
    { 2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2, 58,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2, 12,  3,  3,  3,  3,  2, 50 },      // STATE_57 ->      IN boolean_a KEYWORD
    { 2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2, 12, 12, 36, 36,  3,  2, 50 },      // STATE_58 ->      IN boolean_n KEYWORD
    { 2,  2,  2, 60,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2, 12,  3,  3,  3,  3,  2, 50 },      // STATE_59 -> IN endif_n
    { 2,  2,  2,  2,  2,  2,  2,  2, 22,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2, 12, 12, 36, 36,  3,  2, 50 },      // STATE_60 ->      IN endif_d KEYWORD
    { 2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2, 62,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2, 12,  3,  3,  3,  3,  2, 50 },      // STATE_61 -> IN real_a KEYWORD
    { 2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2, 12, 12, 36, 36,  3,  2, 50 },      // STATE_62 ->      IN real_l KEYWORD
};

#endif // LEXER_CPP