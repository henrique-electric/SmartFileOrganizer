#ifndef FILE_ARCHIVE_INFO
#define FILE_ARCHIVE_INFO

#include <archive.h>
#include <archive_entry.h>

#define SUCCESS_READ 0

int get_archive_file_info(const char *path);

#endif