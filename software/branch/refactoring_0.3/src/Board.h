/********************************************************************
                          OpenAlchemist

  File : Board.h
  Description : 
  License : GNU General Public License 2 or +
  Author : Guillaume Delhumeau <guillaume.delhumeau@gmail.com>


*********************************************************************/

#ifndef _BOARD_H_
#define _BOARD_H_

#include <vector>
#include <list>

#include "Piece.h"
#include "Coords.h"

#define NUMBER_OF_PIECES 12
#define NUMBER_OF_COLS 6
#define NUMBER_OF_LINES 9


class Board{

  Piece *board[NUMBER_OF_COLS][NUMBER_OF_LINES];

  std::vector<Piece*> falling_list;
  std::vector<Coords*> list_to_destroy;
  std::list<Piece*> appearing_list;
  std::list<Coords*> list_to_create;

  public:

  /**
   * Game Position
   */
  int game_top, game_left, zone_top;

  int unlocked_pieces;
  int visible_pieces;


  /** Constructor */
  Board();

  void apply_skin(CL_Sprite **pieces_normal, CL_Sprite** pieces_appearing, CL_Sprite** pieces_disappearing, CL_Sprite** pieces_mini);

  void draw();

  void add_pieces(Piece* piece1, Piece* piece2);


  /**
   * @return true if every pieces are corectly placed
   */
  bool fall_and_create();

  /**
   * @return true if there is pieces to destroy
   */
  bool detect_pieces_to_destroy();

  bool destroy();

  void create_new_pieces(CL_Sprite **pieces_normal, CL_Sprite **pieces_appearing, CL_Sprite **pieces_disappearing,
                         CL_Sprite **pieces_mini);

  void detect_pieces_to_fall();

};

#endif
