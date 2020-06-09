#ifndef __BUFFER_H_
#define __BUFFER_H_

#include <cstdio>
#include <iostream>
#include <cctype>
#include <cstring>

#define SIZE_BUFFER 65536

using std::cout;
using std::endl;

static char _buffer[SIZE_BUFFER];
static int _buffer_size;
static int _ptr_cur = 0;
static FILE *_fp;

extern void init_buffer(const char *filename);

extern char next_char();

extern char current_char();

extern void advance();

extern void retract();

extern void print_info();

#endif /* __BUFFER_H_ */
