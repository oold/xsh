/* xsh - eXperimental SHell
 * log.h - Logging functions
 */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "config.h"
#include "log.h"
#include "util.h"

void log_time();

void *log_file = NULL;

void open_log() {
  char time_str[TIME_STRLEN_DATE_AND_TIME];
  get_time_str(time_str, TIME_STRLEN_DATE_AND_TIME, TIME_FORMAT_FILE_DATE);
  if (*time_str) {
    char log_name[64] = APP_NAME "_";
    strcat(log_name, time_str);
    strcat(log_name, ".log");
    log_file = fopen(log_name, "a");
  } else {
    fputs("WARNING: Cannot retrieve time, using generic log file name\n",
      stderr);
    log_file = fopen(APP_NAME ".log", "a");
  }
  if (!log_file) {
    fputs("WARNING: Cannot open log file\n", stderr);
    return;
  }
  log_time();
  fputs("Opened log file.\n", log_file);
}

void close_log() {
  if (!log_file) {
    fputs("WARNING: Tried to close non-existant log file\n", stderr);
    return;
  }
  log_time();
  fputs("Closing log file.\n", log_file);
  fclose(log_file);
  log_file = NULL;
}

void log_command(const char *const *params) {
  if (!log_file) {
    fputs("WARNING: No log file to log to\n", stderr);
    return;
  }
  log_time();
  size_t i = 0;
  while (1) {
    fputs(params[i], log_file);
    if (!params[++i]) {
      break;
    }
    fputs(" ", log_file);
  }
  fputs("\n", log_file);
  fflush(log_file);
}

void log_time() {
  if (!log_file) {
    fputs("WARNING: No log file to log time to\n", stderr);
    return;
  }
  char time_str[TIME_STRLEN_DATE_AND_TIME];
  get_time_str(time_str, TIME_STRLEN_DATE_AND_TIME, TIME_FORMAT_DATE_AND_TIME);
  if (!*time_str) {
    fputs("WARNING: Cannot retrieve time\n", stderr);
    return;
  }
  fprintf(log_file, "[%s] ", time_str);
}
