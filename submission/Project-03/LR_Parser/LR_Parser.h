#ifndef LR_PARSER_H
#define LR_PARSER_H

#include <iostream>
#include <string>
#include <stack>
#include <vector>
#include <unordered_map>

#include "../Lexer/Lexer.cpp"
#include "./LR_ParserTable/LR_ParserTable.cpp"
#include "./SymbolTable/SymbolTable.cpp"

using std::stack;
using std::string;

struct StackFrame {
    int _state;
    string _symbol;
    size_t _mem_addr;
    string _opt_lexeme;

    StackFrame(const int& state, const string& symbol) :
        _state(state), _symbol(symbol), _mem_addr(0), _opt_lexeme("") {};
        
    StackFrame(const int& state, const string& symbol, const size_t& mem_addr) : 
        _state(state), _symbol(symbol), _mem_addr(mem_addr), _opt_lexeme("") {};

    StackFrame(const int& state, const string& symbol, const string& opt_lexeme) : 
        _state(state), _symbol(symbol), _mem_addr(0), _opt_lexeme(opt_lexeme) {};

    StackFrame(const int& state, const string& symbol, const size_t& mem_addr, const string& opt_lexeme) : 
        _state(state), _symbol(symbol), _mem_addr(mem_addr), _opt_lexeme(opt_lexeme) {};

    void print_stack_frame(ofstream& outfile) {
        outfile << " { state: " << _state << ", symbol: " << _symbol << ", mem addr: "
                << _mem_addr << ", opt lexem: " << _opt_lexeme << " } ";
    }
};

struct QuadRecord {
    string _op;
    size_t _oprnd1;
    size_t _oprnd2;
    size_t _result;

    QuadRecord() = default;
    QuadRecord(string op, size_t oprnd1, size_t oprnd2, size_t result) : _op(op), _oprnd1(oprnd1), _oprnd2(oprnd2), _result(result) {};  

    void print_quad() {
        cout << "[ " << _op << ", "
             << std::to_string(_oprnd1) << ", "
             << std::to_string(_oprnd2) << ", "
             << std::to_string(_result) << " ]\n";
    }
};

class LR_Parser {
    public:
        LR_Parser(string& input_file_name);
        LR_Parser() = default;
        ~LR_Parser() = default;

        // getters
        Lexer get_lexer() const;
        SymbolTable get_symbol_table() const;

        // modifiers
        void pop_reduce_rhs_from_stack(const vector<string>& reduce_entry_rhs);
        vector<StackFrame> pop_reduce_rhs_from_frame_stack(const vector<string>& reduce_entry_rhs);
        void push_reduce_lhs_to_stack(const string& reduce_entry_lhs);
        void push_reduce_lhs_to_frame_stack(const string& reduce_entry_lhs);
        void push_reduce_lhs_to_frame_stack_and_generate_quad(ofstream& out_file, const string& next_action, const string& reduce_entry_lhs, vector<StackFrame>& rhs_stack_frames, const string& opt_incoming_token, const string& opt_lexeme);

        // makequad
        size_t makequad(const string& op, size_t addr1, size_t addr2);

        // print helpers
        void print_current_stack_to_outfile(ofstream& out_file);
        void print_current_stack_frames_to_outfile(ofstream& out_file);
        void print_quads();

        bool parse_to_outfile(string& output_file_name);
        bool compile(string& output_file_name);

    private:
        // int if_nest_count;
        bool in_opt_decl_list;
        bool in_int_decl;
        bool in_bool_decl;
        unsigned int generated_code_line_count;
        unordered_map<size_t, vector<size_t>> _IDs;
        string _input_file_name;
        Lexer _lexer;
        stack<StackFrame> _lr_parser_frame_stack;
        stack<pair<string, int>> _lr_parser_stack;      // _parser_stack.first = state number, _parser_stack.second = symbol (terminal or nonterminal)
        LR_ParserTable _lr_parser_table;                // parser state transition table
        SymbolTable _symbol_table;
        vector<QuadRecord> _quad_table;
        vector<pair<string, QuadRecord>> _instruction_set;
};

#endif // LR_Parser