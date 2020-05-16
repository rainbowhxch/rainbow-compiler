#include "lexical_analysis.h"

static string lexical;
static vector<string> idents;
static vector<string> nums;
static const set<string> keys = { "begin", "end", "if", "then", "while", "do", \
                             "const", "var", "call", "procedure", "odd" };
const string cals = "+-*/=(),.;";

static const char _next_char()
{
    const char c = next_char();
    lexical.push_back(c);
    return c;
}

static void _retract()
{
    retract();
    lexical.pop_back();
}

const pair<string, int> next_lexical()
{
    lexical.clear();
    char cur_char = _next_char();
    if (cur_char == '#')
        return {"#", -1};

    if (islower(cur_char)) {
        while (islower(cur_char) || isdigit(cur_char)) {
            if (keys.count(lexical))
                return {lexical, -1};
            cur_char = _next_char();
        }

        _retract();
        idents.push_back(lexical);
        return {lexical, idents.size()};
    } else if (isdigit(cur_char)) {
        while (isdigit(cur_char)) {
            cur_char = _next_char();
        }

        _retract();
        nums.push_back(lexical);
        return {lexical, nums.size()};
    } else if (cur_char == '<') {
        cur_char = _next_char();
        if (cur_char != '>' || cur_char != '=') {
            _retract();
        }
        return {lexical, -1};
    } else if (cur_char == '>') {
        cur_char = _next_char();
        if (cur_char != '=') {
            _retract();
        }
        return {lexical, -1};
    } else if (cur_char == ':') {
        cur_char = _next_char();
        if (cur_char != '=') {
            _retract();
        }
        return {lexical, -1};
    } else if (cals.find(cur_char) != string::npos) {
        return {lexical, -1};
    } else {
        return {SYM_ERROR, -1};
    }
}
