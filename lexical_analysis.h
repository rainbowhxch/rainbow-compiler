#ifndef __LEXICAL_ANALYSIS_H_
#define __LEXICAL_ANALYSIS_H_

#include <cctype>
#include <iostream>
#include <cstdio>
#include <string>
#include <utility>
#include <vector>
#include <set>
#include <utility>
#include "buffer.h"

#define SYM_ERROR "0"
#define SYM_IDENT "1"
#define SYM_NUMBER "2"

using std::string;
using std::vector;
using std::set;
using std::pair;

extern const pair<string, int> next_lexical();

#endif /* __LEXICAL_ANALYSIS_H_ */
