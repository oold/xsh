/* xsh - eXperimental SHell
 * log.h - Header for log.c
 */

#pragma once

#include "config.h"

void open_log();
void close_log();
void log_command(const char *const *params);
