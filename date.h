#pragma once
#include <math.h>
#include <limits.h>

// approximation of max number of digits an unsigned long might occupy
#define ULONG_MAX_DEC_DIGITS (unsigned int)ceil(sizeof(unsigned long) * CHAR_BIT * 0.302)

typedef unsigned long date_t;

date_t create_date(int year, char month, char day);

void print_date(date_t date);

char* date_to_str(date_t date);
