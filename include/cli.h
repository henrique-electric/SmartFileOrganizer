#ifndef SFO_CLI_H
#define SFO_CLI_H

// Standard includes
#include <stdbool.h>
#include <string.h>
#include <stdio.h>
#include <stdint.h>
#include <string.h>
//

// Module includes
#include "organize.h"
#include "backup.h"


#define CMD_BACKUP "backup"
#define CMD_EXIT "exit"
#define CMD_ORGANIZE "organize"
#define CMD_STATUS "status"

#define USER_COMMAND_READ_ERROR -1
#define USER_COMMAND_READ_SUCCESS 0

#define  USR_BUFF_CAP  35
#define  USR_PATH_LEN  256


// Using a struct to group variables and make easier to work
struct program_state {
    bool    is_running;                 // stores the current state of the program
    char    input_buff[USR_BUFF_CAP];   // holds the user input
    char    path_buff[USR_PATH_LEN];    // Holds the path that the user want to use the program
};

typedef struct program_state program_state_t;

/*
    The function signature for a command handler function.

    The handler must take a single argument of type `program_state *`,
        and it must return `void`.
*/
typedef void (*command_handler_t)(struct program_state *);

// This struct groups a user command with its corresponding handler function
typedef struct
{
    const char *command;
    command_handler_t handler;
} command_dispatch_table_t;

// Command handler prototypes
void handle_organize(struct program_state *program_struct);
void handle_backup(struct program_state *program_struct);
void handle_status(struct program_state *program_struct);
void handle_exit(struct program_state *program_struct);

/*
    This function is responsible to get the user input and handle it
*/
int read_input(struct program_state *program_struct);

// Function that starts a terminal to get the user command
void terminal();

#endif
