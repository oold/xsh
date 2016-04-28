/* xsh - eXperimental SHell
 * signals.c - Contains signal handlers
 */

#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <sys/wait.h>

#include "config.h"
#include "signals.h"
#include "util.h"

bool was_interrupted = false;

void sigint_handler(int param) {
  printf("\nDo you want to quit? (y/n) ");
  fflush(stdout);
  was_interrupted = true;
}

void sigint_child_in_fg_handler(int param) {
  puts("");
}

void sigchld_handler(int param) {
  while (waitpid(-1, NULL, WNOHANG) > 0);
}
