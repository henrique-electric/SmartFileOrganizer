#include <stdio.h>

#include "../include/file_type_detector.h"
#include "../include/sound_files/get_sound_file_info.h"
#include "../include/organize.h"
#include "../include/cli.h"
#include "../include/utils.h"

file_info output;
char program_path[256]; // where the user called the program
char *file_path = NULL; // this variable is used to concat where the program was called with the argv[1] (the File)

int main(int argc, char *argv[])
{

  if (argc > 1)
  {

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
