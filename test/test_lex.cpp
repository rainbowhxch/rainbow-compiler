#include "../include/lexical_analysis.h"

int main(int argc, char *argv[])
{
    init_buffer("pl0_lex.txt");
    print_info();
    pair<State, int> a;
    int n = 10;
    while (n--) {
	next_lexical();
        a = cur_lexical();
        if (a.first == State::FIN)
            break;
        cout << "<" << (int)a.first << ", " << a.second << ">" << endl;
    }
    return 0;
}
