#include "../include/utils.h"


char *get_sfo_home(void) {
    static char sfo_home[SFO_HOME_LEN];
    strcpy(sfo_home, getenv("HOME")); // get the user home folder first

    strcat(sfo_home, "/");    // add a "/" after the the end of the path
    strcat(sfo_home, ".sfo/");

    return sfo_home;
}

