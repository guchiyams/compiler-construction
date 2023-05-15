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

        const vector<string> get_next_step(string lhs, string incoming_token) const;

    private:
        static const unordered_map<string, int> NONTERMINAL_TO_ROW;
        static const unordered_map<string, int> TERMINAL_TO_COL;
        static const vector<vector<vector<string>>> PREDICTIVE_PARSER_TABLE;
};

#endif // PARSER_TABLE_H