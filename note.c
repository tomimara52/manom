#include "note.h"
#include "entry.h"
#include "date.h"
#include <stdio.h>
#include <stdlib.h>

struct note_s {
    char* title;
    unsigned int title_length;
    entry_t* entries;
    unsigned int entries_size;
    unsigned int entries_capacity;
    date_t date;
};

note_t create_note(char* title, unsigned int title_length, date_t date) {
    note_t new_note = malloc(sizeof(struct note_s));
    
    new_note->title = calloc(sizeof(char), title_length);
    for (unsigned int i = 0; i < title_length; ++i) {
        (new_note->title)[i] = title[i];
    }
    new_note->title_length = title_length;
    
    new_note->entries = NULL;
    new_note->entries_size = 0;
    new_note->entries_capacity = 0;

    new_note->date = date;

    return new_note;
}

void add_entry(note_t note, entry_t entry) {
    if (note->entries_size < note->entries_capacity)
        (note->entries)[(note->entries_size)++] = entry;
    else {
        note->entries_capacity = note->entries_capacity ? note->entries_capacity*2 : 1;
        note->entries = realloc(note->entries, sizeof(entry_t) * note->entries_capacity);
        (note->entries)[(note->entries_size)++] = entry;
    }
}

void destroy_note(note_t note) {
    for (unsigned int i = 0; i < note->entries_size; ++i)
        destroy_entry((note->entries)[i]);

    free(note->entries);
    free(note->title);
    free(note);
}

void print_note(note_t note) {
    if (note->date) {
        print_date(note->date);
        printf(": "); 
    }
    printf("%s\n", note->title);
    for (unsigned int i = 0; i < note->entries_size; ++i) {
        printf("\t");
        print_entry((note->entries)[i]);
    }
}

/*
void dump_to_file(note_t note, const char* filename) {
    FILE* file_p = fopen(filename, "w");
    char* date_str = date_to_str(note->date);
}
*/
