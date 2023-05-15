/*
Project 2 : Predictive Parser
Professor : Sijie Shang
Class : CPSC 323
Team : 
    * Yamato Eguchi
*/

#include <iostream>
#include <fstream>

#include "./LL_Parser/LL_Parser.cpp"
#include "./LR_Parser/LR_Parser.cpp"

using std::cout;

int main(int argc, char* argv[])
{
    /* get user inputted arguments and error check */
    if (argc > 2) {
        cout << "Too many arguments. Exiting program..." << std::endl;
        exit(1);
    } else if (argc == 1) {
        cout << "Missing paramter: input_[01 | 02 | 03]. Exiting program..." << std::endl;
        exit(1);
    }

    /* get input file name and output file name */
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
        cout << "Invalid argument. Exiting program..." << std::endl;
        exit(1);
    }

    // intialize parser
    LR_Parser lr_parser(input_file_name);

    // compile
    lr_parser.compile(output_file_name);

    // print details to stdout
    lr_parser.get_symbol_table().print_symbol_to_stdout();
    lr_parser.print_quads();

    return 0;
};