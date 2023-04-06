#ifndef PARSER_TABLE
#define PARSER_TABLE

#include <iostream>
#include <string>
#include <unordered_map>

using std::cout;
using std::string;
using std::unordered_map;

class PredictiveParserTable {

    public:
        PredictiveParserTable() = default;

    private:
        static const string PREDICTIVE_PARSER_TABLE[50][50][10];
        static const unordered_map<string, int> LEXEME_TO_COL;
        static const unordered_map<string, int> NONTERMINAL_TO_ROW;
};

#endif // PARSER_TABLE