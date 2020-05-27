#include "buffer.h"
#include "lexical_analysis.h"

int main(int argc, char *argv[])
{
    init_buffer("pl0.txt");
    pair<State, int> a;
    while (true) {
        a = next_lexical();
        if (a.first == State::FIN)
            break;
        cout << "<" << a.first << ", " << a.second << ">" << endl;
    }
    return 0;
}
