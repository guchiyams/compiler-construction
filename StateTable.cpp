#ifndef STATETABLE
#define STATETABLE

#include <iostream>
#include <stdexcept>
#include <string>
#include <unordered_map>
#include <vector>

using std::cout;
using std::string;
using std::unordered_map;
using std::vector;

// STATE INDICES:
//      1  = STARTING STATE
//      2  = IN IDENTIFIER
//      3  = END IDENTIFIER - ACCEPTING STATE -> BACK UP
//      4  = IN WHILE KEYWORD
//      5  = IN WHILE_H
//      6  = IN WHILE_I
//      7  = IN WHILE_L
//      8  = IN WHILE_E
//      9  = END WHILE KEYWORD - ACCEPTING STATE -> BACK UP
//      10  = IN NUMBER
//      11 = END NUMBER - ACCEPTING STATE -> BACK UP
//      12 = FOUND OPERATOR
//      13 = END OPERATOR - ACCEPTING STATE
//      14 = FOUND SEPARATOR
//      15 = END SEPARATOR - ACCEPTING STATE
//      16 = INVALID - THROW EXCEPTION

// DESIRED TABLE:
//                 0     1     2     3     4     5     6     7     8     9     10    11    12    13    14    15  
// ______________________________________________________________________________________________________________
//  CURR_STATE  | 'w' | 'h' | 'i' | 'l' | 'e' | 'f' | 'a' | 'r' | 'u' | 'p' | DIG | '<' | '=' | '(' | ')' | ' ' |
// _____________|_____|_____|_____|_____|_____|_____|_____|_____|_____|_____|_____|_____|_____|_____|_____|_____|
//      1       |  4  |  2  |  2  |  2  |  2  |  2  |  2  |  2  |  2  |  2  |  10 |  12 |  12 |  14 |  14 |  1  |
// _____________|_____|_____|_____|_____|_____|_____|_____|_____|_____|_____|_____|_____|_____|_____|_____|_____|
//      2       |  2  |  2  |  2  |  2  |  2  |  2  |  2  |  2  |  2  |  2  |  3  |  3  |  3  |  3  |  3  |  3  |
// _____________|_____|_____|_____|_____|_____|_____|_____|_____|_____|_____|_____|_____|_____|_____|_____|_____|
//     _3_      |  1  |  1  |  1  |  1  |  1  |  1  |  1  |  1  |  1  |  1  |  1  |  1  |  1  |  1  |  1  |  1  |   -> BACK UP
// _____________|_____|_____|_____|_____|_____|_____|_____|_____|_____|_____|_____|_____|_____|_____|_____|_____|
//      4       |  2  |  5  |  2  |  2  |  2  |  2  |  2  |  2  |  2  |  2  | 13  |  3  |  3  |  3  |  3  |  3  |
// _____________|_____|_____|_____|_____|_____|_____|_____|_____|_____|_____|_____|_____|_____|_____|_____|_____|
//      5       |  2  |  2  |  6  |  2  |  2  |  2  |  2  |  2  |  2  |  2  | 13  |  3  |  3  |  3  |  3  |  3  |
// _____________|_____|_____|_____|_____|_____|_____|_____|_____|_____|_____|_____|_____|_____|_____|_____|_____|
//      6       |  2  |  2  |  2  |  7  |  2  |  2  |  2  |  2  |  2  |  2  | 13  |  3  |  3  |  3  |  3  |  3  |
// _____________|_____|_____|_____|_____|_____|_____|_____|_____|_____|_____|_____|_____|_____|_____|_____|_____|
//      7       |  2  |  2  |  2  |  2  |  8  |  2  |  2  |  2  |  2  |  2  | 13  |  3  |  3  |  3  |  3  |  3  |
// _____________|_____|_____|_____|_____|_____|_____|_____|_____|_____|_____|_____|_____|_____|_____|_____|_____|
//      8       |  2  |  2  |  2  |  2  |  2  |  2  |  2  |  2  |  2  |  2  | 13  |  9  |  9  |  9  |  9  |  9  |
// _____________|_____|_____|_____|_____|_____|_____|_____|_____|_____|_____|_____|_____|_____|_____|_____|_____|
//     _9_      |  1  |  1  |  1  |  1  |  1  |  1  |  1  |  1  |  1  |  1  |  1  |  1  |  1  |  1  |  1  |  1  |   -> BACK UP
// _____________|_____|_____|_____|_____|_____|_____|_____|_____|_____|_____|_____|_____|_____|_____|_____|_____|
//      10      |  14 |  14 |  14 |  14 |  14 |  14 |  14 |  14 |  14 |  14 |  10 |  11 |  11 |  11 |  11 |  11 |
// _____________|_____|_____|_____|_____|_____|_____|_____|_____|_____|_____|_____|_____|_____|_____|_____|_____|
//     _11_     |  1  |  1  |  1  |  1  |  1  |  1  |  1  |  1  |  1  |  1  |  1  |  1  |  1  |  1  |  1  |  1  |   -> BACK UP
// _____________|_____|_____|_____|_____|_____|_____|_____|_____|_____|_____|_____|_____|_____|_____|_____|_____|
//      12      |  13 |  13 |  13 |  13 |  13 |  13 |  13 |  13 |  13 |  13 |  13 |  13 |  13 |  13 |  13 |  13 |
// _____________|_____|_____|_____|_____|_____|_____|_____|_____|_____|_____|_____|_____|_____|_____|_____|_____|
//     _13_     |  1  |  1  |  1  |  1  |  1  |  1  |  1  |  1  |  1  |  1  |  1  |  1  |  1  |  1  |  1  |  1  |   -> BACK UP
// _____________|_____|_____|_____|_____|_____|_____|_____|_____|_____|_____|_____|_____|_____|_____|_____|_____|
//      14      |  15 |  15 |  15 |  15 |  15 |  15 |  15 |  15 |  15 |  15 |  15 |  15 |  15 |  15 |  15 |  15 |
// _____________|_____|_____|_____|_____|_____|_____|_____|_____|_____|_____|_____|_____|_____|_____|_____|_____|
//     _15_     |  1  |  1  |  1  |  1  |  1  |  1  |  1  |  1  |  1  |  1  |  1  |  1  |  1  |  1  |  1  |  1  |   -> BACK UP
// _____________|_____|_____|_____|_____|_____|_____|_____|_____|_____|_____|_____|_____|_____|_____|_____|_____|
//      16      |  1  |  1  |  1  |  1  |  1  |  1  |  1  |  1  |  1  |  1  |  1  |  1  |  1  |  1  |  1  |  1  |
// _____________|_____|_____|_____|_____|_____|_____|_____|_____|_____|_____|_____|_____|_____|_____|_____|_____|
//

