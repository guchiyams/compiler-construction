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
//      10 = IN NUMBER
//      11 = END NUMBER - ACCEPTING STATE -> BACK UP
//      12 = FOUND OPERATOR
//      13 = END OPERATOR - ACCEPTING STATE
//      14 = FOUND SEPARATOR
//      15 = END SEPARATOR - ACCEPTING STATE
//      16 = INVALID - THROW EXCEPTION
//      17 = END OF INPUT - ACCEPTING STATE -> BREAK LOOP

// DESIRED TABLE:
//                 0     1     2     3     4     5     6     7     8     9     10    11    12    13    14    15    16 
// _____________________________________________________________________________________________________________________
//  CURR_STATE  | 'w' | 'h' | 'i' | 'l' | 'e' | 'f' | 'a' | 'r' | 'u' | 'p' | DIG | '<' | '=' | '(' | ')' | ' ' | endl |   
// _____________|_____|_____|_____|_____|_____|_____|_____|_____|_____|_____|_____|_____|_____|_____|_____|_____|______|
//      1       |  4  |  2  |  2  |  2  |  2  |  2  |  2  |  2  |  2  |  2  |  10 |  12 |  12 |  14 |  14 |  1  |  17  |    STARTING STATE
// _____________|_____|_____|_____|_____|_____|_____|_____|_____|_____|_____|_____|_____|_____|_____|_____|_____|______|
//      2       |  2  |  2  |  2  |  2  |  2  |  2  |  2  |  2  |  2  |  2  |  3  |  3  |  3  |  3  |  3  |  3  |   3  |    IN IDENTIFIER
// _____________|_____|_____|_____|_____|_____|_____|_____|_____|_____|_____|_____|_____|_____|_____|_____|_____|______|
//     _3_      |  1  |  1  |  1  |  1  |  1  |  1  |  1  |  1  |  1  |  1  |  1  |  12 |  12 |  14 |  14 |  1  |  17  |    END IDENTIFIER - ACCEPTING STATE -> BACK UP
// _____________|_____|_____|_____|_____|_____|_____|_____|_____|_____|_____|_____|_____|_____|_____|_____|_____|______|
//      4       |  2  |  5  |  2  |  2  |  2  |  2  |  2  |  2  |  2  |  2  | 13  |  3  |  3  |  3  |  3  |  3  |   3  |    IN WHILE KEYWORD
// _____________|_____|_____|_____|_____|_____|_____|_____|_____|_____|_____|_____|_____|_____|_____|_____|_____|______|
//      5       |  2  |  2  |  6  |  2  |  2  |  2  |  2  |  2  |  2  |  2  | 13  |  3  |  3  |  3  |  3  |  3  |   3  |    IN WHILE_H
// _____________|_____|_____|_____|_____|_____|_____|_____|_____|_____|_____|_____|_____|_____|_____|_____|_____|______|
//      6       |  2  |  2  |  2  |  7  |  2  |  2  |  2  |  2  |  2  |  2  | 13  |  3  |  3  |  3  |  3  |  3  |   3  |    IN WHILE_I
// _____________|_____|_____|_____|_____|_____|_____|_____|_____|_____|_____|_____|_____|_____|_____|_____|_____|______|
//      7       |  2  |  2  |  2  |  2  |  8  |  2  |  2  |  2  |  2  |  2  | 13  |  3  |  3  |  3  |  3  |  3  |   3  |    IN WHILE_L
// _____________|_____|_____|_____|_____|_____|_____|_____|_____|_____|_____|_____|_____|_____|_____|_____|_____|______|
//      8       |  2  |  2  |  2  |  2  |  2  |  2  |  2  |  2  |  2  |  2  | 13  |  9  |  9  |  9  |  9  |  9  |   9  |    IN WHILE_E
// _____________|_____|_____|_____|_____|_____|_____|_____|_____|_____|_____|_____|_____|_____|_____|_____|_____|______|
//     _9_      |  1  |  1  |  1  |  1  |  1  |  1  |  1  |  1  |  1  |  1  | 17  |  12 |  12 |  14 |  14 |  1  |  17  |    END WHILE KEYWORD - ACCEPTING STATE -> BACK UP
// _____________|_____|_____|_____|_____|_____|_____|_____|_____|_____|_____|_____|_____|_____|_____|_____|_____|______|
//      10      |  16 |  16 |  16 |  16 |  16 |  16 |  16 |  16 |  16 |  16 |  10 |  11 |  11 |  11 |  11 |  11 |  11  |    IN NUMBER
// _____________|_____|_____|_____|_____|_____|_____|_____|_____|_____|_____|_____|_____|_____|_____|_____|_____|______|
//     _11_     |  1  |  1  |  1  |  1  |  1  |  1  |  1  |  1  |  1  |  1  |  1  |  12 |  12 |  14 |  14 |  1  |  17  |    END NUMBER - ACCEPTING STATE -> BACK UP
// _____________|_____|_____|_____|_____|_____|_____|_____|_____|_____|_____|_____|_____|_____|_____|_____|_____|______|
//      12      |  13 |  13 |  13 |  13 |  13 |  13 |  13 |  13 |  13 |  13 |  13 |  13 |  13 |  13 |  13 |  13 |  13  |    FOUND OPERATOR
// _____________|_____|_____|_____|_____|_____|_____|_____|_____|_____|_____|_____|_____|_____|_____|_____|_____|______|
//     _13_     |  1  |  1  |  1  |  1  |  1  |  1  |  1  |  1  |  1  |  1  |  1  |  1  |  1  |  1  |  1  |  1  |  17  |    END OPERATOR - ACCEPTING STATE -> BACK UP?
// _____________|_____|_____|_____|_____|_____|_____|_____|_____|_____|_____|_____|_____|_____|_____|_____|_____|______|
//      14      |  15 |  15 |  15 |  15 |  15 |  15 |  15 |  15 |  15 |  15 |  15 |  15 |  15 |  15 |  15 |  15 |  15  |    FOUND SEPARATOR
// _____________|_____|_____|_____|_____|_____|_____|_____|_____|_____|_____|_____|_____|_____|_____|_____|_____|______|
//     _15_     |  2  |  2  |  2  |  2  |  2  |  2  |  2  |  2  |  2  |  2  |  10 |  12 |  12 |  14 |  14 |  1  |  17  |    END SEPARATOR - ACCEPTING STATE -> BACK UP?
// _____________|_____|_____|_____|_____|_____|_____|_____|_____|_____|_____|_____|_____|_____|_____|_____|_____|______|
//      16      |  1  |  1  |  1  |  1  |  1  |  1  |  1  |  1  |  1  |  1  |  1  |  1  |  1  |  1  |  1  |  1  |  17  |    INVALID - THROW EXCEPTION
// _____________|_____|_____|_____|_____|_____|_____|_____|_____|_____|_____|_____|_____|_____|_____|_____|_____|______|
//      17      |  1  |  1  |  1  |  1  |  1  |  1  |  1  |  1  |  1  |  1  |  1  |  1  |  1  |  1  |  1  |  1  |  17  |    END OF INPUT - ACCEPTING STATE -> BREAK LOOP
// _____________|_____|_____|_____|_____|_____|_____|_____|_____|_____|_____|_____|_____|_____|_____|_____|_____|______|
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
    {' ', 15},
    // {'' , 17}
};

