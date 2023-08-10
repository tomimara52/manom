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

void dump_to_file(note_t note, const char* filename) {
    FILE* file_p = fopen(filename, "w");

    char* note_date_str = calloc(sizeof(char), ULONG_MAX_DEC_DIGITS + 1);
    sprintf(note_date_str, "%lu", note->date);
    fputs(note_date_str, file_p);
    free(note_date_str);
    
    fputc('\n', file_p);

    fputs(note->title, file_p);
    fputs("{\n", file_p);

    for (unsigned int i = 0; i < note->entries_size; ++i) {
        char* entry_str = entry_to_str((note->entries)[i]);
        fputs(entry_str, file_p);
        free(entry_str);
        
        fputs("{\n", file_p);
    }
    fputc(0, file_p);

    fclose(file_p);
}

/*
note_t read_note_file(const char* filename) {
    FILE* file_p = fopen(filename, "r");
    
    unsigned long* date_p = malloc(sizeof(date_t));
    fscanf(file_p, "%lu\n", date_p);
}
*/
