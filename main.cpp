/*
Project 2 : Predictive Parser
Professor : Sijie Shang
Class : CPSC 323
Team : 
    * Yamato Eguchi
*/

#include <iostream>
#include <fstream>

#include "./Parser/Parser.cpp"
#include "./Parser/ParserTable/ParserTable.cpp"

using std::cout;

int main(int argc, char* argv[])
{
    if (argc > 2) {
        cout << "Too many arguments. Aborting..." << std::endl;
        exit(1);
    } else if (argc == 1) {
        cout << "Missing paramter: input_[01 | 02 | 03]. Aborting..." << std::endl;
        exit(1);
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
        exit(1);
    }

    PredictiveParser parser(input_file_name);
    parser.parse_to_outfile(output_file_name);

    return 0;
};
