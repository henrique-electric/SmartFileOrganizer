
#include "modules/backup/backup.h"
#include "modules/organize/organize.h"
#include "modules/file_status/file_status.h"
#include "modules/organize/sorters/default.h"

#include "cli.h"

static int8_t format_null(sfo_state *state);
static sfo_state main_state;

// Argp stuff

struct argp_option sfo_cli_options[] = {
    {"organize", ARGP_ORGANIZE, "MODE", 0, "Organizes the current directory"},
    {"backup", ARGP_BACKUP, 0, 0, "Backs up the current directory"},
    {NULL}
};

int cli_parser(int key, char *arg, struct argp_state *state) {

	switch (key)
	{
	case ARGP_ORGANIZE:
		if(strcmp(arg, "default") == 0 || *arg == 'd')
            default_sorter("/default");
		break;
	case ARGP_BACKUP:
		// TODO
		break;

	default:
		return ARGP_ERR_UNKNOWN;
	}
	return 0;
}

int call_parser(int argc, char **argv) {
	struct argp argp = {sfo_cli_options, cli_parser};
	return argp_parse(&argp, argc, argv, 0, 0, 0);
}

// End of argp stuff

void handle_organize(sfo_state *state)
{
	organize(state);

	command_state(&main_state);
}

void handle_backup(sfo_state *state)
{    	
	backup_create();
	
	command_state(&main_state);
}

void handle_status(sfo_state *state)
{
	file_status(state);
	
	command_state(&main_state);
}

void handle_exit(sfo_state *state) {
    
	fprintf(stdout, "\nBye, Thanks for using our app :)\n");
    	state->is_running = false;
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
int read_input(sfo_state *state)
{
    
    if (state == NULL)
        return USER_COMMAND_READ_ERROR;


	if(fgets(state->user_input, sizeof(state->user_input), stdin) != NULL)
	{
		state->user_input[strcspn(state->user_input, "\n")] = 0;
	}
	else
		return USER_COMMAND_READ_ERROR;


	switch(state->user_input[0])
	{
		case '1':
		case 'o':
			{
				strcpy(state->user_input, "organize");
			}
			break;
		case '2':
		case 'b':
			{
				strcpy(state->user_input, "backup");
			}
			break;
		case '3':
		case 'e':
		case 'q':
			{
				strcpy(state->user_input, "exit");
			}
			break;
	}
	

    // Get the corresponding handler for the user command, and execute it 
    for (const command_dispatch_table_t *cmd = command_dispatch_table; cmd->command != NULL; ++cmd) {
        if(strcmp(state->user_input, cmd->command) == 0) {
            cmd->handler(state);
            return USER_COMMAND_READ_SUCCESS;
        }
    }

    return USER_COMMAND_READ_ERROR; // Command not found
}

int command_state(sfo_state *state)
{
	fprintf(stdout, "\n[ sfo ]: ");

	while(((state->command_status = read_input(state)) == USER_COMMAND_READ_ERROR) && state->is_running)
	{
		if(state->command_status == USER_COMMAND_READ_ERROR)
			fprintf(stdout, "Invalid option, try again!\n[ sfo ]: ");
	}	

	return 0;
}

int init()
{

	char format_options[32];
	char format_title[32];

	strcpy(format_options, "%-10s%-20s%-20s%-40s\n");
	strcpy(format_title, "\t%40s\n\n");


	fprintf(stdout, format_title, "Smart File Organizer CLI");
    	fprintf(stdout, format_options, "[ 1 ]", "Organize", "o", "Organizing your files as you prefer");
    	fprintf(stdout, format_options, "[ 2 ]", "Backup", "b", "Creating a backup for your files");
    	fprintf(stdout, format_options, "[ 3 ]", "Exit", "e",  "Exits from the Smart file organizer");

	//Initialize the main states
	main_state.is_running = true;


	command_state(&main_state);
}

/*
     A function to dedicate to format the input to change from a \n at the end to \0
 */
static int8_t format_null(sfo_state *state) {
    if (NULL == state)
        return -1;

    char *char_index = strchr(state->user_input, 0xA); // gets the address where \n occour
    if (char_index == NULL) // check if it was found
        return -1;

    *char_index = 0x00; // set the addr to 0x00
    return 0;
}
