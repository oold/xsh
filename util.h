/* xsh - eXperimental SHell
 * util.h - Header for util.c
 */

#pragma once

#include "config.h"

#define TIME_STRLEN_DATE_AND_TIME 32
#define TIME_STRLEN_FILE_DATE 11

#define TIME_FORMAT_DATE_AND_TIME "%a %d %b %Y %X"
#define TIME_FORMAT_FILE_DATE "%F"

void get_time_str(char *str, size_t limit, const char *format);
void print_prompt();
