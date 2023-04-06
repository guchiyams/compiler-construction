#include "../Lexer/Lexer.cpp"
#include "./Parser.h"

PredictiveParser::PredictiveParser(string& input_file_name, string& output_file_name) {
    // initialize lexer with input and output files
    _lexer = Lexer (input_file_name, output_file_name);
};