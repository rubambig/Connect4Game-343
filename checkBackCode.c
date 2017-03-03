int correct_row = -1, last_row = -5;
int previous_row, next_row, size = game->width * game->height;
char content = game->board[col];
if(content == 'X' || content == 'O'){
  printf("The colum is already full\n");
  return -3;
}
else {
  int temp = col + game->width; //The beginning element
  while( temp <= size){
    temp += game->width; // Keep adding until temps goes out of bounds
    if (temp > size){
      last_row = temp - game->width; // Capture correct temp
    }
    else if (temp == size){
      last_row = temp;
    }
  }

  // Search for the correct row  that hasn't been filled
  correct_row = last_row;
  while(game->board[last_row] != '-' ){
    last_row = last_row - game->width;
    if(game->board[last_row] == '-'){
      correct_row = last_row;
      break;
    }
  }

}

return correct_row;

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


/*// Loop to find out the index of the last non-null element in temp
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
}

printf("The built string is %s\n", diag_string_bottom );
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
