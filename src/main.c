#include <stdio.h>

#include "../include/file_type_detector.h"
#include "../include/organize.h"

file_info output;
char program_path[256]; // where the user called the program
char *file_path = NULL; // this variable is used to concat where the program was called with the argv[1] (the File)

int main(int argc, char *argv[])
{
  printf("Smart File Manager CLI");

  if (argc > 1)
  {
    getcwd(program_path, sizeof(program_path));
    file_path = strcat(program_path, "/");
    file_path = strcat(file_path, argv[1]);
    file_path = strcat(file_path, "/");
    
    printf("%s\n\n", file_path);

    /*
    int result = get_file_type(file_path, &output);
    get_file_size(file_path, &output);
    get_file_extension(file_path, &output);
    
    if (result == 0)
    {
      printf("File Description \n");
      printf("File type: %s\n", output.type);
      printf("File details: %s\n", output.details);
      printf("File size: %ld bytes\n", output.file_size);
      printf("File extension: %s\n", output.extension);
    }
    //Getting more info about the files and categorizing them ( to do )
    type_categories(file_path, &output);

    */

    //Test organizing function
    int organize_output = organize(file_path);
    printf("organize returned: %d\n", organize_output);

  }

  return 0;
}
