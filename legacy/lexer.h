#ifndef LEXER_H
#define LEXER_H

#include "iostream"
#include "symbol_table.cpp"
#include <string>
#include <cstring>
#include <sstream>
#include "vector"
#include "algorithm"
using namespace std;

class Lexer
{
private:
    string str;
    Token t;
    vector<string> words;
    string word;
public:
    Lexer(string incomingStr);
    Lexer();
    ~Lexer();

    void setString(string incomingStr);

    //bool isPunctuator(int index);
    bool validIdentifier (int index);
    bool isOperator(int index);
    bool isKeyword(int index);
    bool isNumber(int index);
    bool isSeparator(int index);


    string getString();
    char* subString(char* realStr, int l , int r);
    void parse();

};
#endif // !LEXER_H
