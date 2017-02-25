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
