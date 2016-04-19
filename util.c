/* xsh - eXperimental SHell
 * util.c - Utility functions
 */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <time.h>
#include <unistd.h>

#include "config.h"
#include "util.h"

void get_time_str(char *str, size_t limit, const char *format) {
  time_t timer = time(NULL);
  if (timer == -1) {
    *str = 0;
  }
  struct tm *curr_time = gmtime(&timer);
  strftime(str, limit, format, curr_time);
}

void print_prompt() {
  char wd[4096];
  if (!getcwd(wd, 4096)) {
    fputs("Cannot get path name\n", stderr);
    exit(EXIT_FAILURE);
  }
  printf("%s> ", wd);
}
