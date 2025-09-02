#include <stdio.h>

#include "cli.h"
#include "utils.h"

int main(int argc, char *argv[]) {

  if (argc > 1) {
    return call_parser(argc, argv);
  }

  int status = init();

  return status;
}
