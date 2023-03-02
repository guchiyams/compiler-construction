#include "SymbolTable.hpp"

SymbolTable::SymbolTable() {
    table_.reserve(MAX_SYMBOLS);
    for (auto keyword : key_words) {
        this->insert_(keyword, "KEYWORD");
    }
    for (auto num : nums) {
        this->insert_(string(num), "NUMBER");
    }
    for (auto separator : separators) {
        this->insert_(separator, "SEPARATOR");
    }
    for (auto op : ops) {
        this->insert_(op, "OPERATOR");
    }
}

bool SymbolTable::lookup_(string lexeme, SymbolTableEntry& entry) {
    // search for lexeme
    auto find = table_.find(lexeme);
    // if not found return 
    if (find == table_.end())
    {
        return false; 
    }
    // if found, update entry to found SymbolTableEntry
    else {
        entry = find->second;
        return true;
    }
};

// void SymbolTable::insert_(string lexeme, string tokenType)