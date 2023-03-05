#include "lexer.h"
#include <iostream>
using namespace std;



Lexer::Lexer(){ 

}

Lexer::Lexer( string incomingStr)
{
    setString(incomingStr);
}

Lexer::~Lexer()
{
    
}

void Lexer::setString(string incomingStr){
    str = incomingStr;
}

bool Lexer::isSeparator(int index){

	int n = sizeof(t.seperators) / sizeof(t.seperators[0]);
    for (int i = 0; i < n; i++)
    {
        if (this->words[index] == string(1, t.seperators[i]) )
        {
            return true;
        }   
    }
    return false;
}




bool Lexer::validIdentifier(int index){
    const char* checkString = this->words[index].c_str(); //extracting the string
    //first we check if it match any reserve words
    //check first letter
    if (isdigit(checkString[0]) || checkString[0] == '-')
    {
        return false;
    }
    int n = sizeof(t.key_word) / sizeof(t.key_word[0]);
    for (int i = 0; i < n; i++)
    {
        if (t.key_word[i].compare(checkString) == 0)
        {
            return false;
        }   
    }
    
    //checkign the remaining characters
    //if any character in the string is not number, letter or underscore.
    // loop will return false
    int count = 1;
    int end = strlen(checkString);
    int size = sizeof(t.ops) / sizeof(t.ops[0]);
    while(count < end){
    
        for (int i = 0; i < size; i++)
        {
            if (checkString[count] == t.ops[i])
            {
                return false;
            }
        }
        count++;
    }
    return true;
}


//not sure yet. 
bool Lexer::isOperator(int index){
    int n = sizeof(t.ops) / sizeof(t.ops[0]);
    for (int i = 0; i < n; i++)
    {
        if (this->words[index] == string(1, t.ops[i]))
        {
            return true;
        }
        
    }
    
    return false;
}


bool Lexer::isKeyword(int index){
    int n = sizeof(t.key_word) / sizeof(t.key_word[0]);
    for (int i = 0; i < n; i++)
    {
        if (this->words[index] == t.key_word[i])
        {
            return true;
        }
    }
    return false;
}

bool Lexer::isNumber(int index){
  

    string str = this->words[index].c_str();
    for (char c : str)
    {
        if (!isdigit(c))
        {
            return false;
        }
        
    }
    return true;
    

}

string Lexer::getString(){
    return this->str;
}

    


/*
Implemenation of parser in 
*/

void Lexer::parse(){
    
    //cut the string up
    stringstream ss(this->str);
    while (ss >> this->word)
    {
       this->words.push_back(this->word);
    }

    //check every word
    int index = 0;
    int size = this->words.size();
    while(index < size){
        if (this->isKeyword(index))
        {
		    cout << this->words[index] << " \tIS A KEYWORD" << endl;
        }
        if (this->isNumber(index))
        {
		    cout << this->words[index] << " \tIS A NUMBER" << endl;
        }
        if (this->isOperator(index))
        {
            cout << this->words[index] << " \tIS A OPERATOR" << endl;
        }
        if (this->isSeparator(index))
        {
            cout << this->words[index] << " \tIS A SEPARATOR" << endl;
        }else if (this->validIdentifier(index) && !this->isOperator(index))
        {
            cout << this->words[index] << " \tIS A IDENTIFER" << endl;
        }
        index++;
    }

}
