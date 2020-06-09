#include "buffer.h"
#include <cstdio>
#include <utility>

extern void init_buffer(const char *filename)
{
    _ptr_cur = 0;
    _fp = fopen(filename, "r");
    fseeko(_fp, 0, SEEK_END);
    _buffer_size = ftello(_fp);
    rewind(_fp);
    fread(_buffer + _ptr_cur, _buffer_size, 1, _fp);
}

extern char next_char()
{
    if (_ptr_cur >= _buffer_size-1) {
	_ptr_cur++;
        return '#';
    }
    while (isspace(_buffer[_ptr_cur]))
    {
        _ptr_cur++;
    }

    return _buffer[_ptr_cur++];
}

extern char current_char()
{
    if (_ptr_cur >= _buffer_size-1) {
        return '#';
    }

    return _buffer[_ptr_cur];
}

extern void advance()
{
    _ptr_cur++;
    if (_ptr_cur >= _buffer_size-1)
	return;

    while (isspace(_buffer[_ptr_cur]))
    {
        _ptr_cur++;
    }
}

extern void retract()
{
    _ptr_cur--;
}

void print_info()
{
    cout << "buffer: \n" << _buffer << endl;
}
