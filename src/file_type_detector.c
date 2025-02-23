#include "../include/file_type_detector.h"

#include "../include/errors.h"

#include <stdio.h>
#include <errno.h>
#include <stdlib.h>
#include <string.h>

#include <sys/stat.h> // Get file size

#include <magic.h> // Load magic database, mimetypes, file descriptor and so on

#include <fcntl.h>  // File Control Options
#include <unistd.h> //Close

#define FILE_BUFFER_SIZE 8192 // Reading by chunk size of 8 kb

int get_file_size(const char *file_path, file_info *f_info)
{
    struct stat file_stat;

    // Get file size
    unsigned long status = stat(file_path, &file_stat);
    if (status == 0)
    {
        f_info->file_size = (unsigned long)file_stat.st_size;
        return f_info->file_size;
    }
    else
    {
        return status;
    }
}

int get_file_type(const char *file_path, file_info *f_info)
{
    magic_t magic_cookie;

    // Initialize magic library
    magic_cookie = magic_open(MAGIC_NONE);

    if (magic_cookie == NULL)
    {
        fprintf(stderr, MSG_FAIL_INIT_MAGIC);
        f_info->success_analyse = false;
        return FAIL_INIT_MAGIC;
    }

    // Load default magic database
    int magic_loaded = magic_load(magic_cookie, NULL);

    if (magic_loaded != 0)
    {
        fprintf(stderr, "%s: %s\n", MSG_FAIL_MAGIC_LOAD, magic_error(magic_cookie));

        magic_close(magic_cookie);

        f_info->success_analyse = false;

        return FAIL_LOAD_MAGIC_DATABASE;
    }

    // Check if file can be opened for read only
    int file_descriptor = open(file_path, O_RDONLY);

    if (file_descriptor == -1)
    {
        fprintf(stderr, "%s: %s\n", MSG_FAIL_OPEN_FILE, strerror(errno));

        magic_close(magic_cookie);

        f_info->success_analyse = false;

        return FAIL_OPEN_FILE;
    }
    else
    {
        // Storing into buffer and getting more information about the file descriptor
        unsigned char file_buffer[FILE_BUFFER_SIZE];
        ssize_t file_bytes_read = read(file_descriptor, file_buffer, sizeof(file_buffer));

        if (file_bytes_read == -1)
        {
            fprintf(stderr, "%s: %d\n", MSG_FAIL_FILE_BYTES_READ, errno);

            close(file_descriptor);
            magic_close(magic_cookie);

            f_info->success_analyse = false;

            return FAIL_BYTES_READ;
        }
        else
        {
            const char *file_info_details = magic_buffer(magic_cookie, file_buffer, file_bytes_read);

            if (file_info_details == NULL)
            {
                fprintf(stderr, "%s: %s\n", MSG_FAIL_FILE_INFO_DETAILS, magic_error(magic_cookie));

                close(file_descriptor);
                magic_close(magic_cookie);

                f_info->success_analyse = false;

                return FAIL_FILE_INFO_DETAILS;
            }

            strncpy(f_info->details, file_info_details, strlen(file_info_details)); // Copying details
            f_info->details[strlen(file_info_details) + 1] = '\0';

            char type_buff[8193]; // Buffer for copying details

            strncpy(type_buff, f_info->details, strlen(f_info->details)); // Copy details to buffer
            type_buff[strlen(f_info->details) + 1] = '\0';

            char *output = strtok(type_buff, ","); // Get only first part (the file type)
            if (output)
            {
                //Copying type
                strncpy(f_info->type, type_buff, strlen(type_buff));
                f_info->type[strlen(type_buff) + 1] = '\0';
            }
        }

        close(file_descriptor);
    }

    f_info->success_analyse = true;
    magic_close(magic_cookie);

    return 0;
}