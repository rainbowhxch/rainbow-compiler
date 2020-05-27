#include "lexical_analysis.h"

static string lexical;
static vector<string> idents;
static vector<string> nums;
static const set<string> keys = { "begin", "end", "if", "then", "while", "do", \
                             "const", "var", "call", "procedure", "odd" };

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

const pair<State, int> next_lexical()
{
    lexical.clear();
    char cur_char = _next_char();
    if (cur_char == '#')
        return {State::FIN, -1};

    if (islower(cur_char)) {
        while (islower(cur_char) || isdigit(cur_char)) {
            if (keys.count(lexical)) {
                if (lexical != "odd")
                    return {State::KEY, -1};
                else
                    return {State::ODD, -1};
            }
            cur_char = _next_char();
        }

        _retract();
        idents.push_back(lexical);
        return {State::IDENT, idents.size()};
    } else if (isdigit(cur_char)) {
        while (isdigit(cur_char)) {
            cur_char = _next_char();
        }

        _retract();
        nums.push_back(lexical);
        return {State::NUMBER, nums.size()};
    } else if (cur_char == '<') {
        cur_char = _next_char();
        if (cur_char != '>' || cur_char != '=') {
            _retract();
        }
        return {State::LESS, -1};
    } else if (cur_char == '>') {
        cur_char = _next_char();
        if (cur_char != '=') {
            _retract();
        }
        return {State::LARGE, -1};
    } else if (cur_char == ':') {
        cur_char = _next_char();
        if (cur_char != '=') {
            _retract();
        }
        return {State::EQUAL, -1};
    } else if (cur_char == '+') {
        return {State::PLUS, -1};
    } else if (cur_char == '-') {
        return {State::MINUS, -1};
    } else if (cur_char == '*') {
        return {State::PRO, -1};
    } else if (cur_char == '/') {
        return {State::DEV, -1};
    } else if (cur_char == '(') {
        return {State::LBRA, -1};
    } else if (cur_char == ')') {
        return {State::RBRA, -1};
    } else if (cur_char == ',') {
        return {State::COMMA, -1};
    } else if (cur_char == '.') {
        return {State::DOT, -1};
    } else if (cur_char == ';') {
        return {State::SEM, -1};
    } else {
        return {State::ERROR, -1};
    }
}
