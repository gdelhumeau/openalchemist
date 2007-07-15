#include "Board.h"

Board::Board()
{
    
  /* Initializing all to NULL */
  for(int i = 0; i < NUMBER_OF_COLS; ++i)
    for(int j = 0; j < NUMBER_OF_LINES; ++j)
      board[i][j] = NULL;

}

void Board::apply_skin(CL_Sprite** pieces_normal, CL_Sprite** pieces_appearing, CL_Sprite** pieces_disappearing, CL_Sprite** pieces_mini)
{
  for(int i = 0; i < NUMBER_OF_COLS; ++i)
    for(int j = 0; j < NUMBER_OF_LINES; ++j)
    {
      if(board[i][j])
      {
        int value = board[i][j] -> get_piece_number();
        board[i][j] -> set_sprites(pieces_normal[value], pieces_appearing[value],
                             pieces_disappearing[value], pieces_mini[value]);
      }
    }
}


void Board::draw()
{
  for(int i = 0; i < NUMBER_OF_COLS; ++i)
    for(int j = 0; j < NUMBER_OF_LINES; ++j)
    {
      if(board[i][j])
      {
        board[i][j] -> draw(); 
      }
    }
}
