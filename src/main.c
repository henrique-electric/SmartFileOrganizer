#include <stdio.h>
#include <argp.h>

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
