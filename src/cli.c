#include "../include/cli.h"

// Static function declare
static int8_t format_null(struct program_state *program_struct);

void handle_organize(struct program_state *program_struct) {
    // TODO: Implement organize command
}

void handle_backup(struct program_state *program_struct) {
    // TODO: Implement backup command
}

void handle_status(struct program_state *program_struct) {
    // TODO: Implement status command
}

void handle_exit(struct program_state *program_struct) {
    printf("Bye :)\n");
    program_struct->is_running = false;
}

/*
    A function dispatch table for CLI user commands.
    It maps a user command to the function that handles that command.
*/
const command_dispatch_table_t command_dispatch_table[] = {
    {CMD_ORGANIZE, handle_organize},
    {CMD_BACKUP, handle_backup},
    {CMD_STATUS, handle_status},
    {CMD_EXIT, handle_exit},
    {NULL, NULL} // Sentinel value to mark the end of the dispatch table
};

/*
    Function to handle user input
*/
int read_input(struct program_state *program_struct) {
    if (NULL == program_struct)
        return USER_COMMAND_READ_ERROR;

    fgets(program_struct->input_buff, USR_BUFF_CAP, stdin); // Get the input
    if (format_null(program_struct) != 0)
        return USER_COMMAND_READ_ERROR;

    // Get the corresponding handler for the user command, and execute it 
    for (const command_dispatch_table_t *cmd = command_dispatch_table; cmd->command != NULL; ++cmd) {
        if (strcmp(program_struct->input_buff, cmd->command) == 0) {
            cmd->handler(program_struct);
            return USER_COMMAND_READ_SUCCESS;
        }
    }

    return USER_COMMAND_READ_ERROR; // Command not found
    return USER_COMMAND_READ_SUCCESS;
}

/*
    A function to dedicate to format the input to change from a \n at the end to \0
*/
static int8_t format_null(struct program_state *program_struct) {
    if (NULL == program_struct)
        return -1;

    char *char_index = strchr(program_struct->input_buff, 0xA); // gets the address where \n occour
    if (char_index == NULL) // check if it was found
        return -1;

    *char_index = 0x00; // set the addr to 0x00
    return 0;
}
