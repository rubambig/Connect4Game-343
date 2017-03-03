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
//#include "file_utils.h"
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
int colcheck, rowcheck, diagcheck, place_result;
while( strncmp(winner,"HW", 2) != 0 ){

  // Capture a column from the user
  currentPlayer = game.currentTurn;
  printf("\nPlace your next piece, player %d\n", currentPlayer);
  scanf("%d", &column);

  /*// Check that the user input is correct for the given board
  if( column > game.width || column < 0){
    while(column > game.width || column < 0) {
      scanf("%d", &column);
    }
  }*/
  while((place_result = placepiece(&game, column - 1 )) < 0){
    printf("Please enter a valid column, player %d\n", currentPlayer);
    scanf("%d", &column);
  }


  //Check the columns, rows, and diagonals;
  if(game.currentTurn == 1){
    colcheck = checkwincol(&game, p1Win, column - 1);
    printf("Winning string %s, current col status %d\n", p1Win, colcheck);
    rowcheck = checkwinrow(&game, p1Win, place_result);
    printf("Winning string %s, current row status %d\n", p1Win, rowcheck);
    diagcheck = checkwindiag(&game, p1Win, place_result);
    printf("Winning string %s, current diag status %d\n", p1Win, diagcheck);
  } else {
    colcheck = checkwincol(&game, p2Win, column);
    rowcheck = checkwinrow(&game, p2Win, place_result);
    diagcheck = checkwindiag(&game, p2Win, place_result);
  }

  if(diagcheck == MATCH || colcheck == MATCH || rowcheck == MATCH){
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
* @param game the game state
* @param col the column input from the user
* @param row the current row we are checking
**********************************************/
int findindex(GameState* game, int col, int row){
  if(row > game->height || row < 0)
    return -1;
  if(col >= game->width || col < 0 )
    return -1;

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
    if(index < 0){
      return -1;
    }
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
    if((current == 'X' || current == 'O') && i == 0)
      return -1;
  }
  int gameState = printboard(game);
  if (gameState < 0){
    printf("Something went awry when printing the board\n" );
  }
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
  printf("Returned string is %s\n", comparator );

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
* If the diagonal is found early, we return
* @param game the game state
* @param winstr the winning string
* @param col the index of a piece given by the user
*********************************************************/
int checkwindiag(GameState* game, char *winstr, int col_index){
  // Global variables to be reused by each loop
  int row = col_index / game->width, col = col_index % game->width;
  int winning = game->connectWin;
  int longest = 1;
  char my_char = game->board[col_index];

  // Strings to hold left and right diagonal checks
  // The most elements they can hold is limited by the number of rows
  char * left_diag = malloc(game->height * sizeof(char));
  char * right_diag = malloc(game->height * sizeof(char));
  int count_left = 0, count_right = 0;


  // Make copies of row and col to ensure each loop has a unique start
  int curr_index_bl, curr_index_br, curr_index_tl, curr_index_tr;
  int row_bl = row, row_br = row, row_tl = row, row_tr = row;
  int col_bl = col, col_br = col, col_tl = col, col_tr = col;

  // Finding a match from index to bottom left
  while ( row_bl > 0 && row_bl < game->height){
    row_bl ++;
    col_bl --;
    curr_index_bl= findindex(game, col_bl, row_bl);
    if(game->board[curr_index_bl] == my_char){
      right_diag[count_right++] = game->board[curr_index_bl];
      longest++;
      if(longest == winning){
        return MATCH;
      }

    } else {
      break;
    }
  }

  // Finding a match from index to top right
  longest = 1;
  while( row_tr >= 0 && row_tr < game->height){
    row_tr--;
    col_tr++;
    curr_index_tr = findindex(game, col_tr, row_tr);
    if(game->board[curr_index_tr] == my_char){
      right_diag[count_right++] = game->board[curr_index_tr];
      longest++;
      if(longest == winning){
        return MATCH;
      }

    } else {
      break;
    }
  }

  // Finding a match from index to bottom right
  longest = 1;
  while( row_br > 0 && row_br < game->height){
    row_br++;
    col_br++;
    curr_index_br = findindex(game, col_br, row_br);
    if(game->board[curr_index_br] == my_char){
      left_diag[count_left++] = game->board[curr_index_br];
      longest++;
      if(longest == winning){
        return MATCH;
      }

    } else {
      break;
    }
  }

  // Finding a match from index to top left
  longest = 1;
  printf("Checking top left\n");
  while( row_tl >= 0 && row_tl < game->height){
    row_tl--;
    col_tl--;
    curr_index_tl = findindex(game, col_tl, row_tl);
    if(game->board[curr_index_tl] == my_char){
      left_diag[count_left++] = game->board[curr_index_tl];
      longest++;
      printf("Longest so far is %d\n", longest );
      if(longest == winning){
        return MATCH;
      }

    } else {
      break;
    }
  }

  // Compare that none of the aggregate strings contain the winning string
  char *match_left = strstr(right_diag, winstr);
  char *match_right = strstr(left_diag, winstr);
  if( match_right != NULL || match_left != NULL){
    free(left_diag);
    free(right_diag);
    return MATCH;
  } else {
    free(right_diag);
    free(left_diag);
    return NOMATCH;
  }

  return NOMATCH;

}

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
/*void savegame(GameState* game, char *filename ){

  // Open the file.
  FILE *out;
  out = open(filename, "w");

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
* @param game the game state
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
