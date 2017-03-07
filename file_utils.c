/********************************************************
* File utils for saving and loading the game
* @author Gloire Rubambiza
* @version 03/01/2017
*********************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <string.h>
#include "connect_four.h"

#define SUCCESS 0;
#define FAILURE -1;

/**************************************
* Loads a saved game from a local file
* @param filename the local file
* @param game the state to be updated
*************************************/
GameState loadgame(GameState* game, char * filename){
  FILE *fin = fopen(filename, "r");
  int prev_player = -1;
  // Save the previous player to keep playing next
  if(game->currentTurn == 0)
    prev_player = 1;
  else
    prev_player = game->currentTurn;
  
  
  // Check that the file was opened correctly.
  if(fin == NULL){
    fprintf(stderr, "Error opening a file named: [%s]\n", filename);
    exit(1);
  }
  
  
  // Scan for the new dimensions.
  fscanf(fin, "%d\n%d\n%d", &game->width, &game->height, &game->connectWin);
  
  
  // Allocate space for a buffer.
  int temp_size = (game->width * game->height + game->height);
  char *buffer = malloc( temp_size * sizeof(char) );
 
  // Read the entire game state.
  int totalRead = fread(buffer, 1, temp_size, fin );
  
  // Re-allocate new space for the board based on new sizes read.
  game->board = malloc(game->width * game->height *  sizeof(char));
  int bd_index = 0;
  for(int k = 0; k < temp_size; k++){
    if(buffer[k] == '\n'){
	// Do nothing. We skip these characters for easier math later
    } else {
	game->board[bd_index] = buffer[k];
	bd_index++;
    }
  }
  
  // Close the local file.
  fclose(fin);
  
  // Re-instate the previous player.
  game->currentTurn = prev_player;
  
  return *game;
}

int write_file(char ** gamestring, char * filename ){
  
  //Open a new file output
  FILE *fout;
  fout = fopen(filename, "w");

  //Check that the file was opened correctly
  if(fout == NULL){
    fprintf(stderr, "Error opening a new file named: %s\n", filename);
    return FAILURE;
  }

  // Print each part of 2D array to file. 
  for(int k = 0; k < 2; k++){
    fputs(*(gamestring+k), fout);
  }
  
  // Close file output
  fclose(fout);
  return SUCCESS;

}
