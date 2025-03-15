#include "../include/organize.h"

const char *image_types[] = {"png", "jpeg", "jpg", "gif", "bmp", "tiff", "webp", "x-icon"};

char *user_home = NULL;
char *file_name = NULL;
char sfo_home[1024];
char links_path[1024];
bool is_image = false;

#define SUCCESS_CREATED_IMAGE_LINKS 0

// Current working director

static int handle_images(const file_info *file_info)
{
    if (file_info == NULL)
        return -1;

    if (symlink(file_info->path, "link_image") == -1)
    {
        printf("%s\n", file_info->path);
        fprintf(stderr, "Error: %s\n", MSG_FAIL_CREATE_SYMBOLIC_LINK);
        return FAIL_CREATE_SYMBOLIC_LINK;
    }

        return 0;
}

static int handle_types(const file_info *file_info)
{
    if (file_info == NULL)
        return FAIL_HANDLE_TYPE;

    for (int i = 0; i < IMAGE_TYPE_ARRAY_LEN; i++)
    {
        if (strcmp(file_info->extension, image_types[i]) == 0)
        {
            is_image = true;
            break;
        }
    }

    if (is_image)
    {
        if (!mkdir(sfo_home, 0755)) // create a directory for images
        {
            fprintf(stderr, "Error: %s\n", MSG_FAIL_CREATE_DIRECTORY);
            return FAIL_CREATE_NEW_DIRECTORY;
        }

        //TO DO ( maybe copying the original image files into newly created folder (images))

        handle_images(file_info);
    }
}

/*
    Function to handle the organize process
*/
int organize(char *path)
{

    struct dirent *file_on_dir = NULL;
    file_info file_info = { 0 };

    DIR *directory = opendir(path);

    while ((file_on_dir = readdir(directory)) != NULL)
    {
       if (file_on_dir->d_type == 8) {
            get_file_type(strcat(path, file_on_dir->d_name), &file_info);
            get_file_extension(strcat(path, file_on_dir->d_name), &file_info);
            //get_file_size(strcat(path, file_on_dir->d_name), &file_info);

            printf("%s\n", file_info.extension);
            handle_types(&file_info);
       }
    }
    
    closedir(directory);

    return 0;
}
