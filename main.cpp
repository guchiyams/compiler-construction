/*
Project 1 : Lexical Analyzer
Professor : Sijie Shang
Class : CPSC 323
Team : 
    * Hoang Nguyen ( Kyle )
    * Yamato Eguchi
*/
#include "LexicalAnalyzer.cpp"

int main()
{
    string input_01 = "if(x > y){x=0;}";
    string input_02 = "while  (fahr < upper)   a = 23.00";
    string input_03 = "for (int i = 0; i < 3; i++) x = 2;";

    vector<Token> tokens = lexicalAnalyzer(input_02);

    return 0;
}

