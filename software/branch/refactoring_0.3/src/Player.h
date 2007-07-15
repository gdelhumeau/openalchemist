/********************************************************************
                          OpenAlchemist

  File : Player.h
  Description : 
  License : GNU General Public License 2 or +
  Author : Guillaume Delhumeau <guillaume.delhumeau@gmail.com>


*********************************************************************/

#ifndef _PLAYER_H_
#define _PLAYER_H_

#include <ClanLib/display.h>

#include "Piece.h"
#include "Board.h"
#include "KeyboardKey.h"

class Player{

  float x;
  float angle;
  
  int target_x;
  int target_angle;

  int position;
  int old_position;
  int position_bis;
  int old_position_bis;
  bool placed;
  
  Piece* next_piece1;
  Piece* next_piece2;

  int next_left;
  int next_top;

  Piece* current_piece1;
  Piece* current_piece2;

  int game_top, game_left, zone_top;
  int current_pieces_r;

  /** Sprites */
  CL_Sprite *pieces_normal[NUMBER_OF_PIECES];
  CL_Sprite *pieces_appearing[NUMBER_OF_PIECES];
  CL_Sprite *pieces_disappearing[NUMBER_OF_PIECES];
  CL_Sprite *pieces_mini[NUMBER_OF_PIECES];

  Board board;

  KeyboardKey *key_change_angle;
  KeyboardKey *key_left;
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
