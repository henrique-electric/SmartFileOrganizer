#include "../include/log.h"

/* 
    Function dedicated to handle the destiny path of the log file, like allocating a buffer.
*/
static void handle_log_path(sfo_log *log_struct) {
    if (log_struct == NULL)
        return;
    
    char *sfo_home = get_sfo_home(); // pointer to the string containig the path to the sfo's home folder
    size_t total_path_len = strlen(sfo_home) + strlen("log.txt") + 1; // calculates the size for a buffer to hold the path to the log file 
    log_struct->file_path = malloc(total_path_len); //  allocates the buffer
    memset(log_struct->file_path, 0x00, total_path_len); // clear the buffer (might be useful to save time by no needing to place a null char at the end of string)

    strcpy(log_struct->file_path, sfo_home); // copy the path to the sfo home
    strcat(log_struct->file_path, SFO_LOG_FILE_NAME);  // add the name of the file
}

/*
    Function used to get the current time when writing the log
*/
static void handle_time(sfo_log *log_struct) {
    if (log_struct == NULL)
        return;

    time(&log_struct->raw_log_time);    // Get the current system time in a raw value
    log_struct->time_info = localtime(&log_struct->raw_log_time);  // transform the raw time value into a organized struct
    log_struct->ascii_time = asctime(log_struct->time_info);       // Translate to a human readble string

    log_struct->ascii_time[strlen(log_struct->ascii_time) + 1] = 0x00; // Remove the '\n' character
}

void write_log(const char *msg) {
    sfo_log new_log;
    
    handle_time(&new_log);

    size_t msg_buff_len = strlen(msg) + strlen(new_log.ascii_time) + strlen(" ----> ") + 1; // Calculate how many bytes should be allocated for the message, + the time and a arrow to separate
    new_log.msg_buff = malloc(msg_buff_len + 1); // Allocate the buffer to hold the message
    if (new_log.msg_buff == NULL)
        return;

    memset(new_log.msg_buff, 0x00, msg_buff_len); // Set the buffer to zero


    strcpy(new_log.msg_buff, new_log.ascii_time);
    strcat(new_log.msg_buff, " ----> ");
    strcat(new_log.msg_buff, msg);
    strcat(new_log.msg_buff, "\n");
    handle_log_path(&new_log);

    new_log.log_file_ptr = fopen(new_log.file_path, "a");
    if (new_log.log_file_ptr != NULL) {
        fwrite(new_log.msg_buff, sizeof(char), msg_buff_len, new_log.log_file_ptr);
        fclose(new_log.log_file_ptr);
    }

    free(new_log.msg_buff);
    free(new_log.file_path);
}