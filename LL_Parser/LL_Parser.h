#ifndef PREDICTIVE_PARSER_H
#define PREDICTIVE_PARSER_H

#include <iostream>
#include <fstream>
#include <stack>
#include <string>
#include <unordered_map>
#include <unordered_set>

#include "../Lexer/Lexer.cpp"
#include "./LL_ParserTable/LL_ParserTable.cpp"

using std::cout;
using std::ofstream;
using std::stack;
using std::string;
using std::unordered_map;
using std::unordered_set;

class LL_Parser {
    public:
        LL_Parser() = default;
        LL_Parser(string& input_file_name);
        ~LL_Parser() = default;

        // getters
        Lexer get_lexer() const;

        // modifiers
        void push_list_to_stack(vector<string>& rhs);

        // parsers
        bool parse_to_outfile(string& output_file_name);

        // print helpers
        void print_current_stack_to_outfile(ofstream& out_file);
        void print_production(ofstream& out_file, string& lhs, vector<string> rhs);

    private:
        string _input_file_name;
        Lexer _lexer;
        stack<string> _parser_stack;
        PredictiveParserTable _parser_table;
        static const unordered_set<string> TERMINAL_SET;
};

#endif // PREDICTIVE_PARSER_H