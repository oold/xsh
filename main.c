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
#include <sys/wait.h>

#include "config.h"
#include "read.h"
#include "signals.h"
#include "log.h"

void reset_parameters(char ***parameters);

int main() {
  char **parameters = malloc(PARAMETERS_SIZE * sizeof(*parameters));
  
  setlocale(LC_ALL, "");
  
  // Set signal handlers and at-exit function calls up
  signal(SIGINT, sigint_handler);
  signal(SIGCHLD, sigchld_handler);
  atexit(close_log);
  
  open_log();
  
  while (1) {
    pid_t child_pid;
    bool child_in_fg;
    size_t arg_count;
    
    read_command(&parameters, &arg_count);
    
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wincompatible-pointer-types-discards-qualifiers"
    log_command(parameters);
#pragma GCC diagnostic pop
    
    if (!strcmp(parameters[0], "cd")) { // Change directory
      if (parameters[2] != NULL) {
        fputs("Too many arguments for cd! Only one is supported.\n", stderr);
      } else if (chdir(parameters[1]) == -1) {
        fputs("Cannot not change directory\n", stderr);
      }
      reset_parameters(&parameters);
      continue;
    }
    
    // Checking for & character at end of command
    if (!strcmp(parameters[arg_count], "&")) {
      child_in_fg = false;
      free(parameters[arg_count]);
      parameters[arg_count] = NULL;
    } else {
      child_in_fg = true;
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
    
    reset_parameters(&parameters);
  }
}

void reset_parameters(char ***parameters) {
  size_t i = 0;
  while ((*parameters)[i] != NULL) {
    free((*parameters)[i++]);
  }
  *parameters = realloc(*parameters, PARAMETERS_SIZE * sizeof(**parameters));
}
