/* xsh - eXperimental SHell
 * signals.c - Contains signal handlers
 */

#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>

#include "config.h"
#include "signals.h"
#include "util.h"

void sigint_handler(int param) {
  printf("\nDo you want to quit? (y/n) ");
  char ch = getchar();
  if (ch == 'y' || ch == 'Y')
    exit(EXIT_SUCCESS);
  fseek(stdin, 0, SEEK_END);
  print_prompt();
  fflush(stdout);
}

void sigchld_handler(int param) {
  while (waitpid(-1, NULL, WNOHANG) > 0);
}
