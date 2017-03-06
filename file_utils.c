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
  
  printf("The old size of the board is %lu\n", strlen(game->board));
  
  // Scan for the new dimensions
  fscanf(fin, "%d\n%d\n%d", &game->width, &game->height, &game->connectWin);
  printf("Changed the dimensions to %d %d\n", game->height, game->width);
  printf("Include one more sentence just in case%d\n", game->width*game->height);
  
  // Re-allocate new space for the board based on new sizes read
  int size = (game->width * game->height + game->height), position = 0;
  printf("The size gathered is %d\n", size);
  char * board = malloc( size * sizeof(char) );
  game->board = malloc((size - game->width) * sizeof(char));
  printf("The new size of the board is %lu\n", strlen(game->board));
  for(int k = 0; k < game->height; k++){
    fscanf(fin, "%s\n", board);
    // Copy the scanned portion to the game board
    for(int i = position; i < position + game->width; i++){
	if(board[i] == '\n'){
	printf("Found the next row at position %d\n", i);
	} else {
	  game->board[i] = board[i];
	}
	  
    }
    position += game->width + 1;
  }
  printf("The copied board is %s\n", board);
  printf("The size of the board is %lu\n", strlen(board));
  fclose(fin);
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
