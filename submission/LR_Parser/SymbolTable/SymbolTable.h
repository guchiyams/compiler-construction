#ifndef SYMBOL_TABLE_H
#define SYMBOL_TABLE_H

#include <iomanip>
#include <utility>
#include <string>
#include <unordered_map>
#include <vector>

using std::pair;
using std::unordered_map;
using std::string;
using std::vector;

enum class SymbolDataType {
    INTEGER,
    BOOLEAN,
    TEMP,
    INT_VAL,
    LABEL,
    NONE,
};

struct DataType {
    SymbolDataType _data_type;
    string _data_type_str;

    DataType() = default;
    DataType(SymbolDataType data_type, string data_type_str) : _data_type(data_type), _data_type_str(data_type_str) {};
};

class SymbolTable {
    public:
        SymbolTable();
        ~SymbolTable() = default;

        // get symbol table
        unordered_map<string, pair<size_t, DataType>>& get_table();

        // get address
        const size_t get_address(const string& symbol);
        const DataType get_address(const size_t& mem_addr);
        const pair<string, pair<size_t, DataType>> get_symbol_entry(const string& symbol);
        const pair<string, pair<size_t, DataType>> get_symbol_entry(const size_t& mem_addr);

        // set address
        const size_t set_address(const string& symbol, const DataType& data_type);
        const size_t set_address_entry(const size_t& mem_addr, const string& symbol, const DataType& data_type);
        
        // get temporary address
        const size_t get_temp_address();

        // printers
        const void print_symbol_to_stdout();
        const void print_symbol_to_file(ofstream& out_file);

    private:
        static const size_t ADDR_STARTING_INDEX = 2000;

        size_t curr_addr_index;
        unordered_map<string, pair<size_t, DataType>> _symbol_table;
};


# endif // SYMBOL_TABLE_H