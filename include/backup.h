#ifndef BACKUP_H
#define BACKUP_H

#include "file_type_detector.h"
#include "errors.h"
#include <dirent.h>
#include <fcntl.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/stat.h>

#define BYTES_PER_READ 512

// Function used to backup the files of a given path
int8_t backup(const char *path);

#endif