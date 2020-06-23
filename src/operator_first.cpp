#include "../include/operator_first.h"
#include "../include/lexical_analysis.h"
#include <c++/10.1.0/x86_64-pc-linux-gnu/bits/c++config.h>

static void init_compose_rule()
{
    compose_rule[LBRA_NUMBER_RBRA] = State::NUMBER;
    compose_rule[NUMBER_PLUS_NUMBER] = State::PLUS;
    compose_rule[NUMBER_MINUS_NUMBER] = State::MINUS;
    compose_rule[NUMBER_PRO_NUMBER] = State::PRO;
    compose_rule[NUMBER_DEV_NUMBER] = State::DEV;
}

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
    _operator_order[(int)State::FIN][(int)State::FIN] = 0;
}

static bool order_less_than(State a, State b)
{
    if (!is_final_state(a) || !is_final_state(b))
	return false;
    return (_operator_order[(int)a][(int)b] == -1);
}

static bool order_large_than(State a, State b)
{
    if (!is_final_state(a) || !is_final_state(b))
	return false;
    return (_operator_order[(int)a][(int)b] == 1);
}

static bool order_equal(State a, State b)
{
    if (!is_final_state(a) || !is_final_state(b))
	return false;
    return (_operator_order[(int)a][(int)b] == 0);
}

static bool is_final_state(State s)
{
    if (s == State::PLUS || s == State::MINUS || \
	s == State::PRO || s == State::DEV || \
	s == State::LBRA || s == State::RBRA || \
	s == State::FIN)
	return true;
    else
	return false;
}

static State is_can_compose(string compose_array)
{
    if (compose_rule.count(compose_array) == 0)
	return State::ERROR;
    return compose_rule[compose_array];
}

void print_info_ope()
{
    _operator_order[(int)State::PLUS][(int)State::LBRA] = -1;
    _operator_order[(int)State::PLUS][(int)State::RBRA] = 1;
    cout << _operator_order[(int)State::PLUS][(int)State::RBRA] << endl;
    cout << _operator_order[(int)State::PLUS][(int)State::LBRA] << endl;
}

token compose(int l, int r)
{
    string compose_array;
    int tmp_l = l;
    while (tmp_l <= r) {
	compose_array.push_back((int)s[tmp_l].first - 1 + '0');
	tmp_l++;
    }

    State tmp = is_can_compose(compose_array);
    if (tmp == State::NUMBER) {
	cout << "(NUMBER) -> NUMBER" << endl;
	return s[l+1];
    } else if (tmp == State::ERROR) {
	error("error compose!");
    } else {
	double first_val = get_num(s[l].second);
	double second_val = get_num(s[r].second);
	double result;

	if (tmp == State::PLUS) {
	    cout << "NUMBER+NUMBER -> NUMBER" << endl;
	    result = first_val + second_val;
	} else if (tmp == State::MINUS) {
	    cout << "NUMBER-NUMBER -> NUMBER" << endl;
	    result = first_val - second_val;
	} else if (tmp == State::PRO) {
	    cout << "NUMBER*NUMBER -> NUMBER" << endl;
	    result = first_val * second_val;
	} else {
	    cout << "NUMBER/NUMBER -> NUMBER" << endl;
	    result = first_val / second_val;
	}
	return {State::NUMBER, add_num(result)};
    }

    /* just for removing the warning */
    return {State::FIN, -1};
}

extern void operator_first()
{
    init_opertor_order();
    init_compose_rule();
    int k = 0, j; s[k] = {State::FIN, -1};
    token cur_state, prev_equal_state;
    do {
	next_lexical();
	cur_state = cur_lexical();
	while (!is_final_state(cur_state.first)) {
	    k += 1;
	    s[k] = cur_state;
	    next_lexical();
	    cur_state = cur_lexical();
	}

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
	    } while (order_large_than(s[j].first, prev_equal_state.first) || \
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

    cout << "The result is: " << get_num(s[k-1].second);
}

static void error(string msg)
{
    std::cerr << "Error occured: " << msg << endl;
    exit(EXIT_FAILURE);
}
