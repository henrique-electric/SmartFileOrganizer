#include "../include/organize.h"


/*
    A simple functions to check if the file is a directory
*/
static bool check_is_a_dir(const struct file *file) {
    if (file == NULL)
        return false;

    char *short_type = strtok(file->mime_type, '/'); // Get the string before the '/', which is the type
    if (strcmp(short_type, "inode") == 1) // check if it is an inode (directory)
        return false; // it is a directory, not a valid type

    return true; // the file has a valid type
}

static int8_t handle_types(const struct dirent *file, const file_info *file_info) {
    if (file == NULL || file_info == NULL)
        return ERROR_ON_HANDLE_TYPE; 
    
}

/*
    Function to handle the organize process
*/
int8_t organize(const char *path) {
    if (path == NULL || check_is_a_dir(path) == false) // Check if the path points do a directory
        return ERROR_ON_ORGANIZE_DIR;   


    struct dirent *file_on_dir;         // struct to store the curret file on the dir 
    DIR *dir_pointer = opendir(path);   // pointer to the current directory
    file_info file_type;

    if (dir_pointer == NULL)
        return ERROR_ON_ORGANIZE_DIR;

    while ((file_on_dir = readdir(&dir_pointer)) != NULL) {
        if (check_is_a_dir(path) == true) {
            continue; // the file is a directory, jump to the next file
        } else {
            get_file_type(file_on_dir->d_name, &file_type);
        }
    }

    return 0;
}
