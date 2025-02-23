#include "../include/file_type_detector.h"

#include "../include/errors.h"

#include <CUnit/CUnit.h>

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <magic.h>

file_info f_info;

int get_file_size(const char *file_path, file_info *f_info)
{
    struct stat file_stat;

    // Get file size
    int status = stat(file_path, &file_stat);
    if (status == 0)
    {
        f_info->file_size = (size_t)file_stat.st_size;
        return f_info->file_size;
    }
    else
    {
        return status;
    }
}

int get_file_type(const char *file_path, file_info *f_info)
{
    magic_t magic_cookie;

    // Initialize magic library
    magic_cookie = magic_open(MAGIC_MIME_TYPE);

    const char *magic_error_output = magic_error(magic_cookie);

    if(magic_error_output != NULL)
    {
        fprintf(stderr, "Error: %s\n", magic_error_output);
        return MAGIC_ERROR;
    }

    if (magic_cookie == NULL)
    {
        fprintf(stderr, "Failed to initialize magic library.\n");
        f_info->success_analyse = false;
        return FAILED_INIT_MAGIC;
    }

    // Load default magic database
    int magic_loaded = magic_load(magic_cookie, NULL);
    if (magic_loaded != 0)
    {
        fprintf(stderr, "Failed to load magic database: %s\n", magic_error(magic_cookie));
        magic_close(magic_cookie);
        f_info->success_analyse = false;
        return FAILED_LOAD_MAGIC_DATABASE;
    }

    // Check if file can be opened
    FILE *file_name = fopen(file_path, "r");
    if (file_name == NULL)
    {
        fprintf(stderr, "Error opening file: %s\n", strerror(errno));
        return FILE_NOT_FOUND;
    }
    else
    {
        fclose(file_name);
    }

    // Get file MIME type
    const char *mime_type = magic_file(magic_cookie, file_path);

    if (mime_type == NULL)
    {
        fprintf(stderr, "Failed to get file type: %s\n", magic_error(magic_cookie));
        magic_close(magic_cookie);
        f_info->success_analyse = false;
        return FAILED_GET_MIME_TYPE;
    }

    char *type_token = strtok(mime_type, '/'); // Get the type of the file which is the first token

    // Copy the token referring to the type
    strncpy(f_info->file_type, mime_type, strlen(type_token));
    f_info->file_type[strlen(type_token) + 1] = '\0';

    type_token = strtok(NULL, '/');

    // Copy the token referring to the format
    strcpy(f_info->file_format, strtok(f_info, '/'));
    f_info->file_format[strlen(type_token) + 1] = '\0';

    f_info->success_analyse = true;
    magic_close(magic_cookie);

    return 0;
}