#ifndef SFO_LOG_H
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "utils.h"

struct sfo_log_struct {
    time_t raw_log_time;
    struct tm *time_info;
    char *msg_buff;
};
typedef struct sfo_log_struct sfo_log;

void write_log(sfo_log *log);

#endif SFO_LOG_H