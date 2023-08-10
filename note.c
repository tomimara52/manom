#include "note.h"
#include "entry.h"
#include "date.h"
#include <stdio.h>
#include <stdlib.h>

#define SEP "%\n%"
#define SEP_L 3
#define SEP_DATE_FORMAT "%%\n%%%lu\n"

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
    fputs(SEP, file_p);

    for (unsigned int i = 0; i < note->entries_size; ++i) {
        char* entry_str = entry_to_str((note->entries)[i]);
        fputs(entry_str, file_p);
        free(entry_str);
        
        fputs(SEP, file_p);
    }
    fputc('\n', file_p);
    fputc(0, file_p);

    fclose(file_p);
}

unsigned int length_until_sep(FILE* file_p) {
    unsigned int length = 0;
    fpos_t return_pos;
    fgetpos(file_p, &return_pos);

    while (1) {
        fpos_t next_char_pos;
        fgetpos(file_p, &next_char_pos);
        
        unsigned int i = 0;
        unsigned int keep_going = 1;
        while (i < SEP_L && keep_going) {
            char c;
            fscanf(file_p, "%c", &c);

            if (c != SEP[i]) {
                keep_going = 0;
            }

            ++i;
        }

        ++length;
        if (i == SEP_L) {
            break;
        }

        fsetpos(file_p, &next_char_pos);
        fgetc(file_p);
    }

    fsetpos(file_p, &return_pos);

    return length;
}

note_t read_note_file(const char* filename) {
    note_t note = malloc(sizeof(struct note_s));
    FILE* file_p = fopen(filename, "r");
    
    date_t* date_p = malloc(sizeof(date_t));
    fscanf(file_p, "%lu\n", date_p);
    note->date = *date_p;

    free(date_p);

    unsigned int title_length = length_until_sep(file_p);
    char* title = calloc(sizeof(char), title_length);
    title[title_length - 1] = 0;

    for (unsigned int i = 0; i < title_length - 1; ++i) {
        title[i] = fgetc(file_p);
    }

    note->title = title;
    note->title_length = title_length;

    note->entries = NULL;
    note->entries_size = 0;
    note->entries_capacity = 0;

    while (1) {

        date_t* entry_date_p = malloc(sizeof(date_t));
        unsigned int date_scan = fscanf(file_p, SEP_DATE_FORMAT, entry_date_p);

        if (date_scan == 0)
            break;

        unsigned int entry_length = length_until_sep(file_p);
        char* entry_content = calloc(sizeof(char), entry_length);
        entry_content[entry_length - 1] = 0;

        for (unsigned int i = 0; i < entry_length - 1; ++i) {
            entry_content[i] = fgetc(file_p);
        }

        add_entry(note, create_entry(entry_content, entry_length, *entry_date_p));

        free(entry_date_p);
        free(entry_content);
    }

    return note;
    
}
