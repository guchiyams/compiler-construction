#ifndef PREDICTIVE_PARSER_CPP
#define PREDICTIVE_PARSER_CPP

#include "../Lexer/Lexer.cpp"
#include "./Parser.h"

// PredictiveParser Constructor
PredictiveParser::PredictiveParser(string& input_file_name) {
    // Initialize member variables
    this->input_file_name = input_file_name;
    this->_lexer = Lexer(this->input_file_name);
    this->_parser_table = PredictiveParserTable();

    // PUSH TO STACK: "<Rat23S>", "$"
    this->_parser_stack.push("$");
    this->_parser_stack.push("<Rat23S>");
};

// Getter function: returns this instance's Lexer
Lexer PredictiveParser::get_lexer() const {
    return _lexer;
}

// parse input file => output to output file
bool PredictiveParser::parse_to_outfile(string& output_file_name) {
    // open output file
    ofstream out_file("./output/" + output_file_name, std::ios::trunc);

    // if output file successfully open
    if (out_file.is_open()) {
        out_file << "parsing input...\n" << std::endl;

        // while parser stack is not empty
        while (!_parser_stack.empty()) {
            // print current stack
            this->print_current_stack_to_outfile(out_file);

            // get top of stack
            string top_of_stack = _parser_stack.top();

            // get incoming token
            Token token = _lexer.get_next_token();

            // get token information
            TokenType token_type = token.type;
            string token_type_str = token.type_str;
            string next_token = token.lexeme;

            // if token type is IDENTIFIER, INTEGER, or REAL, generalize the lexeme to the token type name
            if (token_type == TokenType::IDENTIFIER || token_type == TokenType::INTEGER || token_type == TokenType::REAL) next_token = token_type_str;

            // if nonterminal = <Empty>, pop and skip
            if (top_of_stack == "<Empty>") {
                _parser_stack.pop();
                continue;
            }

            // print current token retrieved from lexer
            token.print_token_to_outfile(out_file);

            // if top_of_stack is a terminal
            if ( TERMINAL_SET.find(top_of_stack) != TERMINAL_SET.end() ) {
                // if next_token = top_of_stack, pop stack and go to next input token
                if ( next_token == top_of_stack ) {
                    _parser_stack.pop();
                    Token popped = _lexer.pop_front();
                    // cout << "POPPING LEXEME: " << popped.lexeme << std::endl;
                }
                else {
                    out_file << "ERROR" << std::endl;
                    return false;
                }
            }
            // else top_of_stack is nonterminal
            else {
                vector<string> rhs = _parser_table.get_next_production(top_of_stack, next_token);
                if ( rhs != vector<string>()) {
                    out_file << _parser_stack.top() << " => " ;
                    for (auto elem : rhs) out_file << elem << " ";
                    out_file << std::endl;
                    // cout << "POPPING NONTERMINAL: " << _parser_stack.top() << std::endl;
                    _parser_stack.pop();
                    // push the rhs in reverse order
                    for (auto it = rhs.rbegin(); it != rhs.rend(); ++it) {
                        _parser_stack.push(*it);
                    }
                } else {
                    out_file << "ERROR" << std::endl;
                    return false;
                }
            }

            // close output file
            out_file << std::endl;
        }
    }
    else {
        cout << "Files not open. Aborting..." << std::endl;
        exit(1);
    }

    out_file << "successfully parsed input. input is valid." << std::endl;
    out_file.close();
    return true;
}

void PredictiveParser::print_current_stack_to_outfile(ofstream& out_file) {
    // print current stack
    stack<string> parser_stack_copy(this->_parser_stack);
    string stack_reversed = "";
    out_file << "current stack: \"";
    while(!parser_stack_copy.empty()) {
        stack_reversed.append("\"");
        stack_reversed.append(parser_stack_copy.top());
        stack_reversed.append("\",");
        parser_stack_copy.pop();
    }
    for (auto elem : stack_reversed) {
        out_file << elem;
    }
    out_file << "\"" << std::endl;
}

const unordered_set<string> PredictiveParser::TERMINAL_SET({
    "function",
    "IDENTIFIER",
    "INTEGER",
    "REAL",
    "int",
    "boolean",
    "real",
    "{",
    "}",
    "(",
    ")",
    "[",
    "]",
    "if",
    "else",
    "endif",
    "return",
    "put",
    "get",
    "while",
    "true",
    "false",
    "+",
    "-",
    "*",
    "/",
    "=",
    "==",
    "^=",
    ">",
    "<",
    "=>",
    "=<",
    ":",
    ";",
    ",",
    "%",
    "$",
});

#endif // PREDICTIVE_PARSER_CPP