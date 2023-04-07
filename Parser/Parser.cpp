#ifndef PREDICTIVE_PARSER_CPP
#define PREDICTIVE_PARSER_CPP

#include "./Parser.h"

PredictiveParser::PredictiveParser(string& input_file_name) {
    // initialize member variables
    this->input_file_name = input_file_name;
    this->_lexer = Lexer(this->input_file_name);
    this->_parser_table = PredictiveParserTable();

    // push starting nonterminal and ending terminal to parser stack: "<Rat23S>", "$"
    this->_parser_stack.push("$");
    this->_parser_stack.push("<Rat23S>");
};

Lexer PredictiveParser::get_lexer() const {
    return _lexer;
}

void PredictiveParser::push_list_to_stack(vector<string>& rhs) {
    // push the rhs in reverse order into the stack
    for (auto it = rhs.rbegin(); it != rhs.rend(); ++it) {
        _parser_stack.push(*it);
    }
}

bool PredictiveParser::parse_to_outfile(string& output_file_name) {
    // open output file
    ofstream out_file("./output/" + output_file_name, std::ios::trunc);

    // if output file successfully opened
    if (out_file.is_open()) {
        out_file << "parsing file: "<< this->input_file_name << "...\n" << std::endl;
        cout << "parsing file: "<< this->input_file_name << "...\n";

        // while parser stack is not empty
        while (!_parser_stack.empty()) {
            // get top of stack
            string top_of_stack = _parser_stack.top();

            // get incoming token
            Token token = _lexer.get_next_token();

            // get token details
            TokenType token_type = token.type;
            string token_type_str = token.type_str;
            string curr_token = token.lexeme;

            // if token type is IDENTIFIER, INTEGER, or REAL, generalize the lexeme to the token type name
            if (token_type == TokenType::IDENTIFIER || token_type == TokenType::INTEGER || token_type == TokenType::REAL) curr_token = token_type_str;
            
            // print current stack
            this->print_current_stack_to_outfile(out_file);

            // if nonterminal = <Empty>, pop it from the stack and skip
            if (top_of_stack == "<Empty>") {
                out_file << "epsilon found -> popping \"" << top_of_stack << "\" from stack\n" << std::endl;
                _parser_stack.pop();
                continue;
            }

            // print current token retrieved from lexer
            token.print_token_to_outfile(out_file);

            // if top_of_stack is a terminal
            if ( TERMINAL_SET.find(top_of_stack) != TERMINAL_SET.end() ) {
                // if curr_token = top_of_stack, pop stack and go to next input token
                if ( curr_token == top_of_stack ) {
                    out_file << "terminal matched: \""<< top_of_stack << "\" = \"" << curr_token << "\" -> popping \"" << top_of_stack << "\" from stack" << std::endl;
                    _parser_stack.pop();
                    _lexer.pop_front();
                }
                // else notify user of parsing error
                else {
                    // print verbose message about the error
                    out_file << "terminals do not match: \""<< top_of_stack << "\" != \"" << curr_token << "\"" << std::endl;

                    // print verbose message about the error to terminal
                    cout << "PARSING ERROR. Invalid input string." << std::endl;
                    cout << "terminals do not match: \""<< top_of_stack << "\" != \"" << curr_token << "\"" << std::endl;
                    cout << "Check ouput/" << output_file_name  << " for more details." << std::endl;

                    // exit gracefully
                    exit(1);
                }
            }
            // else top_of_stack is nonterminal
            else {
                // get the next step (rhs of production)
                vector<string> rhs = _parser_table.get_next_step(top_of_stack, curr_token);

                // if the rhs is not empty
                if ( rhs != vector<string>()) {
                    // print production that will be used to take next step
                    this->print_production(out_file, _parser_stack.top(), rhs);

                    // pop the nonterminal
                    _parser_stack.pop();

                    // push the rhs of production used to the stack
                    this->push_list_to_stack(rhs);
                }
                // else error
                else {
                    // print verbose message about the error to file
                    out_file << "\nno production found in the form: \""<< top_of_stack << "\" => \"" << curr_token << "\" ..." << std::endl;

                    // print verbose message about the error to terminal
                    cout << "PARSING ERROR. Invalid input string." << std::endl;
                    cout << "no production found in the form: "<< top_of_stack << " => " << curr_token << " ..." << std::endl;
                    cout << "Check ouput/" << output_file_name  << " for more details." << std::endl;

                    // exit gracefully
                    exit(1);
                }
            }
            out_file << std::endl;
        }
    }
    else {
        cout << "Files not open. Please check the input directory..." << std::endl;
        exit(1);
    }

    // print success message to output file
    out_file << "successfully parsed input. input is valid." << std::endl;

    // print success message to terminal
    cout << "successfully parsed input. input is valid." << std::endl;
    cout << "Check ouput/" << output_file_name  << " for more details." << std::endl;

    // close file
    out_file.close();

    return true;
}

void PredictiveParser::print_current_stack_to_outfile(ofstream& out_file) {
    // make a copy of the current parser stack
    stack<string> parser_stack_copy(this->_parser_stack);

    // initialize stack string
    string stack_reversed = "";

    // begin printing stack
    out_file << "current stack: ";

    // stack can only be iterated by popping. pop until empty and append popped value to stack string
    while(!parser_stack_copy.empty()) {
        stack_reversed.append(parser_stack_copy.top());
        stack_reversed.append(" ");
        parser_stack_copy.pop();
    }
    
    // print the stack string to the output file
    for (auto elem : stack_reversed) {
        out_file << elem;
    }
    out_file << std::endl;
}

void PredictiveParser::print_production(ofstream& out_file, string& lhs, vector<string> rhs) {
    out_file << "production used: " << lhs << " => " ;
    for (auto elem : rhs) out_file << elem << " ";
    out_file << std::endl;
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