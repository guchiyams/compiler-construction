/*
Project 1 : Lexical Analyzer
Professor : Sijie Shang
Class : CPSC 323
Team : 
    * Hoang Nguyen ( Kyle )
    * Ginya
*/
#include "LexicalAnalyzer.cpp"

int main()
{
    string input = "if(x > y){x=0;}";

    vector<Token> tokens = lexicalAnalyzer(input);

    return 0;
}

