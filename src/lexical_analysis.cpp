#include "../include/lexical_analysis.h"
#include "../include/buffer.h"
#include <string>

static string lexical;
static vector<string> idents;
static vector<string> nums;
static const set<string> keys = { "begin", "end", "if", "then", "while", "do", \
                             "const", "var", "call", "procedure", "odd" };
static token _state;

extern double get_num(int idx)
{
    return stof(nums[idx]);
}

extern int add_num(double val)
{
    nums.push_back(std::to_string(val));
    return nums.size()-1;
}

extern string get_ident(int idx)
{
    return idents[idx];
}

extern int add_ident(string val)
{
    idents.push_back(val);
    return idents.size()-1;
}

static const char _next_char()
{
    const char c = current_char();
    advance();
    lexical.push_back(c);
    return c;
}

static void _retract()
{
    retract();
    lexical.pop_back();
}

const token cur_lexical()
{
    return _state;
}

void next_lexical()
{
    lexical.clear();
    char cur_char = _next_char();

    if (cur_char == '#') {
        _state = {State::FIN, -1};
	return;
    }

    if (islower(cur_char)) {
        while (islower(cur_char) || isdigit(cur_char)) {
            if (keys.count(lexical)) {
                if (lexical != "odd")
                    _state = {State::KEY, -1};
                else
                    _state = {State::ODD, -1};
		return;
            }
            cur_char = _next_char();
        }

        _retract();
        idents.push_back(lexical);
        _state = {State::IDENT, idents.size()-1};
    } else if (isdigit(cur_char)) {
        while (isdigit(cur_char)) {
            cur_char = _next_char();
        }

        _retract();
        nums.push_back(lexical);
        _state = {State::NUMBER, nums.size()-1};
    } else if (cur_char == '<') {
        cur_char = _next_char();
        if (cur_char != '>' || cur_char != '=') {
            _retract();
        }
        _state = {State::LESS, -1};
    } else if (cur_char == '>') {
        cur_char = _next_char();
        if (cur_char != '=') {
            _retract();
        }
        _state = {State::LARGE, -1};
    } else if (cur_char == ':') {
        cur_char = _next_char();
        if (cur_char != '=') {
            _retract();
        }
        _state = {State::EQUAL, -1};
    } else if (cur_char == '+') {
        _state = {State::PLUS, -1};
    } else if (cur_char == '-') {
        _state = {State::MINUS, -1};
    } else if (cur_char == '*') {
        _state = {State::PRO, -1};
    } else if (cur_char == '/') {
        _state = {State::DEV, -1};
    } else if (cur_char == '(') {
        _state = {State::LBRA, -1};
    } else if (cur_char == ')') {
        _state = {State::RBRA, -1};
    } else if (cur_char == ',') {
        _state = {State::COMMA, -1};
    } else if (cur_char == '.') {
        _state = {State::DOT, -1};
    } else if (cur_char == ';') {
        _state = {State::SEM, -1};
    } else {
        _state = {State::ERROR, -1};
    }
}
