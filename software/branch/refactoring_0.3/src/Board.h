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
  Board()
    {
    
      /* Initializing all to NULL */
      for(int i = 0; i < NUMBER_OF_COLS; ++i)
        for(int j = 0; j < NUMBER_OF_LINES; ++j)
          board[i][j] = NULL;

    }

};

#endif
