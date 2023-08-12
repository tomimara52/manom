#pragma once

#include "date.h"

typedef struct entry_s* entry_t;

entry_t create_empty_entry();

entry_t create_entry(char* content, unsigned int length, date_t date);

int entry_is_empty(entry_t entry);

void destroy_entry(entry_t entry);

void print_entry(entry_t entry);

char* entry_to_str(entry_t entry);

date_t get_entry_date(entry_t entry);

unsigned int get_entry_length(entry_t entry);

char* get_entry_content(entry_t entry);

entry_t create_entry_from_stdin();
