#ifndef PREDICTIVE_PARSER_CPP
#define PREDICTIVE_PARSER_CPP

#include "../Lexer/Lexer.cpp"
#include "./Parser.h"

PredictiveParser::PredictiveParser(string& input_file_name) {
    // cout << "initizalizing predictive parser..." << std::endl;
    this->input_file_name = input_file_name;
    this->_lexer = Lexer(this->input_file_name);
    this->_parser_table = PredictiveParserTable();

    this->_parser_stack.push("$");
    this->_parser_stack.push("<Rat23S>");
};

Lexer PredictiveParser::get_lexer() const {
    return _lexer;
}

bool PredictiveParser::parse_to_outfile(string& output_file_name) {
    // open output file
    ofstream out_file("./output/" + output_file_name, std::ios::trunc);

    out_file << "parsing input...\n" << std::endl;
    if (out_file.is_open()) {
        // while parser stack is not empty
        while (!_parser_stack.empty()) {
            // get top of stack
            string top_of_stack = _parser_stack.top();

            // get incoming token
            Token token = _lexer.get_next_token();
            string token_type = token.type_str;
            string next_token = token.lexeme;
            if (token_type == "IDENTIFIER" || token_type == "INTEGER" || token_type == "REAL") next_token = token_type;

            if (top_of_stack == "<Empty>") {
                _parser_stack.pop();
                continue;
            }

            token.print_token_to_outfile(out_file);

            // if top_of_stack is a terminal
            if ( TERMINAL_SET.find(top_of_stack) != TERMINAL_SET.end() ) {
                // cout << "IS A TERMINAL: " << std::endl;
                if ( next_token == top_of_stack ) {
                    // if next_token = top_of_stack, pop stack and go to next input token
                    _parser_stack.pop();
                    Token popped = _lexer.pop_front();
                    // cout << "POPPING LEXEME: " << popped.lexeme << std::endl;
                }
                else {
                    out_file << "ERROR" << std::endl;
                    return false;
                }
            } else {
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

            // print current stack
            // stack<string> parser_stack_copy(_parser_stack);
            // cout << "CURRENT STACK: \"";
            // while(!parser_stack_copy.empty()) {
            //     std::cout << parser_stack_copy.top() << " ";
            //     parser_stack_copy.pop();
            // }
            // cout << "\"" << std::endl;


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