#include "lexical_analysis.h"
#include "buffer.h"

static string lexical;
static vector<string> idents;
static vector<string> nums;
static const set<string> keys = { "begin", "end", "if", "then", "while", "do", \
                             "const", "var", "call", "procedure", "odd" };
static pair<State, int> _state;

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

const pair<State, int> cur_lexical()
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
            }
            cur_char = _next_char();
        }

        _retract();
        idents.push_back(lexical);
        _state = {State::IDENT, idents.size()};
    } else if (isdigit(cur_char)) {
        while (isdigit(cur_char)) {
            cur_char = _next_char();
        }

        _retract();
        nums.push_back(lexical);
        _state = {State::NUMBER, nums.size()};
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
