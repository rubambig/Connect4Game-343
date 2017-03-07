/********************************************************
* Main method for playing the game
* @author Gloire Rubambiza
* @version 02/17/2017
* Code example and guidance provided by Prof. Ira Woodring
*********************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "handle_arguments.h"
#include "file_utils.h"
#include "connect_four.h"
#define MATCH 0
#define NOMATCH -1

int main(int argc, char** argv){

// Parse the command line arguments
struct arguments* gameArgs = setup(argc, argv);


GameState game; // The representation of the game state
game.currentTurn = 1;

// Check that the players do not want to load a previous game
if (gameArgs->load != NULL){
  
  // Load the game from a local file.
  game = loadgame(&game, gameArgs->load);
  int printer = printboard(&game);
}
else{
  createboard(gameArgs, &game);
}

// Set up all global variables
int currentPlayer, column, size = game.width * game.height;
int colcheck, rowcheck, diagcheck, place_result;
char *tiecheck;
char *save_param = malloc(1024 * sizeof(char));

// Keep playing until we find a winner
while( 1 ){

  // Capture a column from the user.
  currentPlayer = game.currentTurn;
  printf("\nPlace your next piece, player %d\n", currentPlayer);
  scanf("%s %d", save_param, &column);
  
  // Check user input before placing the piece.
  while((place_result = placepiece(&game, column - 1 )) < 0){
    printf("Enter a valid/availaible column, player %d\n", currentPlayer);
    scanf("%s %d", save_param, &column);
  }
  
  
  // Check if the user intends to save the game.
  if(strncmp(save_param, "save=" , 5) == 0){
    
    // Copy the filename.
    char * filename = malloc((strlen(save_param) - 5) * sizeof(char));
    int s_index = 0;
    for( int c = 5; c <= strlen(save_param); c++){
      filename[s_index] = save_param[c];
      s_index++;
    }
    
    // Build the multidimensional string to be saved.
    char ** build = buildstring(&game);
    int write = write_file(build, filename);
    if(write == 0)
      printf("Successfully saved the game to file %s\n", filename);
    else
      printf("Saving the game was unsuccessful");
  }
  else if(strncmp(save_param, "load=" , 5) == 0){
    
    // Copy the filename
    char * filename = malloc((strlen(save_param) - 5) * sizeof(char));
    int s_index = 0;
    for( int c = 5; c <= strlen(save_param); c++){
      filename[s_index] = save_param[c];
      s_index++;
    }
    printf("Loading game from file %s\n", filename);
    
    game = loadgame(&game, filename);
    
    int printer = printboard(&game);
    
  } else {
    
    
    
    
  }
  
  // Make up winning strings based on current game state
  char *p1Win = malloc( game.connectWin * sizeof(char));
  for(int x = 0; x < game.connectWin; x++){
    p1Win[x] = 'X';
  }

  char *p2Win = malloc( game.connectWin * sizeof(char));
  for(int o = 0; o < game.connectWin; o++){
    p2Win[o] = 'O';
  }
  

  //Check the columns, rows, and diagonals;
  if(game.currentTurn == 1){
    colcheck = checkwincol(&game, p1Win, place_result);
    rowcheck = checkwinrow(&game, p1Win, place_result);
    diagcheck = checkwindiag(&game, p1Win, place_result);
  } else {
    colcheck = checkwincol(&game, p2Win, place_result);
    rowcheck = checkwinrow(&game, p2Win, place_result);
    diagcheck = checkwindiag(&game, p2Win, place_result);
  }
  
  // Check for win conditions.
  if(diagcheck == MATCH || colcheck == MATCH || rowcheck == MATCH){
    printf("Player %d has won!\n", game.currentTurn);

    // Ask if the user would like a new game
    char *newgame_op = malloc( 3 * sizeof(char));
    printf("Would you like to keep playing? YES/NO\n");
    scanf("%s", newgame_op);
    
    // Compare user input for next action.
    if(strncmp(newgame_op , "YES", 3) == 0){
      printf("Starting a new game....\n\n\n");
      game = newgame(&game);
      free(newgame_op);
    } 
    else if(strncmp(newgame_op, "NO", 2) == 0) {
      printf("Thanks for playing Connect 4, Happy Coding!\n\n\n");
      free(newgame_op);
      exit(0);
    } else {
      free(newgame_op);
      exit(0);
    }
  } 
  else if((tiecheck = strchr(game.board, '-')) == NULL){
    printf("The game has ended in a tie!\n\n\n");
    
    
    //Ask if the user would like a new game.
    char *tiegame_op = malloc( 3 * sizeof(char));
    printf("Would you like to keep playing? YES/NO\n\n");
    scanf("%s", tiegame_op);
    
    if(strncmp(tiegame_op,"YES", 3) == 0){
	printf("Starting a new game....\n");
	game = newgame(&game);
	free(tiegame_op);
    } else if(strncmp(tiegame_op, "NO", 2) == 0) {
	printf("Thanks for playing Connect 4, Happy Coding!\n");
	free(tiegame_op);
	exit(0);
    } else {
	free(tiegame_op);
	exit(0);
    }
  } else {
    
    // Switch turns between players and keep playing
    if(game.currentTurn == 1){
      game.currentTurn = 2;
    } else {
      game.currentTurn = 1;
    }
    
  }
 
}

return 0; 

}
