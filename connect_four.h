#include "handle_arguments.h"
/*********************************************************
Provides the skeleton for the game methods
@author Gloire Rubambiza
@version 02/17/2017
Code example and guidance provided by Prof. Ira Woodring
*********************************************************/

/******************************************
* Defines the struct type of the game state
*******************************************/
typedef struct ConnectGames {
  int width;
  int height;
  int connectWin;
  int currentTurn;
  char * board;
} GameState;

/*************************************
* Recreates the same game for the user
**************************************/
GameState newgame(GameState* game);
/*************************************
 * Instantiates the board for user view
 **************************************/
int createboard(struct arguments* arg, GameState* game);

/*********************************************
* Finds the appropriate row to place a piece in.
***********************************************/
int findindex(GameState* game, int col, int row);

/********************************
* Places a new piece on the board
**********************************/
int placepiece(GameState* game, int col);

/**************************************
* Prints the current state of the game.
***************************************/
int printboard(GameState* game);

/*****************************************************
* Checks for win conditions on the columns of the game
******************************************************/
int checkwincol(GameState* game, char *winstr, int col);

/*******************************************************
* Checks for win conditions on the diagonals of the game
********************************************************/
int checkwindiag(GameState* game, char *winstr, int col);

/*********************************************************
* Checks for win conditions in the row of the given column
**********************************************************/
int checkwinrow(GameState* game, char *winstr, int col);

/***********************************************
* Build a string to be saved as the game state
************************************************/
char ** buildstring(GameState* game);

/***************************************
* Load a game from a previous game state
****************************************/
//int loadgame(GameState* game, char * filename);
