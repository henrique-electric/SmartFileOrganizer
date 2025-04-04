#ifndef BACKUP_H
#define BACKUP_H

#include "file_type_detector.h"
#include "errors.h"
#include "utils.h"
#include <dirent.h>
#include <fcntl.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/stat.h>

#define BYTES_PER_RW 512

#define SUCCESS_ON_COPY   0
#define ERROR_ON_COPY    -1
#define SUCCESS_ON_BACKUP 0
#define ERROR_ON_BACKUP  -1

// Function used to backup the files of a given path
int8_t backup(const char *path);

#endif