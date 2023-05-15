#ifndef SYMBOL_TABLE_CPP
#define SYMBOL_TABLE_CPP

#include "./SymbolTable.h"

using std::make_pair;

SymbolTable::SymbolTable() {
    curr_addr_index = 0;
    _symbol_table = unordered_map<string, pair<size_t, DataType>>();
}

unordered_map<string, pair<size_t, DataType>>& SymbolTable::get_table() {
    return _symbol_table;
}

const size_t SymbolTable::get_address(const string& symbol) {
    auto it = _symbol_table.find(symbol);

    // if symbol is found, return symbol addr
    if (it != _symbol_table.end()) {
        return (*it).second.first;
    }

    return 0;
};

const DataType SymbolTable::get_address(const size_t& mem_addr) {
    for (auto& elem : _symbol_table) {
        if (elem.second.first == mem_addr) {
            return elem.second.second;
        }
    }
    return DataType();
}

const pair<string, pair<size_t, DataType>> SymbolTable::get_symbol_entry(const string& symbol) {
    auto found = _symbol_table.find(symbol);
    if (found != _symbol_table.end())
        return *found;
        // return true;
    else
        // return false;
        return make_pair("", make_pair(0, DataType()));
}

const pair<string, pair<size_t, DataType>> SymbolTable::get_symbol_entry(const size_t& mem_addr) {
    for (auto& elem : _symbol_table) {
        if (elem.second.first == mem_addr) {
            return elem;
            // return true;
        }
    }
    return make_pair("", make_pair(0, DataType()));
}

const size_t SymbolTable::set_address(const string& symbol, const DataType& data_type) {
    auto it = _symbol_table.find(symbol);

    // if symbol is found, overwrite
    if (it != _symbol_table.end()) {
        _symbol_table.insert(make_pair(symbol, make_pair(it->second.first, data_type)));
        // remove temp
        _symbol_table.erase(it);
    }

    // else if not found add to the symbol table
    size_t mem_addr = ++curr_addr_index + ADDR_STARTING_INDEX;
    _symbol_table.insert(make_pair(symbol, make_pair(mem_addr, data_type)));

    return mem_addr;
};

const size_t SymbolTable::set_address_entry(const size_t& mem_addr, const string& symbol, const DataType& data_type) {
    for (auto& elem : _symbol_table) {
        if (elem.second.first == mem_addr) {
            // create new
            _symbol_table.insert(make_pair(symbol, make_pair(mem_addr, DataType(SymbolDataType::INT_VAL, "INT_VAL"))));
            _symbol_table.erase(elem.first);
            return mem_addr;
        }
    }
    return 0;
}


const size_t SymbolTable::get_temp_address() {
    size_t mem_addr = ++curr_addr_index + ADDR_STARTING_INDEX;

    auto mem_addr_str = std::to_string(mem_addr);
    _symbol_table.insert(make_pair("TEMP" + mem_addr_str, make_pair(mem_addr, DataType(SymbolDataType::TEMP, "TEMP"))));

    return mem_addr;
};

const void SymbolTable::print_symbol_to_stdout() {
    // remove all temps
    // for (auto it = _symbol_table.begin(); it != _symbol_table.end(); it++) {
    //     // if (elem.second.second._data_type == SymbolDataType::TEMP) {
    //     cout << it->first << '\n';
    //     _symbol_table.erase(it);
    //     // }
    // }

    cout << "======== SYMBOL TABLE ========\n";
    // Determine the width of each column
    vector<size_t> column_widths(3, 0);
    column_widths[0] = string("MEM ADDR").length();
    column_widths[1] = string("ID").length();
    column_widths[2] = string("DATA TYPE").length();
    for (const auto& row : _symbol_table) {
        column_widths[0] = std::max(column_widths[0], std::to_string(row.second.first).length());
        column_widths[1] = std::max(column_widths[1], row.first.length());
        column_widths[2] = std::max(column_widths[2], row.second.second._data_type_str.length());
    }

    std::cout << "+-" << std::string(column_widths[0], '-') << "-+-"
              << std::string(column_widths[1], '-') << "-+-"
              << std::string(column_widths[2], '-') << "-+\n";
    std::cout << "|" << std::setw(column_widths[0] + 2) << std::left << "MEM ADDR"
              << "|" << std::setw(column_widths[1] + 2) << std::left << "ID"
              << "|" << std::setw(column_widths[2] + 2) << std::left << "DATA TYPE"
              << "|\n";
    std::cout << "+-" << std::string(column_widths[0], '-') << "-+-"
              << std::string(column_widths[1], '-') << "-+-"
              << std::string(column_widths[2], '-') << "-+\n";


    // Print the table data
    for (const auto& row : _symbol_table) {
        if (row.second.second._data_type != SymbolDataType::TEMP && row.second.second._data_type != SymbolDataType::INT_VAL) {
            std::cout << "|" << std::setw(column_widths[0] + 2) << std::left << std::to_string(row.second.first)
                    << "|" << std::setw(column_widths[1] + 2) << std::left << row.first
                    << "|" << std::setw(column_widths[2] + 2) << std::left << row.second.second._data_type_str
                    << "|\n";
        }
    }

    // Print the table footer
    std::cout << "+-" << std::string(column_widths[0], '-') << "-+-"
              << std::string(column_widths[1], '-') << "-+-"
              << std::string(column_widths[2], '-') << "-+\n\n";
}

const void SymbolTable::print_symbol_to_file(ofstream& out_file) {
    out_file << "\n\n======== SYMBOL TABLE ========\n";
    // Determine the width of each column
    vector<size_t> column_widths(3, 0);
    column_widths[0] = string("MEM ADDR").length();
    column_widths[1] = string("ID").length();
    column_widths[2] = string("DATA TYPE").length();
    for (const auto& row : _symbol_table) {
        column_widths[0] = std::max(column_widths[0], std::to_string(row.second.first).length());
        column_widths[1] = std::max(column_widths[1], row.first.length());
        column_widths[2] = std::max(column_widths[2], row.second.second._data_type_str.length());
    }

    out_file << "+-" << std::string(column_widths[0], '-') << "-+-"
              << std::string(column_widths[1], '-') << "-+-"
              << std::string(column_widths[2], '-') << "-+\n";
    out_file << "|" << std::setw(column_widths[0] + 2) << std::left << "MEM ADDR"
              << "|" << std::setw(column_widths[1] + 2) << std::left << "ID"
              << "|" << std::setw(column_widths[2] + 2) << std::left << "DATA TYPE"
              << "|\n";
    out_file << "+-" << std::string(column_widths[0], '-') << "-+-"
              << std::string(column_widths[1], '-') << "-+-"
              << std::string(column_widths[2], '-') << "-+\n";


    // Print the table data
    for (const auto& row : _symbol_table) {
        if (row.second.second._data_type != SymbolDataType::TEMP && row.second.second._data_type != SymbolDataType::INT_VAL) {
            out_file << "|" << std::setw(column_widths[0] + 2) << std::left << std::to_string(row.second.first)
                    << "|" << std::setw(column_widths[1] + 2) << std::left << row.first
                    << "|" << std::setw(column_widths[2] + 2) << std::left << row.second.second._data_type_str
                    << "|\n";
        }
    }

    // Print the table footer
    out_file << "+-" << std::string(column_widths[0], '-') << "-+-"
              << std::string(column_widths[1], '-') << "-+-"
              << std::string(column_widths[2], '-') << "-+\n\n";
}

# endif // SYMBOL_TABLE_CPP