// CHAR TO COLUMN - map char to column number
// COLUMNS: [ 'w', 'h', 'i', 'l', 'e', 'f', 'a', 'r', 'u', 'p', DIG, '<', '=', '(', ')', ' ']
unordered_map<char, int> CHAR_TO_COL {
    {'w', 0},
    {'h', 1},
    {'i', 2},
    {'l', 3},
    {'e', 4},
    {'f', 5},
    {'a', 6},
    {'r', 7},
    {'u', 8},
    {'p', 9},
    {'0', 10},
    {'1', 10},
    {'2', 10},
    {'3', 10},
    {'4', 10},
    {'5', 10},
    {'6', 10},
    {'7', 10},
    {'8', 10},
    {'9', 10},
    {'<', 11},
    {'=', 12},
    {'(', 13},
    {')', 14},
    {' ', 15}
};

// TRANSITION TABLE - create above desired table
const int TRANSITION_TABLE[128][128] = {
    { 0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0 },      // STATE_00 -> PLACEHOLDER
    { 4,  2,  2,  2,  2,  2,  2,  2,  2,  2, 10, 12, 12, 14, 14,  1 },      // STATE_01
    { 2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  3,  3,  3,  3,  3,  3 },      // STATE_02
    { 1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1 },      // STATE_03 -> ACCEPTING STATE -> BACK UP
    { 2,  5,  2,  2,  2,  2,  2,  2,  2,  2,  3,  3,  3,  3,  3,  3 },      // STATE_04
    { 2,  2,  6,  2,  2,  2,  2,  2,  2,  2,  3,  3,  3,  3,  3,  3 },      // STATE_05
    { 2,  2,  2,  7,  2,  2,  2,  2,  2,  2,  3,  3,  3,  3,  3,  3 },      // STATE_06
    { 2,  2,  2,  2,  8,  2,  2,  2,  2,  2,  3,  3,  3,  3,  3,  3 },      // STATE_07
    { 2,  2,  2,  2,  2,  2,  2,  2,  2,  2, 13,  9,  9,  9,  9,  9 },      // STATE_08
    { 1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1 },      // STATE_09 -> ACCEPTING STATE -> BACK UP
    {14, 14, 14, 14, 14, 14, 14, 14, 14, 14, 10, 11, 11, 11, 11, 11 },      // STATE_10
    { 1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1 },      // STATE_11 -> ACCEPTING STATE -> BACK UP
    {13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13 },      // STATE_12
    { 1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1 },      // STATE_13 -> ACCEPTING STATE -> BACK UP
    {15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15 },      // STATE_14 
    { 1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1 },      // STATE_15 -> ACCEPTING STATE -> BACK UP
    { 1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1 },      // STATE_16 -> ACCEPTING STATE -> THROW EXCEPTION
};

