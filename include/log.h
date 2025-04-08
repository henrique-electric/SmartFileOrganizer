#ifndef SFO_LOG_H
#define SFO_LOG_H

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "utils.h"


#define SFO_LOG_FILE_NAME "log.txt" // name for the log file (can be changed as needed)

typedef struct sfo_log_struct {
    time_t raw_log_time;
    struct tm *time_info;
    char *ascii_time;
    char *msg_buff;
    char *file_path;
    FILE *log_file_ptr;
} sfo_log;

void write_log(const char *msg);

#endif