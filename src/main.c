#include <stdio.h>
#include <argp.h>
#include <stdbool.h>

#define MOVE_ID   1 // number used to identify the move argument on parse_opt()
#define SORT_ID   2 // number used to identify the sort argument on parse_opt();

const char version_out[]   = "Simple File Organizer v0.1";          // Text that will show on --version
const char doc_out[]       = "A simple program to organize files";  // text that will show after the usage on --help
const char args_doc[]    = " ";  // argumets that will show on the --help   ex: "Usage: sfo [OPTION...] X"

/*
    Struct that will contain the arguments the program will have
*/
struct arguments {
  bool move;
  bool sort;
  bool no_opt;
};

struct argp_option argument_options[] = {
  { "move", MOVE_ID, NULL, 0, "moves the files"},  // Need to think on argument that move option will take
  { "sort", SORT_ID, NULL, 0, "sorts the files"},  // Need to think on argument that sort option will take
  {0}                                              // Necessery at the end of the argument list
};

/*
  Function to handle the arguments
*/
error_t parse_arguments (int key, char *arg, struct argp_state *state) {
  struct arguments *args = state->input; // Points to the current arguments struct which was passed on the main()

  switch (key)
  {
  case MOVE_ID:
    args->move = true;
    break;
  
  case SORT_ID:
    args->sort = true;
    break;

  case ARGP_KEY_ARG:
    // Handle when no options are passed
    break;

  default:
    return ARGP_ERR_UNKNOWN;
  }

    return 0;
}

struct argp argp = { argument_options, parse_arguments, args_doc, doc_out};

int main(int argc, const char **argv)
{
  struct arguments args; // struct that will contain the arguments passed
  argp_parse(&argp, argc, (char **restrict) argv, 0, 0, &args); // handle the arguments

  return 0;
}
