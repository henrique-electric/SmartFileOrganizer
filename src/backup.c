#include "../include/backup.h"

static int8_t copy_file(const char *file, const char *path) {
    if (file == NULL || path == NULL)
        return -1;

    struct stat file_info;

    if (stat(file, &file_info) == -1)
        return -1;
    
    size_t file_size; // store the file size. Will be used when reading the file

    FILE *src_file = fopen(file, "r");
    FILE *dst_file = fopen()
    if (file == NULL)
        return -1;

    

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

    while ((file_on_dir = readdir(directory)) != NULL) {
        
    }

    return 0;
}