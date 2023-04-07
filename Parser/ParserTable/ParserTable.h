#ifndef PARSER_TABLE_H
#define PARSER_TABLE_H

#include <iostream>
#include <stdexcept>
#include <string>
#include <unordered_map>
#include <vector>

using std::cout;
using std::string;
using std::unordered_map;
using std::vector;

class PredictiveParserTable {

    public:
        PredictiveParserTable() = default;
        ~PredictiveParserTable() = default;

        vector<string> get_next_production(string lhs, string incoming_token);

    private:
        static const vector<vector<vector<string>>> PREDICTIVE_PARSER_TABLE;
        static const unordered_map<string, int> LEXEME_TO_COL;
        static const unordered_map<string, int> NONTERMINAL_TO_ROW;
};

#endif // PARSER_TABLE_H