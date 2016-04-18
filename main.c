/* xsh - eXperimental SHell
 * main.c - Contains main program
 */

#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <signal.h>
#include <locale.h>
#include <unistd.h>

#include "config.h"
#include "read.h"
#include "signals.h"
#include "log.h"

void free_parameters();

char *parameters[PARAMETERS_SIZE];

int main() {
  pid_t child_pid;
  bool child_in_fg;
  
  setlocale(LC_ALL, "");
  
  // Setting pointers to null
  memset(parameters, 0, (PARAMETERS_SIZE) * sizeof(*parameters));
  
  // Set signal handlers and at-exit function calls up
  signal(SIGINT, sigint_handler);
  signal(SIGCHLD, sigchld_handler);
  atexit(close_log);
  atexit(free_parameters);
  
  open_log();
  
  while (1) {
    read_command(parameters);
    
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wincompatible-pointer-types-discards-qualifiers"
    log_command(parameters);
#pragma GCC diagnostic pop
    
    if (!strcmp(parameters[0], "cd")) { // Change directory
      if (chdir(parameters[1]) == -1) {
        fputs("Could not change directory", stderr);
      }
      free_parameters();
      continue;
    }
    
    { // Checking for & character at end of command
      size_t i = 1;
      while (parameters[++i] != NULL);
      if (parameters[--i] && !strcmp(parameters[i], "&")) {
        child_in_fg = false;
        free(parameters[i]);
        parameters[i] = NULL;
      } else {
        child_in_fg = true;
      }
    }
    
    if ((child_pid = fork()) == -1) { // Fork error
      fputs("Cannot fork\n", stderr);
      exit(EXIT_FAILURE);
    } else if (child_pid == 0) { // Child code
      execvp(parameters[0], parameters);
      _exit(EXIT_FAILURE);
    } else if (child_in_fg) { // Parent with child in foreground
      waitpid(child_pid, NULL, WUNTRACED | WCONTINUED);
    } else { // Parent with child in background
      printf("[%d]\n", child_pid);
    }
    
    free_parameters();
  }
}

void free_parameters() {
  size_t i = 0;
  while (i < PARAMETERS_SIZE && parameters[i] != NULL) {
    free(parameters[i++]);
  }
  memset(parameters, 0, i * sizeof(*parameters));
}
