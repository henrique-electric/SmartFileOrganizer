
#ifndef FILE_TYPE_DETECTOR
#define FILE_TYPE_DETECTOR

#include <stdio.h>
#include <stdbool.h>
#include <stdint.h>

#define MAX_DESCRIPTION_SIZE 8193 // Storing 8 kb for header file info ( could be changed if necessary )
#define MAX_TYPE_SIZE 129         // 128 for characters and 1 for \0
#define MAX_EXTENSION_SIZE 64     // could be changed ( should be sufficient )

#define MAX_FILE_NAME_LEN 256
typedef struct
{
    unsigned long file_size;
    char details[MAX_DESCRIPTION_SIZE];
    char type[MAX_TYPE_SIZE];
    char extension[MAX_EXTENSION_SIZE];
    char path[MAX_FILE_NAME_LEN];
    char file_name[MAX_FILE_NAME_LEN];
    bool success_analyse;
} file_info;

int get_file_type(const char *file_path, file_info *f_info);
int get_file_size(const char *file_path, file_info *f_info);
int get_file_extension(const char *file_path, file_info *f_info);

int type_categories(const char *file_path, file_info *f_info);

#endif