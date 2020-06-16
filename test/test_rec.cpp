#include "../include/recursive_descent.h"

int main()
{
    init_buffer("pl0_rec.txt");
    next_lexical();
    E();

    if (cur_lexical().first != State::FIN) {
	cout << "error";
	return 0;
    }

    cout << "success";
    return 0;
}
