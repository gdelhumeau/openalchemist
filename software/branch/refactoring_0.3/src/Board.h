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

/**
 * This class contains board game
 */
class Board{

  /**
   * Board game
   */
  Piece *board[NUMBER_OF_COLS][NUMBER_OF_LINES];

  /**
   * Old Board game (for undoing)
   */
  int undo_board[NUMBER_OF_COLS][NUMBER_OF_LINES];

  /**
   * List of pieces which are falling
   */
  std::vector<Piece*> falling_list;

  /**
   * List of pieces we have to destroy (only coords)
   */
  std::vector<Coords*> list_to_destroy;

  /**
   * List of pieces which are appearing
   */
  std::list<Piece*> appearing_list;

  /**
   * List of pieces we have to create (only coords)
   */
  std::list<Coords*> list_to_create;

  public:

  /**
   * Game Position
   */
  int game_top, game_left, zone_top;

  /**
   * Progression - number of unlocked pieces and visible pieces
   */
  int unlocked_pieces, visible_pieces;
  
  /**
   * Progression, but for undoing
   */
  int undo_unlocked_pieces, undo_visible_pieces;

  /**
   * Score
   */
  u_int score;

  /**
   * Bonus score
   */
  u_int bonus_score;

  /**
   * Old Bonus score
   */
  u_int undo_bonus_score;

  /**
   * Score in string format
   */
  std::string str_score;

  /**
   * Bonus score in string format
   */
  std::string str_bonus;

  /**
   * Hight score in string format
   */
  std::string str_hightscore;

  /**
   * Score coords
   */
  int score_left, score_right, score_top, bonus_left, bonus_right, bonus_top,
    hightscore_left, hightscore_right, hightscore_top;


  /** 
   * Constructor
   */
  Board();

  /**
   * Destructor
   */
  ~Board();

  /**
   * Clearing the board (delete all elements)
   */
  void clear();

  /**
   * Applying current to the board by giving sprites references
   */
  void apply_skin(CL_Sprite **pieces_normal, CL_Sprite** pieces_appearing, CL_Sprite** pieces_disappearing, CL_Sprite** pieces_mini);

  /**
   * Drawing the board
   */
  void draw();

  /**
   * Adding pieces to the game board - making them fall
   */
  void add_pieces(Piece* piece1, Piece* piece2);


  /**
   * Making pieces fall and create new ones
   * @return true if every pieces are corectly placed
   */
  bool fall_and_create();

  /**
   * Look if there is pieces to destroy
   * @return true if there is pieces to destroy
   */
  bool detect_pieces_to_destroy();

  /**
   * Destroying pieces
   * @return true if pieces are deleted
   */
  bool destroy();

  /**
   * Creating new pieces - sprites are needed for this operation
   */
  void create_new_pieces(CL_Sprite **pieces_normal, CL_Sprite **pieces_appearing, CL_Sprite **pieces_disappearing,
                         CL_Sprite **pieces_mini);

  /**
   * Detecting pieces which have to fall
   */
  void detect_pieces_to_fall();

  /**
   * Detecting if pieces are upside the limit, so if game is over
   */
  bool is_game_over();

  /**
   * Calculating score
   */
  void calc_score();

};

#endif
