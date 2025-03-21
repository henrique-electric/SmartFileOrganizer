#ifndef SFO_ORGANIZE_H
#define SFO_ORGANIZE_H
#include <string.h>
#include <stdint.h>
#include <dirent.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <errno.h>
#include <sys/stat.h>
#include "file_type_detector.h"
#include "errors.h"

#define FAIL_HANDLE_TYPE -1
#define FAIL_ORGANIZE_FILES -1

#define IMAGE_TYPE_ARRAY_LEN 7


int organize(char *path);

#endif