/********************************************************************
                          OpenAlchemist

  File : DemoPlayer.cpp
  Description : Player implementation
  License : GNU General Public License 2 or +
  Author : Guillaume Delhumeau <guillaume.delhumeau@gmail.com>


*********************************************************************/

#include <math.h>

#include <ClanLib/core.h>

#include "DemoPlayer.h"
#include "Piece.h"
#include "Preferences.h"
#include "CommonResources.h"
#include "misc.h"
#include "Board.h"
#include "GameEngine.h"


void DemoPlayer::events()
{
  // Getting resources
  static CommonResources *resources = common_resources_get_instance();

  if(GAME_MODE_PLAYING == game_mode)
  {
    // Change the order of the pieces 
    if(key_change_angle->get())
    {
      change_angle();
    }

    // Look the key to know if we have to move the pieces to the left
    if(key_left->get())
    {
      move_left();
    }

    // Look the key to know if we have to move the pieces to the right
    if(key_right->get())
    {
      move_right();
    }

    // It's time for the pieces to fall
    if(key_falling -> get())
    {
      falling_requested = true; 
    } 
    
    // Cheatting
    if(CL_Keyboard::get_keycode(CL_KEY_A) && CL_Keyboard::get_keycode(CL_KEY_L))
    {
      board.unlocked_pieces = NUMBER_OF_PIECES;
      board.visible_pieces = NUMBER_OF_PIECES;
    }
  }

  // Undo the last move
  if(resources->key.undo -> get())
  {
    undo();
  }

  // Retry current game
  if(resources -> key.retry -> get())
  {
    new_game();
  }

}

void DemoPlayer::new_game()
{
  // Getting resources
  CommonResources *resources = common_resources_get_instance();

  // Creating new pieces for playable pieces and next pieces
  current_piece1 = new Piece(2);
  current_piece2 = new Piece(1);
  next_piece1 = new Piece(2);
  next_piece2 = new Piece(2);

  // Setting playable pieces position
  angle = 0.0;
  target_angle = 0;
  position = 2;
  position_bis = 1;
  placed = true;
  undo_possible = false;
  next_next_piece1 = 0;
  next_next_piece2 = 0;
  x = position * resources->pieces_width + (position_bis )*resources->pieces_width/2;
  next_piece1 -> set_position(next_left, next_top);
  next_piece2 -> set_position(next_left+((resources->pieces_width)/2),next_top);

  falling_requested = false;
  game_mode = GAME_MODE_PLAYING;

  board.clear();
  board.unlocked_pieces = 3;
  board.visible_pieces  = 3;
  board.score = 0;
  board.bonus_score = 0;
  board.calc_score();
  
  // Applying skin
  int value;
  value = next_piece1 -> get_piece_number();
  
  next_piece1 -> set_sprites(pieces_normal[value], pieces_appearing[value],
                             pieces_disappearing[value], pieces_mini[value]);
  
  value = next_piece2 -> get_piece_number();
  next_piece2 -> set_sprites(pieces_normal[value], pieces_appearing[value],
                             pieces_disappearing[value], pieces_mini[value]);
  
  value = current_piece1 ->  get_piece_number();
  current_piece1 -> set_sprites(pieces_normal[value], pieces_appearing[value],
                                pieces_disappearing[value], pieces_mini[value]);
  
  value = current_piece2 ->  get_piece_number();
  current_piece2 -> set_sprites(pieces_normal[value], pieces_appearing[value],
                                pieces_disappearing[value], pieces_mini[value]);

}
