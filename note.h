#pragma once

#include "entry.h"
#include "date.h"

typedef struct note_s* note_t;

note_t create_note(char* title, unsigned int title_length, date_t date);

void add_entry(note_t note, entry_t entry);

void destroy_note(note_t note);

void print_note(note_t note);

//void dump_to_file(note_t note, const char* filename);
