/*
Project 1 : Lexical Analyzer
Professor : Sijie Shang
Class : CPSC 323
Team : 
    * Hoang Nguyen ( Kyle )
    * Yamato Eguchi
*/

#include <iostream>
#include <fstream>

// #include "./Lexer/Lexer.cpp"
#include "./Parser/Parser.cpp"
#include "./Parser/ParserTable/ParserTable.cpp"

using std::cout;

int main(int argc, char* argv[])
{
    if (argc > 2) {
        cout << "Too many arguments. Aborting..." << std::endl;
        abort();
    } else if (argc == 1) {
        cout << "Missing paramter: input_[01 | 02 | 03]. Aborting..." << std::endl;
        abort();
    }

    const string INPUT = argv[1];
    string input_file_name = "";
    string output_file_name = "";
    
    if (INPUT == "input_01") {
        input_file_name = "input_01.txt";
        output_file_name = "01_output.txt";
    }
    else if (INPUT == "input_02") {
        input_file_name = "input_02.txt";
        output_file_name = "02_output.txt";
    }
    else if (INPUT == "input_03") {
        input_file_name = "input_03.txt";
        output_file_name = "03_output.txt";
    }
    else {
        cout << "Invalid argument. Aborting..." << std::endl;
        abort();
    }

    PredictiveParser parser(input_file_name);
    parser.parse_to_outfile(output_file_name);

    // Token token = parser.get_lexer().get_next_token();
    // token.print_token();

    // cout << std::endl;

    // parser.get_lexer().print_tokens();

    // Lexer lexical_analyzer(input_file_name, output_file_name);
    // lexical_analyzer.print_tokens();

    // cout << std::endl;
    // cout << std::endl;

    // Token token = lexical_analyzer.get_next_token();
    // token.print_token();
    // Token token1 = lexical_analyzer.get_next_token();
    // token1.print_token();
    // Token token2 = lexical_analyzer.get_next_token();
    // token2.print_token();

    // cout << std::endl;
    // cout << std::endl;

    // lexical_analyzer.print_tokens();

    /*
        // initialize PredictiveParser
        PredictiveParser parser(input_file, output_file);
        parser.parse_to_output_file();
    */



    return 0;
};
