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
#include "connect_four.h"


int main(int argc, char** argv){

// Parse the command line arguments
struct arguments* gameArgs = setup(argc, argv);

// Build the winning strings
char *p1Win = malloc( gameArgs->connectWin * sizeof(char));
for(int x = 0; x < gameArgs->connectWin; x++){
  p1Win[x] = 'X';
}

char *p2Win = malloc( gameArgs->connectWin * sizeof(char));
for(int o = 0; o < gameArgs->connectWin; o++){
  p2Win[o] = 'O';
}

GameState game; // The representation of the game state
char * winner = "NW";

// Check that the players do not want to load a previous game
if (gameArgs->load != NULL){
  //logic for loading game from a file
}
else if(gameArgs->width != gameArgs->square){
  createboard(gameArgs, &game);
}
else{
  createboard(gameArgs, &game);
}
// Keep playing until we find a winner
int currentPlayer, column;
int colcheck, rowcheck, diagcheck;
while( strncmp(winner,"HW", 2) != 0 ){

  // Capture a column from the user
  currentPlayer = game.currentTurn;
  printf("Place your next piece, player %d\n", currentPlayer);
  scanf("%d", &column);

  // Check that the user input is correct for the given board
  if( column > game.width || column < 0){
    while(column > game.width || column < 0) {
      printf("Please enter a valid column!\n");
      scanf("%d", &column);
    }
  }
  int place_result = placepiece(&game, column );
  if(place_result < 0){
    printf("Please choose another column\n");
  }

  //Check the columns, rows, and diagonals;
  if(game.currentTurn == 1){
    colcheck = checkwincol(&game, p1Win, column);
  } else {
    colcheck = checkwincol(&game, p2Win, column);
  }

  if(colcheck > 1){
    printf("Player %d has won!\n", game.currentTurn);

    // Ask if the user would like a new game
    printf("Would you like to keep playing? y/n \n");
    char newgame;
    scanf("%c", &newgame);

    if(newgame == 'y'){
      printf("Starting a new game\n");
    } else {
      exit(0);
    }
  }
  else{
   // Switch turns between players and keep playing
    if(game.currentTurn == 1){
      game.currentTurn = 2;
    }
    else{
      game.currentTurn = 1;
    }
  }

}

return 0;
}

/************************************************************
 * Instantiates the board for user view based on command-line
 * arguments passed by the user. The game state represents
 * the view as a string to the user.
 * @param args the arguments passed by the user
 * @param game the game state
 ***********************************************************/
int createboard(struct arguments* args, GameState* game){

  // Check that the user input is correct for the game
  if (args->height < 3 || args->width < 3){
    fprintf(stderr, "Passed arguments width[%d] and height[%d], both have to be at least 3",
            args->width, args->height);
            return -1;
  } else {
    int i, k;
    game->width = args->width;
    game->height = args->height;
    game->connectWin = args->connectWin;
    game->currentTurn = 1;

    // Instantiate the board
    int size = game->width * game->height;
    game->board = (char *)malloc( size * sizeof(char));

    for(i = 0; i < size; i++){
        game->board[i] = '-';
    }

    int gameState = printboard(game);
    if(gameState < 0){
      printf("Something went wrong with printing the initial board!\n");
    }
  }

  return 0;
}

/*********************************************
* Finds the appropriate row to place a piece in.
* Check if the row has not been filled yet.
**********************************************/
int findindex(GameState* game, int col, int row){
  return (row * game->width) + col;
}

/*******************************************************
* Places a new piece on the board based on the column
* chosen by the user. Pieces are placed on top of
* each other if the column already has some pieces in it
* @param game the game state
*******************************************************/
int placepiece(GameState* game, int col){

  for( int i = game->height; i >=0; --i){
    int index = findindex(game, col, i );
    char current = game->board[index];
    if( current == '-' && game->currentTurn == 1 ){
      game->board[index] = 'X';
      break;
    }
    if(current == '-' && game->currentTurn == 2 ){
      game->board[index] = 'O';
      break;
    }
  }
  int gameState = printboard(game);
  if (gameState < 0){
    printf("Something went awry when printing the board\n" );
    return -1;
  }
  return 0;
}


/*****************************************************
* Checks for win conditions on the board.
* Got idea on using substrings in C from stackoverflow
* Check for wins in colums
@param game the game state
******************************************************/
int checkwincol(GameState* game, char *winstr, int col){

  // Find how far the column is from the total width
  int offset = col % game->width;
  char *comparator = malloc(game->height * sizeof(char));

  for( int c = 0; c < game->height; c++){
    comparator[c] = game->board[offset]; //Start at the top of the column
    offset += game->width;
  }
  char *match = strstr(comparator, winstr);

  if( match != NULL){
    free(comparator);
    return 666; // The devil has been found
  } else {
    free(comparator);
    return -666; // Not now devil, try your luck next time
  }
}

/*******************************************************
* Checks for win conditions on the diagonals of the game
********************************************************/
int checkwindiag(GameState* game, char *winstr, int col){
  
}

/****************************************************
* Save the game state based on its current state.
* The user passes a -s flag and a file name
* Call the file_utils written prior to do the saving
* @param game the game state
****************************************************/
/*void savegame(struct GameState* game){

}*/

/*****************************************************
* Load a game from a previous game state
* The user passes a -l flag and a file name
* Call the file_utils written prior to load the struct
* @param filename the file specified by the user
******************************************************/
/*char** loadgame(char * filename){

}*/

/*************************************************
* Prints the current state of the game to the user
**************************************************/
int printboard(GameState* game){

  int k, size = game->width * game->height;
  // Print the current state of the game to the user
  char *str = malloc( size+1 * sizeof(char));
  strcpy(str, game->board);
  strncat(str, "\0", 1); //Append the EOF character at the end
  for(int k = 0; k < size; k++){
    if(k > 0 && k % game->width == 0){ // Separate the rows of the board
      printf("\n");
    }
      printf("%c", str[k]);

  }

  //Clear the screen
  printf("\n\n\n");
  return 0;
}
