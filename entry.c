#include "entry.h"
#include "date.h"
#include <stdlib.h>
#include <stdio.h>

struct entry_s{
    char* content;
    unsigned int length;
    date_t date;
}; 

entry_t create_empty_entry() {
    entry_t new_entry = malloc(sizeof(struct entry_s));
    new_entry->content = NULL;
    new_entry->length = 0; 
    new_entry->date = 0;

    return new_entry;
}

entry_t create_entry(char* content, unsigned int length, date_t date) {
    entry_t new_entry = malloc(sizeof(struct entry_s));
    new_entry->content = calloc(sizeof(char), length);
    for (unsigned int i = 0; i < length; ++i) {
        (new_entry->content)[i] = content[i];
    }
    new_entry->length = length;

    new_entry->date = date;

    return new_entry;
}

int entry_is_empty(entry_t entry) {
    return entry->length == 0;
}

void destroy_entry(entry_t entry) {
    free(entry->content);
    free(entry);
}

void print_entry(entry_t entry) {
    if (entry->length) {
        if (entry->date) {
            print_date(entry->date);
            printf(": ");
        }
        printf("%s\n", entry->content);
    }
}

char* entry_to_str(entry_t entry) {
    unsigned int str_length = ULONG_MAX_DEC_DIGITS + 2 + entry->length;
    char* entry_str = calloc(sizeof(char), str_length);
    int date_end = sprintf(entry_str, "%lu", entry->date);

    entry_str[date_end] = '\n';

    for (unsigned int i = 0; i < entry->length; ++i) {
        entry_str[date_end + 1 + i] = (entry->content)[i];
    }

    entry_str[str_length] = 0;

    return entry_str;
}
