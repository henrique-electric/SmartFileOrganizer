#include "../include/modules/backup/backup.h"

#include "../include/cli.h"

// Static function declare
static int8_t format_null(struct program_state *program_struct);
static program_state_t main_program_state;

void handle_organize(struct program_state *program_struct) {
    printf("Enter the path to organize: ");
    fgets(program_struct->path_buff, USR_PATH_LEN, stdin); // get the path to organize
    program_struct->path_buff[strlen(program_struct->path_buff) - 1] = 0x00; // removes the \n from the user input (I hate this character XD)
    organize(program_struct->path_buff); // call the organize module
}

void handle_backup(struct program_state *program_struct) {
    printf("Enter the path to backup: ");
    fgets(program_struct->path_buff, USR_PATH_LEN, stdin);
    program_struct->path_buff[strlen(program_struct->path_buff) - 1] = 0x0; // Removing th e\n from the user input (AGAIN!!!)

  backup_create(program_struct->path_buff);
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
    {handle_organize},
    {handle_backup},
    {handle_exit},
    {handle_status}, // TODO
};

/*
    Function to handle user input
*/
int handle_input(struct program_state *program_struct) {
    //To Do
    if (NULL == program_struct)
        return USER_COMMAND_READ_ERROR;


    program_struct->user_input = read_int();
    while (program_struct->user_input < 1 || program_struct->user_input > 3) {
        printf("invalid command, try again: ");
        program_struct->user_input = read_int();
    }

    flush_std();
    command_dispatch_table[program_struct->user_input - 1].handler(program_struct);

    return USER_COMMAND_READ_ERROR; // Command not found
}

void terminal() {
    puts("Smart File Organizer CLI");
    puts("[ 1 ] Organize");
    puts("[ 2 ] Backup");
    puts("[ 3 ] exit");
    printf("Enter an option: ");

   handle_input(&main_program_state);
} 

/*
     A function to dedicate to format the input to change from a \n at the end to \0
 */
