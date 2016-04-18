/* xsh - eXperimental SHell
 * signals.h - Header for signals.c
 */

#pragma once

#include "config.h"

void sigint_handler(int param);
void sigchld_handler(int param);
