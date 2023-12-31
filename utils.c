#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>

#include "utils.h"

unsigned int undef_length_str_stdin(char** str, int allow_newlines, unsigned int excess_size) {
    char text[256];
    unsigned int acc_size = 0;
    *str = calloc(sizeof(char), excess_size);

    while (1) {
        char* check = fgets(text, 256, stdin);

        // if read EOF
        if (check == NULL)
            break;

        unsigned int read_length = strlen(text);

        // realloc to the size it has + the amount i read + the null character
        *str = realloc(*str, (excess_size + acc_size + read_length + 1) * sizeof(char));
        // write in content + acc_size to not overwrite previous
        sprintf(*str + acc_size, "%s", text);
        // only add read_length and not + 1 for null character because I only want a null
        // character at the end
        acc_size += read_length;

     
        // if EOF sent in middle of input
        if (feof(stdin)) {
            break;
        }

        if (!allow_newlines) {
            // remove last '\n'
            (*str)[acc_size - 1] = 0;
            // decrease str length
            --acc_size;
            break;
        }
    }

    // make stdin not EOF
    clearerr(stdin);

    return acc_size + 1 + excess_size;
}

date_t get_current_date() {
    time_t res = time(NULL);
    struct tm* lcl_tm = localtime(&res);
    return create_date(lcl_tm->tm_year + 1900,
                       lcl_tm->tm_mon + 1,
                       lcl_tm->tm_mday);
}