// define token types
enum class TokenType {
    IDENTIFIER,
    KEYWORD,
    NUMBER,
    OPERATOR,
    SEPARATOR
};

// define struct to hold lexeme information
struct Token {
    TokenType type;
    string lexeme;
};

vector<Token> lexicalAnalyzer(const string& input) {
    cout << "starting lexical analyzer... \n";
    cout << "input: \"" << input << "\"\n";

    vector<Token> tokens;
    int curr_state = 1;
    string lexeme = "";
    // cout << "here\n";

    // cout << "here\n";
    for (int i = 0; i < input.length(); i++) {
        char c = input[i];

        // get next state
        int col = CHAR_TO_COL[c];
        int next_state = TRANSITION_TABLE[curr_state][col];
        
        // check for error state 13
        if (next_state == 16) {
            cout << "In invalid state. coming from state: " << curr_state << "\n";
            // throw type error exception
            throw std::invalid_argument("Invalid argument!");
        }

        switch (next_state) {
            // is an identifier
            case 3:
                cout << "adding token: IDENTIFIER, lexeme: " << lexeme << "\n"; 
                tokens.push_back({TokenType::IDENTIFIER, lexeme});
                curr_state = 1;
                lexeme = "";
                i--;
                break;

            // is a keyword
            case 9:
                cout << "adding token: KEYWORD, lexeme: " << lexeme << "\n"; 
                tokens.push_back({TokenType::KEYWORD, lexeme});
                curr_state = 1;
                lexeme = "";
                i--;
                break;

            // is a number
            case 11:
                cout << "adding token: NUMBER, lexeme: " << lexeme << "\n"; 
                tokens.push_back({TokenType::NUMBER, lexeme});
                curr_state = 1;
                lexeme = "";
                i--;
                break;

            // is a operator
            case 13:
                cout << "adding token: OPERATOR, lexeme: " << lexeme << "\n"; 
                tokens.push_back({TokenType::OPERATOR, lexeme});
                curr_state = 1;
                lexeme = "";
                i--;
                break;

            // is a separator
            case 15:
                cout << "adding token: SEPARATOR, lexeme: " << lexeme << "\n"; 
                tokens.push_back({TokenType::SEPARATOR, lexeme});
                curr_state = 1;
                lexeme = "";
                i--;
                break;
            default: 
                lexeme += c;
        }

        curr_state = next_state;
    }

    return tokens;
}

#endif // STATETABLE

int main() {
    string input = "while ( fahr < upper ) a = 23";

    vector<Token> tokens = lexicalAnalyzer(input);

    return 0;
}