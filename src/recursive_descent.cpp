#include "../include/recursive_descent.h"
#include "../include/lexical_analysis.h"

void E()
{
    cout << "E->TE\'" << endl;
    T();
    E_pie();
}

void E_pie()
{
    auto tmp = cur_lexical();

    if (tmp.first == State::PLUS || tmp.first == State::MINUS) {
	cout << "E\'->+TE\'|-TE\'" << endl;
	next_lexical();
        T();
        E_pie();
    } else {
	cout << "E\'->null" << endl;
    }
}

void T()
{
    cout << "T->FT\'" << endl;
    F();
    T_pie();
}

void T_pie()
{
    auto tmp = cur_lexical();

    if (tmp.first == State::PRO || tmp.first == State::DEV) {
	cout << "T\'->*FT\'|/FT\'" << endl;
	next_lexical();
        F();
        T_pie();
    } else {
	cout << "T\'->null" << endl;
    }
}

void F()
{
    auto tmp = cur_lexical();

    if (tmp.first == State::LBRA) {
	cout << "F->(E)" << endl;
	next_lexical();
        E();
        tmp = cur_lexical();

	if (tmp.first == State::RBRA) {
	    next_lexical();
	} else {
	    error(")");
	}
    } else if (tmp.first == State::IDENT || tmp.first == State::NUMBER) {
	cout << "F->id|num" << endl;
	next_lexical();
    } else {
        error("IDENT | NUMBER | (");
    }
}

void error(string msg)
{
    std::cerr << "Error occured, current word is " << msg << endl;
    exit(EXIT_FAILURE);
}
