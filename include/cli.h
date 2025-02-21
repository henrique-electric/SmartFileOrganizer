#ifndef SFO_CLI_H
#define SFO_CLI_H
#include <stdbool.h>
#include <string.h>
#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include "errors.h"

#define  USR_BUFF_CAP  35 // Just a start value, can be changed as needed

// Using a struct to group variables and make easier to work
struct program_state {
    bool    is_running;                 //stores the current state of the program
    char    input_buff[USR_BUFF_CAP];   //holds the user input
};

/*
    This function is responsible to get the user input and handle it
*/
int read_input(struct program_state *program_struct);

#endif
