#include "../include/organize.h"

/*
    A simple functions to check if the file is a directory
*/
static bool check_is_valid(const struct file *file) {
    if (file == NULL)
        return false;

    char *short_type = strtok(file->mime_type, '/'); // Get the string before the '/', which is the type
    if (strcmp(short_type, "inode") == 1) // check if it is an inode (directory)
        return false; // it is a directory, not a valid type

    return true; // the file has a valid type
}