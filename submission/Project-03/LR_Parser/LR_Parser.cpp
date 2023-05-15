#ifndef LR_PARSER_CPP
#define LR_PARSER_CPP

#include "./LR_Parser.h"

LR_Parser::LR_Parser(string& input_file_name) {
    // initialize member variables
    this->in_opt_decl_list = true;
    this->_input_file_name = input_file_name;
    this->_IDs = unordered_map<size_t, vector<size_t>>();
    this->_lexer = Lexer(this->_input_file_name);
    this->_lr_parser_table = LR_ParserTable();
    this->_symbol_table = SymbolTable();
    this->_instruction_set = vector<pair<string, QuadRecord>>();
    this->_quad_table = vector<QuadRecord>();
    this->generated_code_line_count = 1;

    // push the start state and the end of file symbol onto the stack
    this->_lr_parser_stack.push(std::make_pair("$", 0));
    this->_lr_parser_frame_stack.push(StackFrame(0, "$"));
};

Lexer LR_Parser::get_lexer() const {
    return _lexer;
};

SymbolTable LR_Parser::get_symbol_table() const {
    return _symbol_table;
};

bool LR_Parser::compile(string& output_file_name) {
    auto parse = this->parse_to_outfile(output_file_name);
    ofstream out_file("./output/" + output_file_name, std::ios::trunc);

    int line_count = 1;
    for (int i = 0; i < _quad_table.size(); i++) {
        if (_quad_table[i]._op == "=") {
            auto symbol_entry = _symbol_table.get_symbol_entry(_quad_table[i]._oprnd1);
            if (_symbol_table.get_address(_quad_table[i]._oprnd1)._data_type_str == "INTEGER" || _symbol_table.get_address(_quad_table[i]._oprnd1)._data_type_str == "BOOLEAN") {
                _instruction_set.push_back(std::make_pair("PUSHM " + std::to_string(_quad_table[i]._oprnd1), _quad_table[i]));
                ++line_count;
            } else if (symbol_entry.second.second._data_type == SymbolDataType::INT_VAL) {
                _instruction_set.push_back(std::make_pair("PUSHI " + symbol_entry.first, _quad_table[i]));
                ++line_count;
            }
            _instruction_set.push_back(std::make_pair("POPM " + std::to_string(_quad_table[i]._result), _quad_table[i]));
            ++line_count;
        }
        else if (_quad_table[i]._op == "+") {
            // if the 
            auto symbol_entry_1 = _symbol_table.get_symbol_entry(_quad_table[i]._oprnd1);
            if (symbol_entry_1.second.second._data_type == SymbolDataType::INT_VAL) {
                _instruction_set.push_back(std::make_pair("PUSHI " + symbol_entry_1.first, _quad_table[i]));
                ++line_count;
            } else if (symbol_entry_1.second.second._data_type != SymbolDataType::TEMP) {
                _instruction_set.push_back(std::make_pair("PUSHM " + std::to_string(_quad_table[i]._oprnd1), _quad_table[i]));
                ++line_count;
            }

            auto symbol_entry_2 = _symbol_table.get_symbol_entry(_quad_table[i]._oprnd2);
            if (symbol_entry_2.second.second._data_type == SymbolDataType::INT_VAL) {
                _instruction_set.push_back(std::make_pair("PUSHI " + symbol_entry_2.first, _quad_table[i]));
                ++line_count;
            } else {
                _instruction_set.push_back(std::make_pair("PUSHM " + std::to_string(_quad_table[i]._oprnd2), _quad_table[i]));
                ++line_count;
            }
            _instruction_set.push_back(std::make_pair("ADD", _quad_table[i]));
            ++line_count;
        }
        else if (_quad_table[i]._op == "-") {
            // if the 
            auto symbol_entry_1 = _symbol_table.get_symbol_entry(_quad_table[i]._oprnd1);
            if (symbol_entry_1.second.second._data_type == SymbolDataType::INT_VAL) {
                _instruction_set.push_back(std::make_pair("PUSHI " + symbol_entry_1.first, _quad_table[i]));
                ++line_count;
            } else if (symbol_entry_1.second.second._data_type != SymbolDataType::TEMP) {
                _instruction_set.push_back(std::make_pair("PUSHM " + std::to_string(_quad_table[i]._oprnd1), _quad_table[i]));
                ++line_count;
            }

            auto symbol_entry_2 = _symbol_table.get_symbol_entry(_quad_table[i]._oprnd2);
            if (symbol_entry_2.second.second._data_type == SymbolDataType::INT_VAL) {
                _instruction_set.push_back(std::make_pair("PUSHI " + symbol_entry_2.first, _quad_table[i]));
                ++line_count;
            } else {
                _instruction_set.push_back(std::make_pair("PUSHM " + std::to_string(_quad_table[i]._oprnd2), _quad_table[i]));
                ++line_count;
            }
            _instruction_set.push_back(std::make_pair("SUB", _quad_table[i]));
            ++line_count;
        }
        else if (_quad_table[i]._op == "*") {
            // if the 
            auto symbol_entry_1 = _symbol_table.get_symbol_entry(_quad_table[i]._oprnd1);
            if (symbol_entry_1.second.second._data_type == SymbolDataType::INT_VAL) {
                _instruction_set.push_back(std::make_pair("PUSHI " + symbol_entry_1.first, _quad_table[i]));
                ++line_count;
            } else if (symbol_entry_1.second.second._data_type != SymbolDataType::TEMP) {
                _instruction_set.push_back(std::make_pair("PUSHM " + std::to_string(_quad_table[i]._oprnd1), _quad_table[i]));
                ++line_count;
            }

            auto symbol_entry_2 = _symbol_table.get_symbol_entry(_quad_table[i]._oprnd2);
            if (symbol_entry_2.second.second._data_type == SymbolDataType::INT_VAL) {
                _instruction_set.push_back(std::make_pair("PUSHI " + symbol_entry_2.first, _quad_table[i]));
                ++line_count;
            } else {
                _instruction_set.push_back(std::make_pair("PUSHM " + std::to_string(_quad_table[i]._oprnd2), _quad_table[i]));
                ++line_count;
            }
            _instruction_set.push_back(std::make_pair("MUL", _quad_table[i]));
            ++line_count;
        }
        else if (_quad_table[i]._op == "/") {
            // if the 
            auto symbol_entry_1 = _symbol_table.get_symbol_entry(_quad_table[i]._oprnd1);
            if (symbol_entry_1.second.second._data_type == SymbolDataType::INT_VAL) {
                _instruction_set.push_back(std::make_pair("PUSHI " + symbol_entry_1.first, _quad_table[i]));
                ++line_count;
            } else if (symbol_entry_1.second.second._data_type != SymbolDataType::TEMP) {
                _instruction_set.push_back(std::make_pair("PUSHM " + std::to_string(_quad_table[i]._oprnd1), _quad_table[i]));
                ++line_count;
            }

            auto symbol_entry_2 = _symbol_table.get_symbol_entry(_quad_table[i]._oprnd2);
            if (symbol_entry_2.second.second._data_type == SymbolDataType::INT_VAL) {
                _instruction_set.push_back(std::make_pair("PUSHI " + symbol_entry_2.first, _quad_table[i]));
                ++line_count;
            } else {
                _instruction_set.push_back(std::make_pair("PUSHM " + std::to_string(_quad_table[i]._oprnd2), _quad_table[i]));
                ++line_count;
            }
            _instruction_set.push_back(std::make_pair("DIV", _quad_table[i]));
            ++line_count;
        }
        else if (_quad_table[i]._op == "==") {
            // if the 
            auto symbol_entry_1 = _symbol_table.get_symbol_entry(_quad_table[i]._oprnd1);
            if (symbol_entry_1.second.second._data_type == SymbolDataType::INT_VAL) {
                _instruction_set.push_back(std::make_pair("PUSHI " + symbol_entry_1.first, _quad_table[i]));
                ++line_count;
            } else if (symbol_entry_1.second.second._data_type != SymbolDataType::TEMP) {
                _instruction_set.push_back(std::make_pair("PUSHM " + std::to_string(_quad_table[i]._oprnd1), _quad_table[i]));
                ++line_count;
            }

            auto symbol_entry_2 = _symbol_table.get_symbol_entry(_quad_table[i]._oprnd2);
            if (symbol_entry_2.second.second._data_type == SymbolDataType::INT_VAL) {
                _instruction_set.push_back(std::make_pair("PUSHI " + symbol_entry_2.first, _quad_table[i]));
                ++line_count;
            } else {
                _instruction_set.push_back(std::make_pair("PUSHM " + std::to_string(_quad_table[i]._oprnd2), _quad_table[i]));
                ++line_count;
            }
            _instruction_set.push_back(std::make_pair("EQU", _quad_table[i]));
            ++line_count;
        }
        else if (_quad_table[i]._op == "^=") {
            // if the 
            auto symbol_entry_1 = _symbol_table.get_symbol_entry(_quad_table[i]._oprnd1);
            if (symbol_entry_1.second.second._data_type == SymbolDataType::INT_VAL) {
                _instruction_set.push_back(std::make_pair("PUSHI " + symbol_entry_1.first, _quad_table[i]));
                ++line_count;
            } else if (symbol_entry_1.second.second._data_type != SymbolDataType::TEMP) {
                _instruction_set.push_back(std::make_pair("PUSHM " + std::to_string(_quad_table[i]._oprnd1), _quad_table[i]));
                ++line_count;
            }

            auto symbol_entry_2 = _symbol_table.get_symbol_entry(_quad_table[i]._oprnd2);
            if (symbol_entry_2.second.second._data_type == SymbolDataType::INT_VAL) {
                _instruction_set.push_back(std::make_pair("PUSHI " + symbol_entry_2.first, _quad_table[i]));
                ++line_count;
            } else {
                _instruction_set.push_back(std::make_pair("PUSHM " + std::to_string(_quad_table[i]._oprnd2), _quad_table[i]));
                ++line_count;
            }
            _instruction_set.push_back(std::make_pair("NEQ", _quad_table[i]));
            ++line_count;
        }
        else if (_quad_table[i]._op == ">") {
            // if the 
            auto symbol_entry_1 = _symbol_table.get_symbol_entry(_quad_table[i]._oprnd1);
            if (symbol_entry_1.second.second._data_type == SymbolDataType::INT_VAL) {
                _instruction_set.push_back(std::make_pair("PUSHI " + symbol_entry_1.first, _quad_table[i]));
                ++line_count;
            } else if (symbol_entry_1.second.second._data_type != SymbolDataType::TEMP) {
                _instruction_set.push_back(std::make_pair("PUSHM " + std::to_string(_quad_table[i]._oprnd1), _quad_table[i]));
                ++line_count;
            }

            auto symbol_entry_2 = _symbol_table.get_symbol_entry(_quad_table[i]._oprnd2);
            if (symbol_entry_2.second.second._data_type == SymbolDataType::INT_VAL) {
                _instruction_set.push_back(std::make_pair("PUSHI " + symbol_entry_2.first, _quad_table[i]));
                ++line_count;
            } else {
                _instruction_set.push_back(std::make_pair("PUSHM " + std::to_string(_quad_table[i]._oprnd2), _quad_table[i]));
                ++line_count;
            }
            _instruction_set.push_back(std::make_pair("GRT", _quad_table[i]));
            ++line_count;
        }
        else if (_quad_table[i]._op == "<") {
            // if the 
            auto symbol_entry_1 = _symbol_table.get_symbol_entry(_quad_table[i]._oprnd1);
            if (symbol_entry_1.second.second._data_type == SymbolDataType::INT_VAL) {
                _instruction_set.push_back(std::make_pair("PUSHI " + symbol_entry_1.first, _quad_table[i]));
                ++line_count;
            } else if (symbol_entry_1.second.second._data_type != SymbolDataType::TEMP) {
                _instruction_set.push_back(std::make_pair("PUSHM " + std::to_string(_quad_table[i]._oprnd1), _quad_table[i]));
                ++line_count;
            }

            auto symbol_entry_2 = _symbol_table.get_symbol_entry(_quad_table[i]._oprnd2);
            if (symbol_entry_2.second.second._data_type == SymbolDataType::INT_VAL) {
                _instruction_set.push_back(std::make_pair("PUSHI " + symbol_entry_2.first, _quad_table[i]));
                ++line_count;
            } else {
                _instruction_set.push_back(std::make_pair("PUSHM " + std::to_string(_quad_table[i]._oprnd2), _quad_table[i]));
                ++line_count;
            }
            _instruction_set.push_back(std::make_pair("LES", _quad_table[i]));
            ++line_count;
        }
        else if (_quad_table[i]._op == "=>") {
            // if the 
            auto symbol_entry_1 = _symbol_table.get_symbol_entry(_quad_table[i]._oprnd1);
            if (symbol_entry_1.second.second._data_type == SymbolDataType::INT_VAL) {
                _instruction_set.push_back(std::make_pair("PUSHI " + symbol_entry_1.first, _quad_table[i]));
                ++line_count;
            } else if (symbol_entry_1.second.second._data_type != SymbolDataType::TEMP) {
                _instruction_set.push_back(std::make_pair("PUSHM " + std::to_string(_quad_table[i]._oprnd1), _quad_table[i]));
                ++line_count;
            }

            auto symbol_entry_2 = _symbol_table.get_symbol_entry(_quad_table[i]._oprnd2);
            if (symbol_entry_2.second.second._data_type == SymbolDataType::INT_VAL) {
                _instruction_set.push_back(std::make_pair("PUSHI " + symbol_entry_2.first, _quad_table[i]));
                ++line_count;
            } else {
                _instruction_set.push_back(std::make_pair("PUSHM " + std::to_string(_quad_table[i]._oprnd2), _quad_table[i]));
                ++line_count;
            }
            _instruction_set.push_back(std::make_pair("GEQ", _quad_table[i]));
            ++line_count;
        }
        else if (_quad_table[i]._op == "=<") {
            // if the 
            auto symbol_entry_1 = _symbol_table.get_symbol_entry(_quad_table[i]._oprnd1);
            if (symbol_entry_1.second.second._data_type == SymbolDataType::INT_VAL) {
                _instruction_set.push_back(std::make_pair("PUSHI " + symbol_entry_1.first, _quad_table[i]));
                ++line_count;
            } else if (symbol_entry_1.second.second._data_type != SymbolDataType::TEMP) {
                _instruction_set.push_back(std::make_pair("PUSHM " + std::to_string(_quad_table[i]._oprnd1), _quad_table[i]));
                ++line_count;
            }

            auto symbol_entry_2 = _symbol_table.get_symbol_entry(_quad_table[i]._oprnd2);
            if (symbol_entry_2.second.second._data_type == SymbolDataType::INT_VAL) {
                _instruction_set.push_back(std::make_pair("PUSHI " + symbol_entry_2.first, _quad_table[i]));
                ++line_count;
            } else {
                _instruction_set.push_back(std::make_pair("PUSHM " + std::to_string(_quad_table[i]._oprnd2), _quad_table[i]));
                ++line_count;
            }
            _instruction_set.push_back(std::make_pair("LEQ", _quad_table[i]));
            ++line_count;
        }
        else if (_quad_table[i]._op == "ifjumpz") {
            _instruction_set.push_back(std::make_pair("JUMPZ", _quad_table[i]));
            ++line_count;
        }
        else if (_quad_table[i]._op == "jump") {
            _instruction_set.push_back(std::make_pair("JUMP", _quad_table[i]));
            ++line_count;
        }
        else if (_quad_table[i]._op == "label") {
            _instruction_set.push_back(std::make_pair("LABEL", _quad_table[i]));
            for (auto& elem : _instruction_set) {
                if (elem.first == "JUMP") {
                    if (elem.second._result == _quad_table[i]._oprnd1) {
                        elem.first = elem.first + " " + std::to_string(line_count);
                    }
                }
            }
            ++line_count;
        }
        else if (_quad_table[i]._op == "iflabel") {
            _instruction_set.push_back(std::make_pair("LABEL", _quad_table[i]));
            for (auto& elem : _instruction_set) {
                if (elem.first == "JUMPZ") {
                    if (elem.second._result == _quad_table[i]._oprnd1) {
                        elem.first = elem.first + " " + std::to_string(line_count);
                    }
                }
            }
            ++line_count;
        }
        else if (_quad_table[i]._op == "whilelabel") {
            _instruction_set.push_back(std::make_pair("LABEL", _quad_table[i]));

            auto n = _instruction_set.size();
            _instruction_set.push_back(_instruction_set[n-4]);
            _instruction_set.push_back(_instruction_set[n-3]);
            _instruction_set.push_back(_instruction_set[n-2]);

            // removed the condition that was moved to the end
            _instruction_set.erase(_instruction_set.begin() + (n-2));
            _instruction_set.erase(_instruction_set.begin() + (n-3));
            _instruction_set.erase(_instruction_set.begin() + (n-4));

            _instruction_set.push_back(std::make_pair("JUMPZ", _quad_table[i]));

            line_count+=2;
        }
        else if (_quad_table[i]._op == "whilejumpz") {
            for (int n = 0; n < _instruction_set.size(); n++) {
                if (_instruction_set[n].first == "LABEL" && _instruction_set[n].second._op == "whilelabel") {
                    if (_instruction_set[n].second._result == _quad_table[i]._result) {
                        _instruction_set.push_back(std::make_pair("JUMP", _quad_table[i]));
                        _instruction_set.back().first =  _instruction_set.back().first + " " + std::to_string(n + 1);
                        line_count++;
                    }
                } else if (_instruction_set[n].first == "JUMPZ" && _instruction_set[n].second._op == "whilelabel") {
                        if (_instruction_set[n].second._result == _quad_table[i]._result) {
                            _instruction_set.push_back(std::make_pair("LABEL", _quad_table[i]));
                            _instruction_set[n].first =  _instruction_set[n].first + " " + std::to_string(_instruction_set.size());
                            line_count++;
                        }
                }
            }
        }
        else if (_quad_table[i]._op == "scan") {
            auto ids = _IDs.at(_quad_table[i]._oprnd1);
            for (auto it = ids.rbegin(); it != ids.rend(); it++) {
                _instruction_set.push_back(std::make_pair("STDIN", _quad_table[i]));
                _instruction_set.push_back(std::make_pair("POPM " + std::to_string(*it), _quad_table[i]));
                line_count += 2;
            }
        }
        else if (_quad_table[i]._op == "print") {
            // _instruction_set.push_back(std::make_pair("PUSHM " + std::to_string(_quad_table[i]._oprnd1), _quad_table[i]));
            auto symbol_entry = _symbol_table.get_symbol_entry(_quad_table[i]._oprnd1);
            if (symbol_entry.second.second._data_type != SymbolDataType:: TEMP) {
                _instruction_set.push_back(std::make_pair("PUSHM " + std::to_string(_quad_table[i]._oprnd1), _quad_table[i]));
                ++line_count;
            }
            _instruction_set.push_back(std::make_pair("STDOUT", _quad_table[i]));
            ++line_count;
        }
    }

    for (int i = 1; i <= _instruction_set.size(); i++) {
        out_file << std::to_string(i) << "\t" << _instruction_set[i-1].first << '\n';
    }

    _symbol_table.print_symbol_to_file(out_file);
    out_file.close();
    return true;
}

