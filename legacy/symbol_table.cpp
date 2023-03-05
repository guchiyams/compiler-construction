#ifndef SYMBOLTABLE_C
#define SYMBOLTABLE_C

#include <string>
#include <iostream>


struct Token{
	
    const std::string key_word[28] = {"if", "else", "while" , "do","break",
                                "continue","int","double","float","return",
                                "char","case","short","typedef","switch",
                                "unsigned","void","static","struct","sizeof","long",
                                "volatile","typedef","enum","const","union","extern","bool"};

    const char num[10] = {'0','1','2','3','4','5','6','7','8','9'};
 
    const char seperators[6] = { '(', ')', '[', ']' ,'{', '}' };

    const char ops[7] = {'+','-','=','>','<','*','/'};
};

#endif

// auto
// bool break
// case catch char class const constexpr continue
// default delete do double
// else enum explicit export
// false float for freind
// goto
// if inline int
// long
// namespace new noexcept not nullptr 
// operator or
// private public
// requires return
// short signed static struct switch
// template this throw true try typedef typeid typename
// union unsigned using
// virtual void
// while
// xor

// IN  IF_I KEYWORD
// IN  IF_F KEYWORD
// END IF  KEYWORD

// IN ELSE_E KEYWORD
// 

// IN C_ KEYWORD

// IN 