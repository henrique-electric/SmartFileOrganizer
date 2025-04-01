#include <stdio.h>

#include "../include/file_type_detector.h"
#include "../include/sound_files/get_sound_file_info.h"
#include "../include/organize.h"
#include "../include/cli.h"

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
    
    if (result == 0)
    {
      printf("File Description \n");
      printf("File type: %s\n", output.type);
      printf("File details: %s\n", output.details);
      printf("File size: %ld bytes\n", output.file_size);
      printf("File extension: %s\n", output.extension);

      //Test get_archive_file_info()
      if(strcmp(output.extension, "zip") == 0)
      {
        int archive_output = get_archive_file_info(path);
      }
    }
    //Getting more info about the files and categorizing them ( to do )
    type_categories(path, &output);

    //Test organizing function
    int organize_output = organize(&output);
    printf("organize returned: %d\n", organize_output);
  }

  return 0;
}
