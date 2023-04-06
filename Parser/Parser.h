#ifndef PREDICTIVE_PARSER
#define PREDICTIVE_PARSER

#include <iostream>
#include <string>
#include <unordered_map>

#include "../Lexer/Lexer.h"
#include "./ParserTable/ParserTable.h"

using std::cout;
using std::string;
using std::unordered_map;

class PredictiveParser {
    public:
        PredictiveParser() = default;
        PredictiveParser(string& input_file_name, string& output_file_name);
        
    private:
        Lexer _lexer;
        PredictiveParserTable _table;

};

#endif // PREDICTIVE_PARSER