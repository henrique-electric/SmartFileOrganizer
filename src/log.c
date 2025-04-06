#include "../include/log.h"

void write_log(sfo_log *log) {
    char   *sfo_home = get_sfo_home();
    char log_path_buff[strlen(sfo_home) + strlen("log.txt") + 1];
    strcpy(log_path_buff, sfo_home);
    strcat(log_path_buff, "log.txt");


    FILE *log_file = fopen(log_path_buff, "a");
    fwrite(log->msg_buff, sizeof(char), strlen(log->msg_buff), log_file);
    fclose(log_file);
}