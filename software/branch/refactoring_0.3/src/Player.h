/********************************************************************
                          OpenAlchemist

  File : Player.h
  Description : Implements Player Class
  License : GNU General Public License 2 or +
  Author : Guillaume Delhumeau <guillaume.delhumeau@gmail.com>


*********************************************************************/

#ifndef _PLAYER_H_
#define _PLAYER_H_

#include <ClanLib/display.h>

#include "Piece.h"
#include "Board.h"
#include "KeyboardKey.h"

/**
 * Implements the player, keys events for going left, right & falling
 * and contains his board.
 */
class Player{

  /**
   * X Position
   */
  float x;

  /**
   * Angle
   */
  float angle;
  

  /**
   * Angle required (for changing)
   */
  int target_angle;

  /**
   * Current position (in cols)
   */
  int position;

  /**
   * Old position (to undo - in cols)
   */
  int old_position;

  /**
   * 1 if angle = 90 or 180
   */
  int position_bis;

  /**
   * Old position bis to undo
   */
  int old_position_bis;

  /**
   * To know if pieces are moving too the left or to the right or not
   */
  bool placed;
  
  /**
   * One of the next piece (displaying in top)
   */
  Piece* next_piece1;

  /**
   * One of the next piece (displaying in top)
   */
  Piece* next_piece2;

  /**
   * X Position for next items
   */
  int next_left;

  /**
   * Y Position for next items
   */
  int next_top;

  /**
   * One of the current pieces
   */
  Piece* current_piece1;

  /**
   * One of the current pieces
   */
  Piece* current_piece2;

  /**
   * Game Position
   */
  int game_top, game_left, zone_top;

  /**
   * Rayon of circle which contains playable pieces
   */
  int current_pieces_r;

  /** 
   * Contains the normal pieces sprites
   */
  CL_Sprite *pieces_normal[NUMBER_OF_PIECES];

  /**
   * Contains the appearing pieces sprites
   */
  CL_Sprite *pieces_appearing[NUMBER_OF_PIECES];

  /**
   * Contains the disappearing pieces sprites
   */
  CL_Sprite *pieces_disappearing[NUMBER_OF_PIECES];

  /**
   * Contains the mini pieces sprites
   */
  CL_Sprite *pieces_mini[NUMBER_OF_PIECES];

  /**
   * Board game
   */
  Board board;

  /**
   * Key for playing
   */
  KeyboardKey *key_change_angle;

  /**
   * Key for playing
   */
  KeyboardKey *key_left;

  /**
   * Key for playing
   */
  KeyboardKey *key_right;
  
  public:
  Player();
  ~Player();

  void load_gfx(std::string skin);
  void unload_gfx();

  void events();
  void change_angle();
  void move_left();
  void move_right();

  void new_game();
  void draw();
  void update();

};

#endif
