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
  printf("Entered loadgame\n");
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
  printf("The new gamewin condition is %d", game->connectWin);
  // Allocate space for a buffer.
  int temp_size = (game->width * game->height + game->height);
  printf("The temporary size is %d\n", temp_size);
  char *buffer = malloc( temp_size * sizeof(char) );
  printf("Allocated memory for the buffer!\n");
 
  // Read the entire game state.
  int totalRead = fread(buffer, 1, temp_size, fin );
  
  // Re-allocate new space for the board based on new sizes read.
  game->board = malloc(game->width * game->height *  sizeof(char));
  int bd_index = 0;
  for(int k = 0; k < temp_size; k++){
    if(buffer[k] == '\n'){
	printf("Found the next row at position %d\n", k);
    } else {
	game->board[bd_index] = buffer[k];
	printf("Copied over %c\n", game->board[bd_index]);
	bd_index++;
    }
  }
  printf("Game board now contains %s\n\n\n", game->board);
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

  
  for(int k = 0; k < 2; k++){
    printf("String being written is\n%s", *(gamestring+k));
    fputs(*(gamestring+k), fout);
  }

  printf("Successfully wrote to the file\n");
  // Close file output
  fclose(fout);
  return SUCCESS;

}
