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

/*
int read_file( char * filename, GameState* game){

  
  // Allocate the memory space
  *buffer = malloc(size * sizeof(char));
  // Allocate the buffer for the second string
  //Open a new file input
  FILE *fin;
  fin = fopen(filename, "r");

  // Check that the file was opened correctly
  // Notify  the user that the file might not be in the
  // current directory
  if(fin == NULL){
    fprintf(stderr, "Error opening file named: %s\n", filename );
    exit(EXIT_FAILURE);
  }

  int totalRead = fread(*buffer, 1, size, fin );
  if (totalRead != size){
    fprintf(stderr, "Something went wrong with reading %s\n", filename );
  }
  printf("Read %d bytes of characters\n", totalRead);

  //Close the file
  // Return the number of bytes read
  fclose(fin);
  return totalRead;
}*/

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
    printf("String being read is\n %s", *(gamestring+k));
    fputs(*(gamestring+k), fout);
  }

  printf("Successfully wrote to the file\n");
  // Close file output
  fclose(fout);
  return SUCCESS;

}
