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
    }

    const string INPUT = argv[1];
    string file_name = "";

    if (INPUT == "input_01") file_name = "input_01.txt";
    else if (INPUT == "input_02") file_name = "input_02.txt";
    else if (INPUT == "input_03") file_name = "input_03.txt";
    else {
        cout << "Invalid input. Aborting..." << std::endl;
        abort();
    }

    std::ifstream file("./input/" + file_name);

    if (file.is_open()) {
        string line = "";
        while (std::getline(file, line)) {
            vector<Token> tokens = lexicalAnalyzer(line);
        }
    } else {
        cout << "Input file not open. Abortin..." << std::endl;
        abort();
    }

    return 0;
}