bool LR_Parser::parse_to_outfile(string& output_file_name) {
    // open parse_log and output file
    ofstream parse_log_file("./parse_log/" + output_file_name, std::ios::trunc);
    ofstream out_file("./output/" + output_file_name, std::ios::trunc);

    // initialize transition count and program line count used for debugging
    int transition_count = 0;

    // if output file successfully opened
    if (parse_log_file.is_open()) {
        parse_log_file << "compiling file: "<< this->_input_file_name << "...\n" << std::endl;
        cout << "\ncompiling file: "<< this->_input_file_name << "...\n";

        // loop until accepting state or error
        while(true) {
            // initialize current state as top of stack state
            int curr_state = _lr_parser_stack.top().second;

            // get incoming token from lexer
            Token token = _lexer.get_next_token();

            // get token details
            TokenType token_type = token.type;
            string token_type_str = token.type_str;
            string incoming_token = token.lexeme;

            // if token type is IDENTIFIER or INTEGER, (and not "true", or "false"), generalize the lexeme to the token type name
            if (token_type == TokenType::IDENTIFIER || token_type == TokenType::INTEGER) {
                if (incoming_token != "true" && incoming_token != "false" ) {
                    incoming_token = token_type_str;
                }
            }
            // print transition details
            parse_log_file << "transition number: [ " << transition_count << " ]" << std::endl;
            this->print_current_stack_to_outfile(parse_log_file);
            this->print_current_stack_frames_to_outfile(parse_log_file);
            token.print_token_to_outfile(parse_log_file);

            // get next action from lr state table:
            //      row:    curr_state
            //      column: incoming token
            const string next_action = _lr_parser_table.get_next_action(curr_state, incoming_token);

            // if next action is ACC, break
            if (next_action == "ACC") {
                // print accept details
                parse_log_file << "INPUT ACCEPTED" << std::endl;

                break;
            }
            // if next action is empty, error
            else if (next_action.empty()) {
                // print verbose message about the error to file
                parse_log_file << "\nno action found from state: ["<< std::to_string(curr_state) << "] with the input: \"" << incoming_token << "\" ..." << std::endl;

                // print verbose message about the error to terminal
                cout << "\nPARSING ERROR. Invalid input string." << std::endl;
                cout << "   -> no action found from state: ["<< std::to_string(curr_state) << "] with the input: \"" << incoming_token << "\" ..." << std::endl << std::endl;
                cout << "Check ouput/" << output_file_name  << " - transition number: " << transition_count << " for more details." << std::endl << std::endl;

                return false;
            }
            // next action is valid action and not ACC
            else {
                // determine action type
                const char next_action_identifier = next_action[0];

                // if action is reduce
                if (next_action_identifier == 'R') {
                    // retrieve values to pop from stack from REDUCE_DIRECTORY in _lr_parser_table
                    auto reduce_entry = _lr_parser_table.get_reduce(next_action);
                    
                    // error handling
                    if (reduce_entry.first == "") {
                        // print error and exit program
                        cout << "Error reducing: " << next_action << "\n";
                        cout << "Exiting program...";
                        exit(1);
                    }

                    // print reducing details
                    parse_log_file << "Reducing: " << reduce_entry.first << " =>"; 
                    for (auto it = reduce_entry.second.rbegin(); it != reduce_entry.second.rend(); it++) {
                        parse_log_file << " " << *it;
                    }
                    parse_log_file << std::endl;

                    // determine if we are in <Opt Declaration List> or not
                    // this will later be used to determine if symbols should be added to symbol table or not
                    if (reduce_entry.first == "<Qualifier>") {
                        in_opt_decl_list = true;
                        parse_log_file << "in declaration list...\n";

                        // determine if we are in a integer <Declaration>
                        if (reduce_entry.second[0] == "int") {
                            in_int_decl = true;
                            parse_log_file << "in int declaration ...\n";
                        // or in a boolean <Declaration>
                        } else if (reduce_entry.second[0] == "boolean") {
                            in_bool_decl = true;
                            parse_log_file << "in int declaration ...\n";
                        }
                    }
                    // determine end of int and boolean declaration
                    else if (reduce_entry.first == "<Declaration>") {
                        // end of int declaration
                        if (in_int_decl) {
                            in_int_decl = false;
                            parse_log_file << "end of int declaration...\n";
                        } else if (in_bool_decl) {
                            in_int_decl = false;
                            parse_log_file << "end of bool declaration...\n";
                        }
                    }
                    // determine end of identifiers declaration
                    else if (reduce_entry.first == "<Opt Declaration List>") {
                        in_int_decl = false;
                        in_bool_decl = false;
                        in_opt_decl_list = false;
                        parse_log_file << "end declaration list...\n";
                    }

                    // pop reduce entry rhs from stack and store the popped values memory addresses
                    this->pop_reduce_rhs_from_stack(reduce_entry.second);
                    auto popped_memory_addresses = this->pop_reduce_rhs_from_frame_stack(reduce_entry.second);

                    // push reduce entry lhs to stack and generate quad if necessary
                    this->push_reduce_lhs_to_stack(reduce_entry.first);
                    this->push_reduce_lhs_to_frame_stack_and_generate_quad(out_file, next_action, reduce_entry.first, popped_memory_addresses, incoming_token, token.lexeme);
                }
                // if action is shift
                else {
                    // translate string integer to int
                    const int next_state = std::stoi(next_action);
 
                    // print shifting details
                    parse_log_file << "Shifting: \"" << incoming_token << "\", next state: " << next_state << "\n";

                    // shift pair<incoming_token, next_state> to stack
                    _lr_parser_stack.push(std::make_pair(incoming_token, next_state));

                    // if incoming token is an identifier, we need to refer to the symbol table
                    if (incoming_token == "IDENTIFIER") {
                        // retrieve memory address of incoming token
                        auto mem_addr = _symbol_table.get_address(token.lexeme);

                        // if we are in <Opt Declaration List>, add new symbols to symbol tables
                        if (in_opt_decl_list) {
                            // if symbol exists already, then throw redefinition error
                            if (mem_addr != 0) {
                                parse_log_file << "\nIDENTIFIER: \"" + token.lexeme + "\" IS ALREADY DEFINED\n";
                                parse_log_file << "Exiting Program...\n\n";

                                cout << "\nIDENTIFIER: \"" + token.lexeme + "\" IS ALREADY DEFINED\n";
                                cout << "Exiting Program...\n\n";
                                exit(1);
                            }
                            // if symbol does not exists, add symbol to symbol table and get address
                            // then push StackFrame with address to stack
                            else {
                                if (in_int_decl) {
                                    auto new_symbol_table_entry_addr = _symbol_table.set_address(token.lexeme, DataType(SymbolDataType::INTEGER, "INTEGER"));
                                    _lr_parser_frame_stack.push(StackFrame(next_state, incoming_token, new_symbol_table_entry_addr));
                                } else if (in_bool_decl) {
                                    auto new_symbol_table_entry_addr = _symbol_table.set_address(token.lexeme, DataType(SymbolDataType::BOOLEAN, "BOOLEAN"));
                                    _lr_parser_frame_stack.push(StackFrame(next_state, incoming_token, new_symbol_table_entry_addr));
                                }                               
                            }
                        } 
                        // if in body of program, each identifier should be present in the symbol table
                        else {
                            // if symbol does not exists, throw error
                            if (mem_addr == 0) {
                                parse_log_file << "\nIDENTIFIER: \"" + token.lexeme + "\" NOT DEFINED\n";
                                parse_log_file << "Exiting Program...\n\n";

                                cout << "\nIDENTIFIER: \"" + token.lexeme + "\" NOT DEFINED\n";
                                cout << "Exiting Program...\n\n";
                                exit(1);
                            } 
                            // if symbol exists, add stack frame with address
                            else {
                                _lr_parser_frame_stack.push(StackFrame(next_state, incoming_token, mem_addr, token.lexeme));
                            }
                        }
                    } else if (incoming_token == "INTEGER") {
                        _lr_parser_frame_stack.push(StackFrame(next_state, incoming_token, token.lexeme));
                    } else {
                        // push StackFrame without addr
                        _lr_parser_frame_stack.push(StackFrame(next_state, incoming_token));
                    }

                    // pop incoming token from lexer
                    _lexer.pop_front();
                }
            }
            parse_log_file << std::endl;

            transition_count++;
        }
    }

    // print success message to output file
    parse_log_file << "\n\nsuccessfully compiled input. input is valid.";

    // print success message to terminal
    cout << "successfully compiled input. input is valid." << std::endl << std::endl;
    cout << "Check ouput/" << output_file_name  << " for more details." << std::endl << std::endl;

    // close file
    parse_log_file.close();
    out_file.close();

    return true;
};

