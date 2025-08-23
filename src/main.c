#include <argp.h>
#include <stdio.h>
#include <stdlib.h>

#include "cli.h"
#include "file_type_detector.h"
#include "organize.h"
#include "sound_files/get_sound_file_info.h"
#include "utils.h"

file_info output;
char program_path[256]; // where the user called the program
char *file_path = NULL; // this variable is used to concat where the program was

struct argp_option arguments[] = {
    {"organize", 'o', "organize_path", 0, "Organize {path}", 0},
    {"backup", 'b', "backup_path", 0, "Backup {path}", 0},
    {NULL}};

struct argument_state {
  bool use_organize;
  bool use_backup;
};

static error_t parse_arguments(int key, char *arg, struct argp_state *state) {
  switch (key) {
    case 'b':
      backup(arg);
      break;

    case 'o':
      organize(arg);
      break;

    default:
      return ARGP_ERR_UNKNOWN;
  }

  return 0;
}

int main(int argc, char *argv[]) {
  struct argument_state arguments_struct;
  struct argp argp_struct = {arguments, parse_arguments};
  argp_parse(&argp_struct, argc, argv, 0, 0, &arguments);

  if (argc > 1) {

    char *home = getenv("HOME");
    getcwd(program_path, sizeof(program_path));
    strcat(program_path, "/");
    strcat(home, "/");
    strcat(program_path, argv[1]);
    strcat(program_path, "/");
    
  } else {
    terminal();
  }

  return 0;
}
