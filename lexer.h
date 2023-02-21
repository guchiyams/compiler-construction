#ifndef LEXER_H
#define LEXER_H

class Lexer
{
private:
    
public:
    Lexer(/* args */);
    ~Lexer();

    bool isPunctuator(char ch);
    bool validIdentifier (char *str);
    bool isOperator (char ch);
    bool isKeyword(char * str);
    bool isNumber(char* str);
    bool isSeprator(char* ch);


    char* subString(char* realStr, int l , int r);
    void parse(char* str);

};
#endif // !LEXER_H