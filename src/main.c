#include <stdio.h>
#include <argp.h>
#include <getopt.h>

const char *argp_program_version      = "Smart File Organizer v0.1";
const char *argp_program_error_report = "Open a issue in https://github.com/Shadabdullah/SmartFileOrganizer";

struct argp_option argument_options[] = {
  /*
      Setup options to be used on the program
  */

  {0} // Necessery at the end of the argument list
};

int main(int argc, const char **argv)
{
  printf("Smart File Manager CLI");
  return 0;
}
