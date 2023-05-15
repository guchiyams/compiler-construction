#ifndef LR_PARSER_TABLE
#define LR_PARSER_TABLE

#include <iostream>
#include <unordered_map>    // std::unordered_map
#include <utility>          // std::pair
#include <vector>           // std::vector

using std::pair;
using std::unordered_map;
using std::vector;

class LR_ParserTable {
    public:
        LR_ParserTable() = default;
        ~LR_ParserTable() = default;

        // get next action
        const string get_next_action(int row, string incoming_token) const;

        // get next goto
        const string get_next_goto(int curr_state, string reduce_entry_lhs) const;

        // get reduce entry
        pair<string, vector<string>> get_reduce(const string& reduce_action);
    
    private:
        static const unordered_map<string, int> LR_TERMINAL_TO_ACTION_TABLE_COLUMN_INDEX;
        static const unordered_map<string, int> LR_NONTERMINAL_TO_GOTO_TABLE_COLUMN_INDEX;
        static const unordered_map<string, pair<string, vector<string>>> REDUCE_DIRECTORY;
        static const vector<vector<string>> LR_STATE_TRANSITION_TABLE;

};


#endif // LR_PARSER_TABLE