#ifndef __LEXICAL_ANALYSIS_H_
#define __LEXICAL_ANALYSIS_H_

#include <cctype>
#include <iostream>
#include <cstdio>
#include <string>
#include <utility>
#include <vector>
#include <set>
#include <utility>
#include "buffer.h"

enum class State : unsigned int
{
    ERROR, FIN, KEY, IDENT, NUMBER, PLUS, MINUS,
    PRO, DEV, LBRA, RBRA, LESS, LARGE, EQUAL,COMMA,
    DOT, SEM, ODD
};

using std::string;
using std::vector;
using std::set;
using std::pair;

extern double get_num(int idx);
extern int add_num(double val);

extern string get_ident(int idx);
extern int add_ident(string val);


extern void next_lexical();

extern const pair<State, int> cur_lexical();

#endif /* __LEXICAL_ANALYSIS_H_ */
