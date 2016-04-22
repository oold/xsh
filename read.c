/* xsh - eXperimental SHell
 * read.c - Contains helpers for reading commands
 */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "config.h"
#include "read.h"
#include "util.h"

char read_str(char **str);

void read_command(char **par, size_t *argc) {
  print_prompt();
  *argc = 0;
  while (1) {
    par[*argc] = malloc(COMMAND_LENGTH * sizeof(**par));
    if (read_str(&par[*argc]) == '\n') {
      par[*argc + 1] = NULL;
      break;
    }
    if (++*argc == PARAMETERS_SIZE - 1) {
      fputs("Too many parameters!\n", stderr);
      exit(EXIT_FAILURE);
    }
  }
}

char read_str(char **str) {
  char tmp;
  size_t i = 0;
  size_t arr_size = COMMAND_LENGTH;
  while (1) {
    tmp = getchar();
    if (tmp == ' ' || tmp == '\n') {
      (*str)[i] = '\0';
      break;
    }
    (*str)[i] = tmp;
    if (++i == arr_size - 1) {
      arr_size *= 2;
      *str = realloc(*str, arr_size * sizeof(**str));
      if (!*str) {
        fputs("Could not allocate enough memory for arguments", stderr);
        exit(EXIT_FAILURE);
      }
    }
  }
  return tmp;
}
