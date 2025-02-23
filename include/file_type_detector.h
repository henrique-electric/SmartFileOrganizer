
#ifndef FILE_TYPE_DETECTOR
#define FILE_TYPE_DETECTOR

#include <stdio.h>
#include <stdbool.h>
#include <stdint.h>

#define MAXIMUM_LENGTH 30 // Maximum length of MIME types 128 + 1 for null character

typedef struct file
{
    size_t file_size;
    char   file_type[MAXIMUM_LENGTH];
    char   file_format[MAXIMUM_LENGTH];
    bool success_analyse;
} file_info;

int get_file_type(const char *file_path, file_info *file);
int get_file_size(const char *file_path, file_info *file);

#endif