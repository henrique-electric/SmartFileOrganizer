#ifndef SFO_UTILS_H
#define SFO_UTILS_H

#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>

#define SFO_HOME_LEN 512

// Colors of output
#define RED_COLOR       "\033[0;31m"
#define GREEN_COLOR     "\033[0;32m"
#define YELLOW_COLOR    "\033[0;33m"
#define BLUE_COLOR      "\033[0;34m"
#define MAGENTA_COLOR   "\033[0;35m"
#define CYAN_COLOR      "\033[0;36m"
#define WHITE_COLOR     "\033[0;37m"

char *get_sfo_home(void);
void flush_std();

#endif