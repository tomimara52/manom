#include "date.h"
#include <stdio.h>
#include <stdlib.h>


date_t create_date(int year, char month, char day) {
    return day | (month << 5) | (year << 9); 
}

void print_date(date_t date) {
    printf("%lu/%lu/%lu", date >> 9, (date >> 5) & 15, date & 31);
}

char* date_to_str(date_t date) {
    char* date_str = calloc(sizeof(char), ULONG_MAX_DEC_DIGITS + 1);
    sprintf(date_str, "%lu", date);

    return date_str;
}
