#include "LexicalAnalyzer.h"

Lexer::Lexer( string& input_file_name , string& output_file_name)
{
    this->input_file_name = input_file_name;
    this->output_file_name = output_file_name;
}

Lexer::~Lexer()
{
    cout << "Destructor is called\n";
}

vector<Token> Lexer::parser(){
       // open input and output files
    std::ifstream in_file("./input/" + this->input_file_name);
    std::ofstream out_file("./output/" + this->output_file_name, std::ios::trunc);

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