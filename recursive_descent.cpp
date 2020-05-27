#include "recursive_descent.h"
#include "lexical_analysis.h"

void E()
{
    T();
    E_pie();
}

void E_pie()
{
    auto tmp = next_lexical();
    if (tmp.first == State::PLUS || tmp.first == State::MINUS) {
        T();
        E_pie();
    } else {
        error("+ | -");
    }
}

void T()
{
    F();
    T_pie();
}

void T_pie()
{
    auto tmp = next_lexical();
    if (tmp.first == State::PRO || tmp.first == State::DEV) {
        F();
        T_pie();
    } else {
        error("* | /");
    }
}

void F()
{
    auto tmp = next_lexical();
    if (tmp.first == State::LBRA) {
        E();
        tmp = next_lexical();
        if (tmp.first != State::RBRA)
            error(")");
    } else if (tmp.first != State::IDENT && tmp.first != State::NUMBER) {
        error("IDENT | NUMBER");
    }
}

void error(string msg)
{
    std::cerr << __FILE__ << ", " << __LINE__ << ": ";
    std::cerr << "Error occured, current word is " << msg << endl;
    exit(EXIT_FAILURE);
}
