#include <argp.h>
#include <stdio.h>
#include <stdlib.h>

#include "../include/cli.h"
#include "../include/file_type_detector.h"
#include "../include/organize.h"
#include "../include/sound_files/get_sound_file_info.h"
#include "../include/utils.h"

file_info output;
char program_path[256]; // where the user called the program
char *file_path = NULL; // this variable is used to concat where the program was
                        // called with the argv[1] (the File)

struct argp_option arguments[] = {
    {"organize", 'o', "organize_path", 0, "Organize {path}", 0},
    {"backup", 'b', "backup_path", 0, "Backup {path}", 0},
    {NULL}};

struct argument_state {
  bool use_organize;
  bool use_backup;
};

static error_t parse_arguments(int key, char *arg, struct argp_state *state) {}

int main(int argc, char *argv[]) {
  if (argc > 1) {

  } else {
    terminal();
  }

  return 0;
}
