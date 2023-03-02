#ifndef SYMBOLTABLE_H
#define SYMBOLTABLE_H

#define MAX_SYMBOLS 100

#include <iostream>
#include <string>
#include <unordered_map>

using std::cout;
using std::pair;
using std::string;
using std::unordered_map;

struct SymbolTableEntry {
    string lexeme;
    string tokenType;

    void print() {
        cout << "Lexeme: " << lexeme << ", TokenType: " << tokenType << "\n";
    }
};

class SymbolTable {
    public:
        SymbolTable();

        bool lookup_(string lexeme, SymbolTableEntry& entry);
    private:
        std::unordered_map<string, SymbolTableEntry> table_;

        const string key_words[28] = {"if", "else", "while" , "do","break",
                                "continue","int","double","float","return",
                                "char","case","short","typedef","switch",
                                "unsigned","void","static","struct","sizeof","long",
                                "volatile","typedef","enum","const","union","extern","bool"}; 

        const string nums[10] = {"0", "1", "2", "3", "4", "5", "6", "7", "8", "9"};
        const string separators[6] = { "(", ")", "[", "]" ,"{", "}" };
        const string ops[7] = {"+","-","=",">","<","*","/"};

        void insert_(string lexeme, string tokenType)  {
            SymbolTableEntry entry;
            entry.lexeme = lexeme;
            entry.tokenType = tokenType;
            table_.insert(pair<string, SymbolTableEntry> (lexeme, entry));
        };
};

#endif