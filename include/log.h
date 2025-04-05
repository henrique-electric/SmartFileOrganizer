#ifndef SFO_LOG_H
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

struct sfo_log_struct {
    time_t raw_log_time;
    struct tm *time_info;
    char *msg_buff;
};

#endif SFO_LOG_H