void LR_Parser::pop_reduce_rhs_from_stack(const vector<string>& reduce_entry_rhs) {
    for (int i = 0; i < reduce_entry_rhs.size(); i++) {
        // get top of stack symbol
        auto top_of_stack_symbol = _lr_parser_stack.top().first;
        
        // get lhs symbol
        auto symbol = reduce_entry_rhs[i];

        // if top of stack symbol and current reduce entry lhs symbol is the same, pop
        if (top_of_stack_symbol == symbol) {
            _lr_parser_stack.pop();
        } else if (symbol == "<Conditional Jump>") {
            continue;
        }
        else {
            cout << "Error reducing. Reduce value mismatch.\n";
            exit(1);
        }
    }
};

vector<StackFrame> LR_Parser::pop_reduce_rhs_from_frame_stack(const vector<string>& reduce_entry_rhs) {
    vector<StackFrame> popped_stack_frames;

    for (int i = 0; i < reduce_entry_rhs.size(); i++) {
        // get top of stack symbol
        auto top_of_stack_symbol = _lr_parser_frame_stack.top()._symbol;
        auto top_of_stack_mem_addr = _lr_parser_frame_stack.top()._mem_addr;

        // get rhs symbol
        auto symbol = reduce_entry_rhs[i];

        // if top of stack symbol and current reduce entry lhs symbol is the same, pop
        if (top_of_stack_symbol == symbol) {
            popped_stack_frames.push_back(_lr_parser_frame_stack.top());
            _lr_parser_frame_stack.pop();
        } else if (symbol == "<Conditional Jump>") {
            continue;
        }
        else {
            cout << "Error reducing. Reduce value mismatch.\n\n";
            exit(1);
        }
    }

    return popped_stack_frames;
};

