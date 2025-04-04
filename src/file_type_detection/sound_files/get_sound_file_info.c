#include "../../../include/sound_files/get_sound_file_info.h"

#include <sndfile.h>

int get_file_sound_info(const char *file_path, SF_INFO *sf_info)
{
    SNDFILE *sound_file = sf_open(file_path, SFM_READ, sf_info);

    if (!sound_file)
    {
        fprintf(stderr, "%s: %s\n", MSG_FAIL_OPEN_FILE, sf_strerror(sound_file));
        return -1;
    }

    fprintf(stdout, "\nSound file info: \n");
    fprintf(stdout, "Sample rate: %d\n", sf_info->samplerate);
    fprintf(stdout, "Channels: %d\n", sf_info->channels);
    fprintf(stdout, "Format: 0x%0x\n", sf_info->format);
    fprintf(stdout, "Sections: %d\n", sf_info->sections);
    fprintf(stdout, "Seekable: %d\n", sf_info->seekable);

    return 0;
}