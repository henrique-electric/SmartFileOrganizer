#include "../include/backup.h"

#define DST_PATH_MAX_LEN 256

char backup_path[DST_PATH_MAX_LEN];

/*
    A function implementation to copy the files. (Can be modified to become more optmized or be removed to use other one)
*/
static int8_t copy_file(const char *file, const char *path, const file_info *file_struct) {
    if (file == NULL || path == NULL || file_struct == NULL)
        return ERROR_ON_COPY;

    
    struct stat file_info; // struct to store info about the file (Planned to be removed)
    if (stat(file, &file_info) == -1)
        return ERROR_ON_COPY;
    
    
    FILE *src_file = fopen(file, "r");
    if (file == NULL)
        return ERROR_ON_COPY;

    static char dst_path_buff[DST_PATH_MAX_LEN]; // Creates a buffer to hold the destiny path where the backup will be
    static uint8_t copy_tmp_buff[BYTES_PER_RW]; // buffer to hold the data from the original file

    // Sets the destiny path with the backup file with the same name as the orignial
    strncpy(dst_path_buff, file, DST_PATH_MAX_LEN);
    strncat(dst_path_buff, file, DST_PATH_MAX_LEN);

    FILE *dst_file = fopen(dst_path_buff, "a"); // creates the backup file
    if (dst_file == NULL) {
        fclose(src_file); // closes the src file and aborts the program
        return ERROR_ON_COPY;
    }

    // Reads the data from the original file to buffer and write to the backup file
    while (fread(copy_tmp_buff, sizeof(uint8_t), BYTES_PER_RW, src_file) > 0)
        fwrite(copy_file, sizeof(uint8_t), BYTES_PER_RW, dst_file);
    
    fclose(src_file);
    fclose(dst_file);

    return SUCCESS_ON_COPY;

}

int8_t backup(const char *path) {
    if (path == NULL)
        return -1;

    struct dirent *file_on_dir = NULL;
    DIR *directory = NULL;

    if (opendir(path) == NULL) {
        sfo_abort(MSG_FAIL_CREATE_BACKUP);
        return -1;
    }

    file_info file; // store info about the file

    strcpy(get_sfo_home(), backup_path);
    strcat(backup_path, "backups/");
    
    char *tmp_path_buff = NULL; // pointer to the temporary buffer

    // Main part of the function, it will read the next file in the dir and create a copy of it
    while ((file_on_dir = readdir(directory)) != NULL) {
        tmp_path_buff = malloc(strlen(path) + strlen(file_on_dir->d_name) + 1); // Allocate a dynamic memory to hold the path + the file
        if (tmp_path_buff == NULL)
            return ERROR_ON_BACKUP;

        strcpy(tmp_path_buff, path); // copies the path to the buffer
        strcat(path, file_on_dir->d_name); // add the file name at the end of the path
        
        get_file_type(path, &file); // Analyze the file

        // Try to create a copy of the file
        if(copy_file(path, backup_path, &file) == ERROR_ON_COPY) { 
            free(tmp_path_buff);
            return ERROR_ON_BACKUP;
        }
        
        free(tmp_path_buff); // Free the temporary buffer 
        tmp_path_buff = NULL; // Sets it to NULL to avoid UAF (use after free)
    }
    

    return SUCCESS_ON_BACKUP; // backup was successfully 
}