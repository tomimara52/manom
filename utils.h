#pragma once

#include "date.h"

unsigned int undef_length_str_stdin(char** str, int allow_newlines, unsigned int excess_size);

date_t get_current_date();