// TRANSITION TABLE - create above desired table
const int TRANSITION_TABLE[128][128] = {
    { 0,  1,  2,  3,  4,  5,  6,  7,  8,  9, 10, 11, 12, 13, 14, 15, 16 },      // STATE_00 -> PLACEHOLDER
    { 4,  2,  2,  2,  2,  2,  2,  2,  2,  2, 10, 12, 12, 14, 14,  1, 17 },      // STATE_01
    { 2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  3,  3,  3,  3,  3,  3,  3 },      // STATE_02
    { 1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1, 12, 12, 14, 14,  1, 17 },      // STATE_03 -> ACCEPTING STATE -> BACK UP
    { 2,  5,  2,  2,  2,  2,  2,  2,  2,  2,  3,  3,  3,  3,  3,  3,  3 },      // STATE_04
    { 2,  2,  6,  2,  2,  2,  2,  2,  2,  2,  3,  3,  3,  3,  3,  3,  3 },      // STATE_05
    { 2,  2,  2,  7,  2,  2,  2,  2,  2,  2,  3,  3,  3,  3,  3,  3,  3 },      // STATE_06
    { 2,  2,  2,  2,  8,  2,  2,  2,  2,  2,  3,  3,  3,  3,  3,  3,  3 },      // STATE_07
    { 2,  2,  2,  2,  2,  2,  2,  2,  2,  2, 16,  9,  9,  9,  9,  9,  9 },      // STATE_08
    { 1,  1,  1,  1,  1,  1,  1,  1,  1,  1, 16, 12, 12, 14, 14,  1, 17 },      // STATE_09 -> ACCEPTING STATE -> BACK UP
    {16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 10, 11, 11, 11, 11, 11, 11 },      // STATE_10
    { 1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1, 12, 12, 14, 14,  1, 17 },      // STATE_11 -> ACCEPTING STATE -> BACK UP
    {13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13 },      // STATE_12
    { 1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1, 17 },      // STATE_13 -> ACCEPTING STATE -> BACK UP
    {15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15 },      // STATE_14 
    { 2,  2,  2,  2,  2,  2,  2,  2,  2,  2, 10, 12, 12, 14, 14,  1, 17 },      // STATE_15 -> ACCEPTING STATE -> BACK UP
    { 1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1, 17 },      // STATE_16 -> ACCEPTING STATE -> THROW EXCEPTION
    { 1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1, 17 },      // STATE_17
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
    cout << "\nstarting lexical analyzer... \n";
    cout << "input: \"" << input << "\"\n\n";

    vector<Token> tokens;
    int curr_state = 1;
    string lexeme = "";
    bool isEnd = false;

    for (int i = 0; i < input.length(); i++) {
        char c = input[i];

        int next_state = 0;

        if (isEnd == false) {
            // get next state
            int col = CHAR_TO_COL[c];
            next_state = TRANSITION_TABLE[curr_state][col];
        } else {
            // don't go to next state - stay on current state
            next_state = curr_state;
        }

        // cout << "CURRENT CHAR: \"" << c << "\"\n";
        // cout << "CURRENT STATE: " << curr_state << "\n";
        // cout << "NEXT STATE:    " << next_state << "\n\n";
        
        // check for error state 13
        if (next_state == 16) {
            // throw type error exception
            throw std::invalid_argument("In invalid state - " + std::to_string(next_state) + " - coming from state: " + std::to_string(curr_state) + "\n");
        }

        switch (next_state) {
            // is an identifier
            case 3:
                if (isEnd == true) {
                    cout << "adding token: IDENTIFIER,      lexeme: " << lexeme << "\n"; 
                    tokens.push_back({TokenType::IDENTIFIER, lexeme});
                    continue;
                }

                cout <<     "adding token: IDENTIFIER,      lexeme: " << lexeme << "\n"; 
                tokens.push_back({TokenType::IDENTIFIER, lexeme});
                curr_state = 1;
                lexeme = "";
                i--;
                break;

            // is a keyword
            case 9:
                if (isEnd == true) {
                    cout << "adding token: KEYWORD   ,      lexeme: " << lexeme << "\n"; 
                    tokens.push_back({TokenType::KEYWORD, lexeme});
                    continue;
                }
                cout <<     "adding token: KEYWORD   ,      lexeme: " << lexeme << "\n"; 
                tokens.push_back({TokenType::KEYWORD, lexeme});
                curr_state = 1;
                lexeme = "";
                // i--;
                break;

            // is a number
            case 11:
                if (isEnd == true) {
                    cout << "adding token: NUMBER    ,      lexeme: " << lexeme << "\n"; 
                    tokens.push_back({TokenType::NUMBER, lexeme});
                    continue;
                }
                cout <<     "adding token: NUMBER    ,      lexeme: " << lexeme << "\n"; 
                tokens.push_back({TokenType::NUMBER, lexeme});
                curr_state = 1;
                lexeme = "";
                i--;
                break;

            // is an operator
            case 13:
                if (isEnd == true) {
                    cout << "adding token: OPERATOR  ,      lexeme: " << lexeme << "\n"; 
                    tokens.push_back({TokenType::OPERATOR, lexeme});
                    continue;
                }
                cout <<     "adding token: OPERATOR  ,      lexeme: " << lexeme << "\n"; 
                tokens.push_back({TokenType::OPERATOR, lexeme});
                curr_state = 1;
                lexeme = "";
                i--;
                break;

            // is a separator
            case 15:
                if (isEnd == true) {
                    cout << "adding token: SEPARATOR ,      lexeme: " << lexeme << "\n"; 
                    tokens.push_back({TokenType::SEPARATOR, lexeme});
                    continue;
                }
                cout <<     "adding token: SEPARATOR ,      lexeme: " << lexeme << "\n"; 
                tokens.push_back({TokenType::SEPARATOR, lexeme});
                curr_state = 1;
                lexeme = "";
                i--;
                break;
            default:
                lexeme += c;
                if (i == input.length() - 1) {
                    if (isEnd == true) {
                        continue;
                    } else {
                        // !!LAST TOKEN!!\n";
                        // SETTING NEXT STATE TO CURRENT STATES' END OF INPUT STATE (COLUMN INDEX 16)
                        // SETTING ISEND BOOL VARIABLE TO TRUE, THEN DECREMENT ITERATOR TO RUN AGAIN

                        curr_state = TRANSITION_TABLE[next_state][16];
                        isEnd = true;
                        i--;

                        continue;
                    }

                }
        }
        curr_state = next_state;
    }
    cout << "\nlexical analyzer complete...\n\n";
    return tokens;
}

#endif // STATETABLE

// TODO-02: floating point numbers

int main() {
    string input = "while (fahr<upper)a=23";

    vector<Token> tokens = lexicalAnalyzer(input);

    return 0;
}