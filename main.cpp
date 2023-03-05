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
    string input = "for(int i=0;i<5;i++){x=y-0.5; }";

    double _ = +.67;
    cout << _ << std::endl;

    vector<Token> tokens = lexicalAnalyzer(input);

    return 0;
}

