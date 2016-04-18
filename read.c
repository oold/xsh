/* xsh - eXperimental SHell
 * read.c - Contains helpers for reading commands
 */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "config.h"
#include "read.h"
#include "util.h"

char read_str(char *str);

void read_command(char **par) {
  print_prompt();
  size_t i = 0;
  while (1) {
    par[i] = malloc(COMMAND_LENGTH * sizeof(char));
    if (read_str(par[i]) == '\n') {
      break;
    }
    if (++i == PARAMETERS_SIZE - 1) {
      fputs("Too many parameters!\n", stderr);
      exit(EXIT_FAILURE);
    }
  }
}

char read_str(char *str) {
  char tmp;
  size_t i = 0;
  while (1) {
    tmp = getchar();
    if (tmp == ' ' || tmp == '\n') {
      str[i] = '\0';
      break;
    }
    str[i] = tmp;
    if (++i == COMMAND_LENGTH - 1) {
      fputs("String too long!\n", stderr);
      exit(EXIT_FAILURE);
    }
  }
  return tmp;
}
