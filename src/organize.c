#include "../include/organize.h"
#define LINK_MAX_LEN 256

const char *image_types[] = {"PNG", "JPEG", "JPG", "GIF", "BMP", "TIFF", "WEBP", "X-ICON"};

char *user_home     = NULL;
char *sfo_home      = NULL;
char link_dst[LINK_MAX_LEN];


#define SUCCESS_CREATED_LINKS 0

static void handle_link_path(const char *type, const char *name) {
    if (type == NULL)
        return;

    user_home = getenv("HOME");
    strncpy(link_dst, user_home, LINK_MAX_LEN); 

    strcat(link_dst, "/");
    strcat(link_dst, ".sfo/");
    strcat(link_dst, type); // concat the type
    strcat(link_dst, "/");  // add a / after the type

    mkdir(link_dst, 0777);

    strcat(link_dst, name); // add the file name at the end of the path
}

static int handle_types(const file_info *file_info)
{
    if (file_info == NULL)
        return FAIL_HANDLE_TYPE;

    handle_link_path(file_info->type, file_info->file_name);
    if(symlink(file_info->path, link_dst) == -1) {
    
        fprintf(stderr, MSG_FAIL_CREATE_SYMBOLIC_LINK);
        return FAIL_CREATE_SYMBOLIC_LINK;
    }
    printf("Symlink created at %s\n", link_dst);
    return SUCCESS_CREATED_LINKS;
}

/*
    Function to handle the organize process
*/
int organize(char *path)
{
    struct dirent *file_on_dir = NULL;
    file_info file_info = { 0 };

    DIR *directory = NULL;
    if ((directory = opendir(path)) == NULL) {
        fprintf(stderr, "ERROR on open path (%d)\n", errno);
        return FAIL_OPEN_DIRECTORY;
    }

    while ((file_on_dir = readdir(directory)) != NULL)
    {
        // Check if the file is not a directory
        if (strcmp(file_on_dir->d_name, ".") == 0 || strcmp(file_on_dir->d_name, "..") == 0) { 
            continue;
        } else {
            strncpy(file_info.file_name, file_on_dir->d_name, MAX_FILE_NAME_LEN); // copy the current file name to the buffer
            get_file_type(strcat(path, file_on_dir->d_name), &file_info); // analyse the current file
            handle_types(&file_info);
            
        }
    }
    
    closedir(directory);

    return 0;
}
