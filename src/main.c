#include <stdio.h>

#include "../include/file_type_detector.h"
#include "../include/sound_files/get_sound_file_info.h"
#include "../include/organize.h"

file_info output;

int main(int argc, char *argv[])
{
  printf("Smart File Manager CLI");

  if (argc > 1)
  {
    printf("argv[1]: %s\n", argv[1]);
    const char *path = argv[1];

    int result = get_file_type(path, &output);
    get_file_size(path, &output);
    get_file_extension(path, &output);
    
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
