/********************************************************************
                          OpenAlchemist

  File : DemoPlayer.cpp
  Description : Player implementation
  License : GNU General Public License 2 or +
  Author : Guillaume Delhumeau <guillaume.delhumeau@gmail.com>


*********************************************************************/

#include "memory.h"
#include <math.h>

#include <ClanLib/core.h>

#include "DemoPlayer.h"
#include "Piece.h"
#include "Preferences.h"
#include "CommonResources.h"
#include "misc.h"
#include "Board.h"
#include "GameEngine.h"


void DemoPlayer::events(CL_DisplayWindow & window)
{
 

}

void DemoPlayer::new_game()
{
	term_game();
		
  // Getting resources
  CommonResources *resources = common_resources_get_instance();

  // Creating new pieces for playable pieces and next pieces
  _p_current_piece1 = my_new Piece(2);
  _p_current_piece2 = my_new Piece(1);
  _p_next_piece1 = my_new Piece(2);
  _p_next_piece2 = my_new Piece(2);

  // Setting playable pieces position
  _angle = 0.0;
  _aimed_angle = 0;
  _position = 2;
  _position_bis = 1;
  _is_placed = true;
  _undo_possible = false;
  _next_next_piece1 = 0;
  _next_next_piece2 = 0;
  _x = _position * resources->pieces_width + (_position_bis )*resources->pieces_width/2;
  _p_next_piece1 -> set_position(_next_left, _next_top);
  _p_next_piece2 -> set_position(_next_left+((resources->pieces_width)/2),_next_top);

  _is_falling_requested = false;
  _game_mode = GAME_MODE_PLAYING;

  _board.clear();
  _board.unlocked_pieces = 3;
  _board.visible_pieces  = 3;
  _board.score = 0;
  _board.bonus_score = 0;
  _board.calc_score();
  
  // Applying skin
  int value;
  value = _p_next_piece1 -> get_piece_number();
  
  _p_next_piece1 -> set_sprites(&_p_pieces_normal[value], &_p_pieces_appearing[value],
                             &_p_pieces_disappearing[value], &_p_pieces_mini[value]);
  
  value = _p_next_piece2 -> get_piece_number();
  _p_next_piece2 -> set_sprites(&_p_pieces_normal[value], &_p_pieces_appearing[value],
                             &_p_pieces_disappearing[value], &_p_pieces_mini[value]);
  
  value = _p_current_piece1 ->  get_piece_number();
  _p_current_piece1 -> set_sprites(&_p_pieces_normal[value], &_p_pieces_appearing[value],
                                &_p_pieces_disappearing[value], &_p_pieces_mini[value]);
  
  value = _p_current_piece2 ->  get_piece_number();
  _p_current_piece2 -> set_sprites(&_p_pieces_normal[value], &_p_pieces_appearing[value],
                                &_p_pieces_disappearing[value], &_p_pieces_mini[value]);

}

