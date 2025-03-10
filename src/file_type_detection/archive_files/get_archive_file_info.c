#include "../../../include/errors.h"
#include "../../../include/archive_files/get_archive_file_info.h"

int get_archive_file_info(const char *path)
{

    FILE *fd = fopen(path, "r");

    if (!fd)
    {
        fprintf(stderr, "Error: %s\n", MSG_FAIL_OPEN_FILE);
        return FAIL_OPEN_FILE;
    }

    struct archive *arch = archive_read_new();
    struct archive_entry *arch_entry;
    if (!arch)
    {
        fprintf(stderr, "Error: %s\n", MSG_FAIL_CREATE_ARCHIVE_STRUCT);
        return FAIL_CREATE_ARCHIVE_STRUCT;
    }

    if (archive_read_support_filter_all(arch) != ARCHIVE_OK)
    {
        fprintf(stderr, "Error: %s\n", MSG_FAIL_SUPPORT_ARCHIVE_FILTERS);
        return FAIL_SUPPORT_ARCHIVE_FILTERS;
    }

    if (archive_read_support_format_all(arch) != ARCHIVE_OK)
    {
        fprintf(stderr, "Error: %s\n", MSG_SUPPORT_ARCHIVE_FORMATS);
        return FAIL_SUPPORT_ARCHIVE_FORMATS;
    }

    if (archive_read_open_FILE(arch, fd) != ARCHIVE_OK)
    {
        fprintf(stderr, "Error: %s\n", MSG_FAIL_OPEN_ARCHIVE_FILE);
        return FAIL_OPEN_ARCHIVE_FILE;
    }

    //Reading
    printf("\nArchive contents:\n");
    int i = 1;
    while (archive_read_next_header(arch, &arch_entry) == ARCHIVE_OK)
    {
        printf("file %d: %s\n", i++, archive_entry_pathname(arch_entry));
        archive_read_data_skip(arch);
    }
    printf("\nNumber of file/s inside the archive: %d\n", archive_file_count(arch));
    printf("Format name: %s\n", archive_format_name(arch));
    printf("Filter code: %d\n", archive_filter_code(arch, 0));
    printf("Archive format code: 0x%x\n", archive_format(arch));

    archive_read_close(arch);
    archive_read_free(arch);
    fclose(fd);

    return SUCCESS_READ;
}