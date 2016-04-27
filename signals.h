/* xsh - eXperimental SHell
 * signals.h - Header for signals.c
 */

#pragma once

#include <stdbool.h>

#include "config.h"

extern bool was_interrupted;

void sigint_handler(int param);
void sigchld_handler(int param);
