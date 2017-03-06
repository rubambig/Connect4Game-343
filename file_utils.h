/************************************************************
Provides the skeleton for the game loading and saving methods
@author Gloire Rubambiza
@version 02/17/2017
Code example and guidance provided by Prof. Ira Woodring
*************************************************************/
#include "connect_four.h"
#ifndef H_FILE_UTILS
#define H_FILE_UTILS


GameState loadgame(GameState* game, char * filename);
int write_file(char ** gamestring, char * filename);

#endif