#include "../../../include/errors.h"
#include "../../../include/file_type_detector.h"

#include <stdio.h>

const char *image_types[] = {
    "jpg",
    "jpeg",
    "png",
    "gif",
    "bmp",
    "tiff",
    "webp",
    "svg",
    "ico"
};

int get_image_file_info(const char *path)
{
    FILE *fd = fopen(path, "r");

    if (!fd)
    {
        fprintf(stderr, "Error: %s\n", MSG_FAIL_OPEN_FILE);
        return FAIL_OPEN_FILE;
    }

    file_info output;

    int res = get_file_type(path, &output);

    if (res == 0)
    {
        fprintf(stdout, ""
                        "File Type: %s\n"
                        "File Size: %lu bytes\n"
                        "File Extension: %s\n"
                        "File Path: %s\n",
                output.type,
                output.file_size,
                output.extension,
                output.path);

        return 0;
    }
    else
    {
        fprintf(stderr, "Error: %s\n", MSG_FAIL_FILE_INFO_DETAILS);
        return res;
    }

    fclose(fd);
}