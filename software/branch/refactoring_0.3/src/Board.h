/********************************************************************
                          OpenAlchemist

  File : Board.h
  Description : 
  License : GNU General Public License 2 or +
  Author : Guillaume Delhumeau <guillaume.delhumeau@gmail.com>


*********************************************************************/

#ifndef _BOARD_H_
#define _BOARD_H_

#include "Piece.h"

#define NUMBER_OF_PIECES 12
#define NUMBER_OF_COLS 6
#define NUMBER_OF_LINES 9

class Board{

  Piece *board[NUMBER_OF_COLS][NUMBER_OF_LINES];

  public:
  /** Constructor */
  Board();

  void apply_skin(CL_Sprite **pieces_normal, CL_Sprite** pieces_appearing, CL_Sprite** pieces_disappearing, CL_Sprite** pieces_mini);

  void draw();

};

#endif