void LR_Parser::push_reduce_lhs_to_stack(const string& reduce_entry_lhs) {
    // get top of stack state
    auto curr_state = _lr_parser_stack.top().second;
    
    // get next state from GOTO section of state transition table
    auto next_state = stoi(_lr_parser_table.get_next_goto(curr_state, reduce_entry_lhs));
    
    _lr_parser_stack.push(std::make_pair(reduce_entry_lhs, next_state));
};

void LR_Parser::push_reduce_lhs_to_frame_stack_and_generate_quad(ofstream& out_file, const string& next_action, const string& reduce_entry_lhs, vector<StackFrame>& rhs_stack_frames, const string& opt_incoming_token, const string& opt_lexeme) {
    // get top of stack state
    auto curr_state = _lr_parser_frame_stack.top()._state;

    // get next state from GOTO section of state transition table
    auto next_state = stoi(_lr_parser_table.get_next_goto(curr_state, reduce_entry_lhs));

    // R9:  <IDs> => <Identifier>
    if ( next_action == "R9" && !in_opt_decl_list ) {
        auto result_address = this->makequad("ids", rhs_stack_frames[0]._mem_addr, 0);
        _IDs.insert(make_pair(result_address, vector<size_t>{rhs_stack_frames[0]._mem_addr}));
        _lr_parser_frame_stack.push(StackFrame(next_state, reduce_entry_lhs, result_address));
    }
    // R10: <IDs> => <Identifier>, <IDs>
    else if ( next_action == "R10" && !in_opt_decl_list ) {
        // auto result_address = this->makequad("ids", rhs_stack_frames[0]._mem_addr, rhs_stack_frames[2]._mem_addr);
        try {
            auto it = _IDs.find(rhs_stack_frames[0]._mem_addr);
            if (it != _IDs.end() && rhs_stack_frames[2]._mem_addr != 0) {
                _IDs.at(it->first).push_back(rhs_stack_frames[2]._mem_addr);
            }
        } catch (const std::out_of_range& e) {
            cout << "Caught exception: " << e.what() << std::endl;
        }

        _lr_parser_frame_stack.push(StackFrame(next_state, reduce_entry_lhs, rhs_stack_frames[0]._mem_addr));
    }
    // R21: <Assign> => <Identifier> = <Expression>
    else if ( next_action == "R21" ) {
        // generate quad
        this->makequad("=", rhs_stack_frames[1]._mem_addr, rhs_stack_frames[3]._mem_addr);
        _lr_parser_frame_stack.push(StackFrame(next_state, reduce_entry_lhs, 0));
    }
    // R22: <If> => if ( <Condition> )
    else if ( next_action == "R22" ) {
        // generate quad
        auto result_address = this->makequad("ifjumpz", 0, 0);
        _lr_parser_frame_stack.push(StackFrame(next_state, reduce_entry_lhs, result_address));
    }
    // R23: <IfElse> => <If> <Statement> else
    else if ( next_action == "R23" ) {
        // generate quad
        auto result_address = this->makequad("jump", 0, 0);
        this->makequad("iflabel", rhs_stack_frames[2]._mem_addr, 0);
        _lr_parser_frame_stack.push(StackFrame(next_state, reduce_entry_lhs, result_address));
    }
    // R26: <Print> => put ( <Expression> );
    else if ( next_action == "R26" ) {
        // if (_symbol_table.get_address(rhs_stack_frames[2]._mem_addr)._data_type != SymbolDataType::TEMP) {
        //     this->_quad_table.push_back(QuadRecord("printpush", 0, 0, rhs_stack_frames[2]._mem_addr));
        // }
        this->makequad("print", rhs_stack_frames[2]._mem_addr, size_t(0) );
        _lr_parser_frame_stack.push(StackFrame(next_state, reduce_entry_lhs, 0));
    }
    // R27: <Scan> => get ( <IDs> );
    else if ( next_action == "R27" ) {
        // for (auto& elem : _IDs.at(rhs_stack_frames[2]._mem_addr)) {
        //     cout << std::to_string(elem) << '\n';
        // }
        this->makequad("scan", rhs_stack_frames[2]._mem_addr, size_t(0) );
        _lr_parser_frame_stack.push(StackFrame(next_state, reduce_entry_lhs, 0));
    }
    // R28: <While> => while ( <Condition> )
    else if ( next_action == "R28" ) {
        auto result_address = this->makequad("whilelabel", 0, size_t(0) );
        _lr_parser_frame_stack.push(StackFrame(next_state, reduce_entry_lhs, result_address));
    }
    // R29: <Condition> => <Expressions> <Relop> <Expression>
    else if ( next_action == "R29" ) {
        this->makequad(rhs_stack_frames[1]._opt_lexeme, rhs_stack_frames[2]._mem_addr, rhs_stack_frames[0]._mem_addr );
        _lr_parser_frame_stack.push(StackFrame(next_state, reduce_entry_lhs, 0));
    }
    // R30: <Relop> => ==
    else if ( next_action == "R30" ) {
        _lr_parser_frame_stack.push(StackFrame(next_state, reduce_entry_lhs, 0, "=="));
    }
    // R31: <Relop> => ^=
    else if ( next_action == "R31" ) {
        _lr_parser_frame_stack.push(StackFrame(next_state, reduce_entry_lhs, 0, "^="));
    }
    // R32: <Relop> => >
    else if ( next_action == "R32" ) {
        _lr_parser_frame_stack.push(StackFrame(next_state, reduce_entry_lhs, 0, ">"));
    }
    // R33: <Relop> => <
    else if ( next_action == "R33" ) {
        _lr_parser_frame_stack.push(StackFrame(next_state, reduce_entry_lhs, 0, "<"));
    }
    // R34: <Relop> => =>
    else if ( next_action == "R34" ) {
        _lr_parser_frame_stack.push(StackFrame(next_state, reduce_entry_lhs, 0, "=>"));
    }
    // R35: <Relop> => =<
    else if ( next_action == "R35" ) {
        _lr_parser_frame_stack.push(StackFrame(next_state, reduce_entry_lhs, 0, "=<"));
    }
    // R36: <Expression> => <Expression> + <Term>
    else if ( next_action == "R36" ) {
        // if (rhs_stack_frames[0]._mem_addr)
        auto result_address = this->makequad("+", rhs_stack_frames[2]._mem_addr, rhs_stack_frames[0]._mem_addr);
        _lr_parser_frame_stack.push(StackFrame(next_state, reduce_entry_lhs, result_address));
    }
    // R37: <Expression> => <Expression> - <Term>
    else if ( next_action == "R37" ) {
        auto result_address = this->makequad("-", rhs_stack_frames[2]._mem_addr, rhs_stack_frames[0]._mem_addr);
        _lr_parser_frame_stack.push(StackFrame(next_state, reduce_entry_lhs, result_address));
    }
    // R37: <Expression> => <Term>
    else if ( next_action == "R38" ) {
        _lr_parser_frame_stack.push(StackFrame(next_state, reduce_entry_lhs, rhs_stack_frames[0]._mem_addr));
    }
    // R39: <Term> => <Term> * <Factor>
    else if ( next_action == "R39" ) {
        auto result_address = this->makequad("*", rhs_stack_frames[2]._mem_addr, rhs_stack_frames[0]._mem_addr);
        _lr_parser_frame_stack.push(StackFrame(next_state, reduce_entry_lhs, result_address));
    }
    // R40: <Term> => <Term> / <Factor>
    else if ( next_action == "R40" ) {
        auto result_address = this->makequad("/", rhs_stack_frames[2]._mem_addr, rhs_stack_frames[0]._mem_addr);
        _lr_parser_frame_stack.push(StackFrame(next_state, reduce_entry_lhs, result_address));
    }
    // R41: <Term> => <Factor>
    else if ( next_action == "R41" ) {
        _lr_parser_frame_stack.push(StackFrame(next_state, reduce_entry_lhs, rhs_stack_frames[0]._mem_addr));
    }
    // R42: <Term> => - <Primary>
    else if ( next_action == "R42" ) {
        _lr_parser_frame_stack.push(StackFrame(next_state, reduce_entry_lhs, rhs_stack_frames[0]._mem_addr));
    }
    // R43: <Term> => <Primary>
    else if ( next_action == "R43" ) {
        _lr_parser_frame_stack.push(StackFrame(next_state, reduce_entry_lhs, rhs_stack_frames[0]._mem_addr));
    }
    // R44: <Term> => <Identifier>
    else if ( next_action == "R44" ) {
        _lr_parser_frame_stack.push(StackFrame(next_state, reduce_entry_lhs, rhs_stack_frames[0]._mem_addr));
    }
    // R45: <Primary> => <Integer>
    else if ( next_action == "R45" ) {
        auto temp = _symbol_table.get_temp_address();
        _symbol_table.set_address_entry(temp, rhs_stack_frames[0]._opt_lexeme, DataType(SymbolDataType::INT_VAL, rhs_stack_frames[0]._opt_lexeme));
        _lr_parser_frame_stack.push(StackFrame(next_state, reduce_entry_lhs, temp));
    }
    // R46: <Primary> => ( <Expression> )
    else if ( next_action == "R46") {
        _lr_parser_frame_stack.push(StackFrame(next_state, reduce_entry_lhs, rhs_stack_frames[1]._mem_addr));
    }
    // R50: <IfThen> => <If> <Statement> endif
    else if ( next_action == "R49") {
        auto result_address = this->makequad("iflabel", rhs_stack_frames[2]._mem_addr, 0);
        _lr_parser_frame_stack.push(StackFrame(next_state, reduce_entry_lhs, 0));
    }
    // R50: <IfElseThen> => <IfElse> <Statement> endif
    else if ( next_action == "R50") {
        auto result_address = this->makequad("label", rhs_stack_frames[2]._mem_addr, 0);
        _lr_parser_frame_stack.push(StackFrame(next_state, reduce_entry_lhs, 0));
    }
    // R52: <WhileThen> => <While> <Statement>
    else if ( next_action == "R52") {
        // auto result_address = this->makequad("jump", rhs_stack_frames[1]._mem_addr, 0);
        this->_quad_table.push_back(QuadRecord("whilejumpz", 0, 0, rhs_stack_frames[1]._mem_addr));
        _lr_parser_frame_stack.push(StackFrame(next_state, reduce_entry_lhs, 0));
    }
    else {
        _lr_parser_frame_stack.push(StackFrame(next_state, reduce_entry_lhs, 0));
    }
}

