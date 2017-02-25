/*********************************************************
Provides the logic for how the arguments will be parsed
@author Gloire Rubambiza
@version 02/17/2017
Code example and guidance provided by Prof. Ira Woodring
*********************************************************/
#include <stdlib.h>
#include "handle_arguments.h"

// Description of the arguments program.
char doc[] = "A program to parse arguments for the connect-4 game in C.";

// Description of the required arguments we accept.
char args_doc[] = "-w or -width for the width of the board \n-h or -height for the height of the board \n-s or -square for a square board\n-c or -connect for the number of connections to win\n-l or -load to load a previously saved game\notherwise a default game is loaded for players\n";

// This option struct is for any optional arguments.
struct argp_option options[] = {
	{"width",	'w',	"WIDTH",	0,	"the width of the board" },
	{"height",	'h',	"HEIGHT",	0,	"the height of the board" },
	{"square",	's',	"SQUARE",		0,	"square for a square board" },
  {"connect", 'c', "CONNECT", 0, "the number of connections to win"},
	{"load",	'l',	"LOAD", 	0, 	"load a previously saved game" },
	{ 0 }
};

// Argp requires us to pass these values in via the argp struct
struct argp argp = { options, parse_opt, args_doc, doc };

// The default arguments struct we will use
struct arguments arguments;

// Function for setting up values after parsing from the command line.
error_t parse_opt(int key, char* arg, struct argp_state *state){
	struct arguments *arguments = state->input;
	switch(key){
		case 'w':
			arguments->width = atoi(arg);
			break;
		case 'h':
			arguments->height = atoi(arg);
			break;
		case 's':
			arguments->square = atoi(arg);
			break;
		case 'c':
			arguments->connectWin = atoi(arg);
			break;
    case 'l':
      arguments->load = arg;
      break;
		default:
			return ARGP_ERR_UNKNOWN;
	}
	return 0;
}

// Set up default values in case the user
// does not enter any values for the arguments
struct arguments* setup(int argc, char** argv){

	// Default of width, height, square, connect, and load
	arguments.width = 7;
	arguments.height = 7;
  arguments.square = 7;
  arguments.connectWin = 4;
	arguments.load = NULL;

	// Call argp to parse command-line arguments
	argp_parse(&argp, argc, argv, 0, 0, &arguments);

	// Return values are in the arguments struct.  Pull
	// them out if they are there.
	int width = arguments.width;
	int height = arguments.height;
  int square = arguments.square;
  int connectWin = arguments.connectWin;
	printf("Width: %d\nHeight: %d\nSquare: %d\nConnectWin: %d\n\n", width, height, square, connectWin);
	if(arguments.load != NULL){
		printf("Load file: %s\n\n", arguments.load);
	}
	return &arguments;
}
