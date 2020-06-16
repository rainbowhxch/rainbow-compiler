#include "operator_first.h"
#include "lexical_analysis.h"
#include <cstdlib>

static void init_opertor_order()
{
    _operator_order[(int)State::PLUS][(int)State::PLUS] = 1;
    _operator_order[(int)State::PLUS][(int)State::MINUS] = 1;
    _operator_order[(int)State::PLUS][(int)State::PRO] = -1;
    _operator_order[(int)State::PLUS][(int)State::DEV] = -1;
    _operator_order[(int)State::PLUS][(int)State::LBRA] = -1;
    _operator_order[(int)State::PLUS][(int)State::RBRA] = 1;
    _operator_order[(int)State::PLUS][(int)State::FIN] = 1;

    _operator_order[(int)State::MINUS][(int)State::PLUS] = 1;
    _operator_order[(int)State::MINUS][(int)State::MINUS] = 1;
    _operator_order[(int)State::MINUS][(int)State::PRO] = -1;
    _operator_order[(int)State::MINUS][(int)State::DEV] = -1;
    _operator_order[(int)State::MINUS][(int)State::LBRA] = -1;
    _operator_order[(int)State::MINUS][(int)State::RBRA] = 1;
    _operator_order[(int)State::MINUS][(int)State::FIN] = 1;

    _operator_order[(int)State::PRO][(int)State::PLUS] = 1;
    _operator_order[(int)State::PRO][(int)State::MINUS] = 1;
    _operator_order[(int)State::PRO][(int)State::PRO] = 1;
    _operator_order[(int)State::PRO][(int)State::DEV] = 1;
    _operator_order[(int)State::PRO][(int)State::LBRA] = -1;
    _operator_order[(int)State::PRO][(int)State::RBRA] = 1;
    _operator_order[(int)State::PRO][(int)State::FIN] = 1;

    _operator_order[(int)State::DEV][(int)State::PLUS] = 1;
    _operator_order[(int)State::DEV][(int)State::MINUS] = 1;
    _operator_order[(int)State::DEV][(int)State::PRO] = 1;
    _operator_order[(int)State::DEV][(int)State::DEV] = 1;
    _operator_order[(int)State::DEV][(int)State::LBRA] = -1;
    _operator_order[(int)State::DEV][(int)State::RBRA] = 1;
    _operator_order[(int)State::DEV][(int)State::FIN] = 1;

    _operator_order[(int)State::LBRA][(int)State::PLUS] = -1;
    _operator_order[(int)State::LBRA][(int)State::MINUS] = -1;
    _operator_order[(int)State::LBRA][(int)State::PRO] = -1;
    _operator_order[(int)State::LBRA][(int)State::DEV] = -1;
    _operator_order[(int)State::LBRA][(int)State::LBRA] = -1;
    _operator_order[(int)State::LBRA][(int)State::RBRA] = 0;
    _operator_order[(int)State::LBRA][(int)State::FIN] = 2;

    _operator_order[(int)State::RBRA][(int)State::PLUS] = 1;
    _operator_order[(int)State::RBRA][(int)State::MINUS] = 1;
    _operator_order[(int)State::RBRA][(int)State::PRO] = 1;
    _operator_order[(int)State::RBRA][(int)State::DEV] = 1;
    _operator_order[(int)State::RBRA][(int)State::LBRA] = 2;
    _operator_order[(int)State::RBRA][(int)State::RBRA] = 1;
    _operator_order[(int)State::RBRA][(int)State::FIN] = 1;

    _operator_order[(int)State::FIN][(int)State::PLUS] = -1;
    _operator_order[(int)State::FIN][(int)State::MINUS] = -1;
    _operator_order[(int)State::FIN][(int)State::PRO] = -1;
    _operator_order[(int)State::FIN][(int)State::DEV] = -1;
    _operator_order[(int)State::FIN][(int)State::LBRA] = -1;
    _operator_order[(int)State::FIN][(int)State::RBRA] = 2;
    _operator_order[(int)State::FIN][(int)State::FIN] = 2;
}

static bool order_less_than(State a, State b)
{
    return (_operator_order[(int)a][(int)b] == -1);
}

static bool order_large_than(State a, State b)
{
    return (_operator_order[(int)a][(int)b] == 1);
}

static bool order_equal(State a, State b)
{
    return (_operator_order[(int)a][(int)b] == 0);
}

static bool is_final_state(State s)
{
    if (s == State::PLUS || s == State::MINUS || \
	s == State::PRO || s == State::DEV || \
	s == State::LBRA || s == State::RBRA)
	return true;
    else
	return false;
}

pair<State, int> compose(int l, int r)
{
    int len = r - l + 1;
    if (len == 1) {
	if (s[l].first == State::PLUS)
	    return {State::NUMBER, s[l-1].second + s[l+1].second};
	else if (s[l].first == State::MINUS)
	    return {State::NUMBER, s[l-1].second - s[l+1].second};
	else if (s[l].first == State::PRO)
	    return {State::NUMBER, s[l-1].second * s[l+1].second};
	else if (s[l].first == State::DEV)
	    return {State::NUMBER, s[l-1].second / s[l+1].second};
    } else if (len == 3) {
	return s[l+1];
    } else {
	error("error compose!");
    }
}

extern void operator_first()
{
    int k = 0, j; s[k] = {State::FIN, -1};
    pair<State, int> cur_state, prev_equal_state;
    do {
	next_lexical();
	cur_state = cur_lexical();
	if (is_final_state(s[k].first))
	    j = k;
	else
	    j = k - 1;
	while (order_large_than(s[j].first, cur_state.first)) {
	    do {
		prev_equal_state = s[j];
		if (is_final_state(s[j-1].first))
		    j -= 1;
		else
		    j -= 2;
	    } while (order_less_than(s[j].first, prev_equal_state.first) || \
		    order_equal(s[j].first, prev_equal_state.first));
	    /* compose */
	    int l = j+1, r = k;
	    k = j + 1;
	    s[k] = compose(l, r);
	}

	if (order_less_than(s[j].first, cur_state.first) || \
		order_equal(s[j].first, cur_state.first)) {
	    k += 1;
	    s[k] = cur_state;
	} else {
	    error("error order!");
	}
    } while (cur_state.first != State::FIN);
}

static void error(string msg)
{
    std::cerr << "Error occured: " << msg << endl;
    exit(EXIT_FAILURE);
}
