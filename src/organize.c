#include "../include/organize.h"

const char *image_types[] = {"PNG", "JPEG", "JPG", "GIF", "BMP", "TIFF", "WEBP", "X-ICON"};

char *user_home = NULL;
char *sfo_home  = NULL;
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
        //printf("%s\n", file_info->path);
        fprintf(stderr, "Error: %s\n", MSG_FAIL_CREATE_SYMBOLIC_LINK);
        return FAIL_CREATE_SYMBOLIC_LINK;
    }

        return 0;
}

static int handle_types(const file_info *file_info)
{
    if (file_info == NULL)
        return FAIL_HANDLE_TYPE;

    user_home = getenv("HOME");
    sfo_home = strcat(user_home, "/.sfo/");

    for (int i = 0; i < IMAGE_TYPE_ARRAY_LEN; i++)
    {
        if (strcmp(file_info->type, image_types[i]) == 0)
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

    DIR *directory = NULL;
    if ((directory = opendir(path)) == NULL) {
        fprintf(stderr, "ERROR on open path (%d)\n", errno);
    }

    while ((file_on_dir = readdir(directory)) != NULL)
    {
        // Check if the file is not a directory
        if (strcmp(file_on_dir->d_name, ".") == 0 || strcmp(file_on_dir->d_name, "..") == 0) { 

            continue;
        } else {
            get_file_type(strcat(path, file_on_dir->d_name), &file_info);
            handle_types(&file_info);
        }

        
       
    }
    
    closedir(directory);

    return 0;
}
