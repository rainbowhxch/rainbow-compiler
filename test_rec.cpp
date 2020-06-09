#include "buffer.h"
#include "lexical_analysis.h"
#include "recursive_descent.h"

int main()
{
    init_buffer("pl0.txt");
    next_lexical();
    E();

    if (cur_lexical().first != State::FIN) {
	cout << "error";
	return 0;
    }

    cout << "success";
    return 0;
}
