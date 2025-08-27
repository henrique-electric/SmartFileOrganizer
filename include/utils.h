#ifndef SFO_UTILS_H
#define SFO_UTILS_H

#include <string.h>
#include <stdlib.h>
#include <stdio.h>

#define SFO_HOME_LEN 512

char *get_sfo_home(void);
void flush_std();

#endif