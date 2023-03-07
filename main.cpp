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
#include "LexicalAnalyzer.cpp"

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

    vector<Token> tokens = lexicalAnalyzer(input_file_name, output_file_name);

    return 0;
}

