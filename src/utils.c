#include "utils.h"

static char sfo_path_tmp_buff[SFO_HOME_LEN];

char *get_sfo_home(void) {
    strcpy(sfo_path_tmp_buff, getenv("HOME")); // get the user home folder first

    strcat(sfo_path_tmp_buff, "/");    // add a "/" after the the end of the path
    strcat(sfo_path_tmp_buff, ".sfo/");

    return sfo_path_tmp_buff;
}

void flush_std() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF) ;
}