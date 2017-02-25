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

/***************************************
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

/***************************************
* Checks for win conditions on the board
****************************************/
//int checkwin(struct GameState* game);

/***********************************************
* Save the game state based on its current state
************************************************/
//void savegame(struct GameState* game);

/***************************************
* Load a game from a previous game state
****************************************/
//char** loadgame(char * filename);*/
