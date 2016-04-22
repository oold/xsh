/* xsh - eXperimental SHell
 * config.h - Contains compile-time configuration
 */

#pragma once

#define APP_NAME "xsh"
// Initial size of command and arguments
#define COMMAND_LENGTH 16
// Initial size of array holding pointers to parameters
#define PARAMETERS_SIZE 4
// Format string for date and time
#define TIME_FORMAT_DATE_AND_TIME "%a %d %b %Y %X"
// Size of date and time string; update if format string changes!
#define TIME_STRLEN_DATE_AND_TIME 32
// Format string for file date
#define TIME_FORMAT_FILE_DATE "%F"
// Size of file date string; update if format string changes!
#define TIME_STRLEN_FILE_DATE 11