size_t LR_Parser::makequad(const string& op, size_t addr1, size_t addr2) {
    size_t temp_addr = 0;
    if (op == "=") {
        temp_addr = addr2;
        addr2 = 0;
    }
    else if (op == "print" || op == "scan") {
        temp_addr = 0;
    }
    else {
        temp_addr = _symbol_table.get_temp_address();
    }
    this->_quad_table.push_back(QuadRecord(op, addr1, addr2, temp_addr));
    return temp_addr;
}


void LR_Parser::print_current_stack_to_outfile(ofstream& parse_log_file) {
    // make a copy of the current parser stack
    stack<pair<string, int>> parser_stack_copy(this->_lr_parser_stack);

    // initialize stack string
    string stack_reversed;

    // begin printing stack
    parse_log_file << "current stack: ";

    // stack can only be iterated by popping. pop until empty and append popped value to stack string
    while(!parser_stack_copy.empty()) {
        // print reversed
        stack_reversed.append(std::to_string(parser_stack_copy.top().second));
        stack_reversed.append(" ");
        stack_reversed.append(parser_stack_copy.top().first);
        stack_reversed.append(" ");
        parser_stack_copy.pop();
    }

    parse_log_file << stack_reversed;
    parse_log_file << std::endl;
}

void LR_Parser::print_current_stack_frames_to_outfile(ofstream& parse_log_file) {
    stack<StackFrame> parser_frame_stack_copy(this->_lr_parser_frame_stack);
    string stack_with_frames_reversed;

    // begin printing stack
    parse_log_file << "current stack frames: ";

    while(!parser_frame_stack_copy.empty()) {
        // print reversed
        stack_with_frames_reversed.append("{ state: " + std::to_string(parser_frame_stack_copy.top()._state));
        stack_with_frames_reversed.append(", ");
        stack_with_frames_reversed.append("symbol: \"" + parser_frame_stack_copy.top()._symbol + "\"");
        stack_with_frames_reversed.append(", ");
        stack_with_frames_reversed.append("mem addr: " + std::to_string(parser_frame_stack_copy.top()._mem_addr));
        stack_with_frames_reversed.append(", ");
        stack_with_frames_reversed.append("opt lexeme: " + parser_frame_stack_copy.top()._opt_lexeme);
        stack_with_frames_reversed.append("}, ");
        parser_frame_stack_copy.pop();
    }

    parse_log_file << stack_with_frames_reversed;
    parse_log_file << std::endl;
}

void LR_Parser::print_quads() {
    cout << "\n\nprinting quad (" << std::to_string(_quad_table.size()) <<  "): \n";

    for (auto& elem : _quad_table) {
        elem.print_quad();
    }

    cout << "\n\n";
}

//    parse_log_file << stack_with_frames_reversed;

#endif // LR_PARSER_CPP