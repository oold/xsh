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
  setlocale(LC_ALL, "");
  
  puts("Welcome to the " APP_NAME " shell!");
  
  char **parameters = malloc(PARAMETERS_SIZE * sizeof(*parameters));
  
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
    log_command(parameters);
    
    if (was_interrupted) { // In case the user interrupted us
      if (parameters[0][0] == 'y' || parameters[0][0] == 'Y') {
        exit(EXIT_SUCCESS);
      }
      was_interrupted = false;
      reset_parameters(&parameters);
      continue;
    }
    
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
      signal(SIGINT, sigint_child_in_fg_handler);
      waitpid(child_pid, NULL, WUNTRACED | WCONTINUED);
      signal(SIGINT, sigint_handler);
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
