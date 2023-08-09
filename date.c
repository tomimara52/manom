#include "date.h"
#include <stdio.h>
#include <stdlib.h>

/*
if I start counting from the right of the number:
from bit 0 to bit 4 is the day
from 5 to bit 8 is the mont
the rest of the bits is the year
*/

date_t create_date(int year, char month, char day) {
    return day | (month << 5) | (year << 9); 
}

void print_date(date_t date) {
    printf("%lu/%lu/%lu", date >> 9, (date >> 5) & 15, date & 31);
    // & 15 is representing & 0b1111 (keep the last 4 bits)
    // & 31 is representing & 0b11111 (keep the last 5 bits)
}

char* date_to_str(date_t date) {
    char* date_str = calloc(sizeof(char), ULONG_MAX_DEC_DIGITS + 1);
    sprintf(date_str, "%lu", date);

    return date_str;
}
