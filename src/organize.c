#include "../include/organize.h"
#define LINK_MAX_LEN 256

char *user_home     = NULL;
char *sfo_home      = NULL;
char link_dst[LINK_MAX_LEN];


#define SUCCESS_CREATED_LINKS 0

char sfo_msg_log[SFO_LOG_MSG_LEN];

static void remove_newline(char *str);

static void handle_link_path(const char *type, const char *name) {
    if (type == NULL)
        return;

    memset(link_dst, 0x0, LINK_MAX_LEN);

    user_home = getenv("HOME");
    strncpy(link_dst, user_home, LINK_MAX_LEN); 

    strcat(link_dst, "/");
    strcat(link_dst, ".sfo/");
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
    remove_newline(path);
    struct dirent *file_on_dir = NULL;
    file_info file_info = { 0 };
    char file_full_path[MAX_FILE_PATH_LEN];
    memset(file_full_path, 0x0, MAX_FILE_PATH_LEN);

    DIR *directory = NULL;
    if ((directory = opendir(path)) == NULL) {
        fprintf(stderr, "ERROR on open path (%d)\n", errno);
        return FAIL_OPEN_DIRECTORY;
    }

    while ((file_on_dir = readdir(directory)) != NULL)
    {
        // Check if the file is not a directory
        if (strcmp(file_on_dir->d_name, ".") == 0 || strcmp(file_on_dir->d_name, "..") == 0 || file_on_dir->d_type == DT_DIR) { 
            continue;
        } else {
            memset(file_full_path, 0x0, MAX_FILE_PATH_LEN);
            strncpy(file_info.file_name, file_on_dir->d_name, MAX_FILE_NAME_LEN); // copy the current file name to the buffer
            strncpy(file_full_path, path, MAX_FILE_PATH_LEN);
            strcat(file_full_path, file_on_dir->d_name);
            remove_newline(file_full_path);
            get_file_type(file_full_path, &file_info); // analyse the current file
            handle_types(&file_info);
        }
    }
    
    closedir(directory);

    return 0;
}

static void remove_newline(char *str) {
    if (str == NULL)
        return;

    for (int i = 0; str[i] != 0x0; i++) {
        if (str[i] == '\n') {
            str[i] = 0x00;
            break;
        }
    }
}