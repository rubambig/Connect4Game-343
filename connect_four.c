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

#define MATCH 0
#define NOMATCH -1

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
int currentPlayer, column, size = game.width * game.height;
int colcheck, rowcheck, diagcheck;
while( strncmp(winner,"HW", 2) != 0 ){

  // Capture a column from the user
  currentPlayer = game.currentTurn;
  printf("\nPlace your next piece, player %d\n", currentPlayer);
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
    rowcheck = checkwinrow(&game, p1Win, place_result);
  } else {
    colcheck = checkwincol(&game, p2Win, column);
    rowcheck = checkwinrow(&game, p2Win, place_result);
  }

  if(colcheck == MATCH || rowcheck == MATCH){
    printf("Player %d has won!\n", game.currentTurn);

    // Ask if the user would like a new game
    int newgame;
    printf("Would you like to keep playing? y/n\n");
    scanf("%d", &newgame);

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
  int current_index;
  for( int i = game->height; i >=0; --i){
    int index = findindex(game, col, i );
    char current = game->board[index];
    if( current == '-' && game->currentTurn == 1 ){
      game->board[index] = 'X';
      current_index = index;
      break;
    }
    if(current == '-' && game->currentTurn == 2 ){
      game->board[index] = 'O';
      current_index = index;
      break;
    }
  }
  int gameState = printboard(game);
  if (gameState < 0){
    printf("Something went awry when printing the board\n" );
    return NOMATCH;
  }
  printf("Returned index is %d\n", current_index );
  return current_index;
}

/*****************************************************
* Checks for win conditions on the board columns.
* Got idea on using substrings in C from stackoverflow
* @param game the game state
* @param winstr the winning string
* @param col a colum number given by the user
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
    return MATCH; // The devil has been found
  } else {
    free(comparator);
    return NOMATCH; // Not now devil, try your luck next time
  }
}

/********************************************************
* Checks for win conditions on the diagonals of the board
* Builds both tr-to-bl and tl-to-br diagonals
* @param game the game state
* @param winstr the winning string
* @param col a colum number given by the user
*********************************************************/
/*int checkwindiag(GameState* game, char *winstr, int col){

  // Building a diagonal string from top right to bottom left
  char *diag_string_bottom;
  char temp[10000];
  //int start_pos, next_pos, prev = col - game->width -1;
  int start_here = col - game->width - 1;
  while(start_here >= 0){
    start_here -= game->width - 1;
  }
  int count = 0;
  while(start_here <= (game->width * game ->height)){
    temp[count++] = game->board[start_here];
  }


  // Loop to find out the index of the last non-null element in temp
  // use that index to malloc diag_string_bottom
  // copy temp to diag_string_bottom
  //diag_string_bottom = malloc( strlen(temp))
  //for(int x)
  // Find the index of the starting position of the diagonal
  while( game->board[prev] == '_' || game->board[prev] == 'X' || game->board[prev] == 'O' ){
    printf("In while statement %c\n", game->board[prev]);
    prev -= game->width - 1;
    printf("Previous is %d\n", prev);
    if (!(game->board[prev] == '_' && game->board[prev] == 'X' && game->board[prev] == 'O')){
      start_pos = prev + game->width + 1;
      printf("Start pos %d\n", start_pos);
      break;
    }
  }
  printf("Start position is %d\n", start_pos );
  // Start building string from the beginning of the diagonal
  next_pos = start_pos;
  char *temp = malloc(game->width * sizeof(char));
  while(game->board[next_pos] == '_' || game->board[next_pos] == 'X' || game->board[next_pos] == 'O' ){
    // Might not need this size = strlen(temp);

    // Check that we ran out of bounds
    char tempchar = game->board[next_pos];
    printf("Temp char is %c", tempchar);
    if( !(tempchar == '_' && tempchar == 'X' && tempchar == 'O')){
      diag_string_bottom = malloc(strlen(temp) * sizeof(char));
      strcpy(diag_string_bottom, temp);
      break;
    } else {
      temp[strlen(temp)] = tempchar;
      next_pos += game->width + 1;
    }
  }*/

  /*printf("The built string is %s\n", diag_string_bottom );
  printf("The winning string is %s\n", winstr);

  // Compare the two strings
  char *match = strstr(diag_string_bottom, winstr);

  if( match != NULL){
    free(diag_string_bottom);
    free(match);
    return MATCH;
  } else {
    free(diag_string_bottom);
    free(match);
    return NOMATCH;
  }*/

  // Attempt to build a diagonal string from top left to bottom right

//}

/********************************************************
* Checks for win conditions on the rows of the board
* Uses the offset of the col to build the row
* @param game the game state
* @param winstr the winning string
* @param col a colum number given by the user
*********************************************************/
int checkwinrow(GameState* game, char *winstr, int col){

  // Find the start of the current row
  //int next_row_start = col + (col % game->width) + 1;
  //printf("Next row starts at: %d\n", next_row_start);
  //int row_start = next_row_start - game->width;
  int row_start = col - (col % game->width);
  printf("This row starts at: %d\n", row_start);

  // Allocate space for the comparator string
  char *comparator = malloc ( game->width * sizeof(char));
  comparator[0] = game->board[row_start];
  int count = 1;
  row_start++;
  while( (row_start % game->width) != 0){
    comparator[count] = game->board[row_start];
    row_start++;
    count++;
  }

  printf("The built string is %s\n", comparator);
  printf("The winning string is %s\n", winstr);

  // Compare the two strings
  char *match = strstr(comparator, winstr);

  if( match != NULL){
    free(comparator);
    return MATCH;
  } else {
    free(comparator);
    return NOMATCH;
  }
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
