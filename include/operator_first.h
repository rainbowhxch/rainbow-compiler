#ifndef _OPERATOR_FIRST_H_
#define _OPERATOR_FIRST_H_

#include "lexical_analysis.h"
#include <unordered_map>
using std::unordered_map;

#define SIZE_OPERATOR 100
#define LBRA_NUMBER_RBRA    "839"
#define NUMBER_PLUS_NUMBER  "343"
#define NUMBER_MINUS_NUMBER "353"
#define NUMBER_PRO_NUMBER   "363"
#define NUMBER_DEV_NUMBER   "373"

static token s[SIZE_OPERATOR];
static int _operator_order[SIZE_OPERATOR][SIZE_OPERATOR];
static unordered_map<string, State> compose_rule;

static void init_compose_rule();

static void init_opertor_order();

static bool order_less_than(State a, State b);

static bool order_large_than(State a, State b);

static bool order_equal(State a, State b);

static State is_can_compose(string compose_array);

static bool is_final_state(State s);

static token compose(int l, int r);

static void error(string msg);

extern void print_info_ope();

extern void operator_first();

#endif /* ifndef _OPERATOR_FIRST_H_ */
