#ifndef PREDICTIVE_PARSER_H
#define PREDICTIVE_PARSER_H

#include <iostream>
#include <fstream>
#include <stack>
#include <string>
#include <unordered_map>
#include <unordered_set>

#include "../Lexer/Lexer.cpp"
#include "./ParserTable/ParserTable.cpp"

using std::cout;
using std::ofstream;
using std::stack;
using std::string;
using std::unordered_map;
using std::unordered_set;

class PredictiveParser {
    public:
        PredictiveParser() = default;
        PredictiveParser(string& input_file_name);
        ~PredictiveParser() = default;

        // getters
        Lexer get_lexer() const;

        // modifiers
        void push_to_stack(vector<string>& rhs);

        // parsers
        bool parse_to_outfile(string& output_file_name);

        // print helpers
        void print_current_stack_to_outfile(ofstream& out_file);
        void print_production(ofstream& out_file, string& lhs, vector<string> rhs);

    private:
        stack<string> _parser_stack;
        string input_file_name;
        Lexer _lexer;
        PredictiveParserTable _parser_table;
        static const unordered_set<string> TERMINAL_SET;
};

#endif // PREDICTIVE_PARSER_H