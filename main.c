#include <stdio.h>
#include <stdlib.h>
#include <stdio.h>
#include <dirent.h>

#include "note.h"

note_t select_note() {
    DIR* dir_p = opendir(".");

    // get file number in dir
    unsigned int n_files = 0;
    while(readdir(dir_p)) {
        ++n_files;
    }

    // substract .. and .
    n_files -= 2;

    // return dir to first postition
    seekdir(dir_p, 0);

    unsigned int n_note_files = 0;
    char** note_file_names = calloc(sizeof(char*), n_files);

    struct dirent* file;
    while ((file = readdir(dir_p))) {
        char* file_name = file->d_name;

        // get the length of the file_name
        unsigned int i = 0;
        while (file_name[i] != 0) {
            ++i;
        }

        // see if has length at least 5 and .mnm extension
        if (i >= 5 && file_name[i-3] == 'm' && file_name[i-2] == 'n' && file_name[i-1] == 'm') {
            note_file_names[n_note_files] = file_name;
            ++n_note_files;
            printf("(%u): %s\n", n_note_files, file_name);
        }
    }

    if (n_note_files == 0) {
        printf("There are not .mnm files in this directory\n");
        closedir(dir_p);
        free(note_file_names);

        return NULL;
    }

    char* file_chosen = NULL;
    unsigned int choice;
    while (!file_chosen) {
        printf("Select which note you wanna select [1-%u]: ", n_note_files);

        if ((scanf("%u", &choice)) && 1 <= choice && choice <= n_note_files) {
            file_chosen = note_file_names[choice - 1];
        } else {
            printf("Invalid choice\n");
            // consume newline
            getchar();
        }
    }

    note_t note = read_note_file(file_chosen);

    closedir(dir_p);
    free(note_file_names);

    return note;
}

int main() {
    char choice = 0;
    do {
        printf("Do you want to create or select a note? [c/s]: ");    
        scanf("%s", &choice);

        if (choice != 's') {
            printf("Invalid option\n");
            choice = 0;
        }
    } while (!choice);

    note_t note = select_note();

    if (!note) {
        printf("Bye\n");
        return 0;
    }

    printf("\tp\tPrint the selected note.\n"
           "\ta\tAdd new entry to selected note.\n"
           "\tq\tQuit program.\n"
           "\th\tDisplay this menu.\n");

    int quit = 0;
    while (!quit) {
        printf("\n(%s)> ", get_note_title(note));
        scanf("%s", &choice);
        // consume newline
        getchar();

        switch (choice) {
        case 'p':
            print_note(note);
            break;
        case 'q':
            quit = 1;
            break;
        case 'a':
            printf("When finished typing entry, press CTRL-D in a newline or CTRL-D twice\n");
            add_entry(note, create_entry_from_stdin());
            break;
        case 'h':
            printf("\tp\tPrint the selected note.\n"
                   "\ta\tAdd new entry to selected note.\n"
                   "\tq\tQuit program.\n"
                   "\th\tDisplay this menu.\n");
            break;
        default:
            printf("Invalid choice\n");
        }
    }

    destroy_note(note);
    return 0;

}
