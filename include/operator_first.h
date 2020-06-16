#ifndef _OPERATOR_FIRST_H_
#define _OPERATOR_FIRST_H_

#include "lexical_analysis.h"
#define SIZE_OPERATOR 100

static pair<State, int> s[SIZE_OPERATOR];
static int _operator_order[SIZE_OPERATOR][SIZE_OPERATOR];

static void init_opertor_order();

static bool order_less_than(State a, State b);

static bool order_large_than(State a, State b);

static bool order_equal(State a, State b);

static bool is_final_state(State s);

static pair<State, int> compose(int l, int r);

static void error(string msg);

extern void operator_first();

#endif /* ifndef _OPERATOR_FIRST_H_ */
