#include <stdio.h>
#include <stdlib.h>
#include "entry.h"
#include "note.h"
#include "date.h"

int main() {
    entry_t entry0 = create_empty_entry();
    print_entry(entry0);

    char text[] = "greetings, universe";
    char text1[] = "omg starbucks";

    entry_t entry1 = create_entry(text, 20, create_date(2023, 8, 17));
    print_entry(entry1);

    entry_t entry2 = create_entry(text1, 14, create_date(2021, 2, 1));
    print_entry(entry2);

    note_t my_note = create_note("My first note", 14, create_date(2023, 8, 16));
    print_note(my_note);

    add_entry(my_note, entry2);
    print_note(my_note);

    add_entry(my_note, entry1);
    print_note(my_note);

    destroy_entry(entry0);

    char* entry1_str = entry_to_str(entry1);
    printf("%s\n", entry1_str);

    dump_to_file(my_note, "my_note.mnm");

    destroy_note(my_note);
    free(entry1_str);
}
