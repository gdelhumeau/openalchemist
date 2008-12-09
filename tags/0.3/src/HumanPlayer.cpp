/********************************************************************
                          OpenAlchemist

  File : HumanPlayer.cpp
  Description : Player implementation
  License : GNU General Public License 2 or +
  Author : Guillaume Delhumeau <guillaume.delhumeau@gmail.com>


*********************************************************************/

#include <math.h>

#include <ClanLib/core.h>

#include "HumanPlayer.h"
#include "Piece.h"
#include "Preferences.h"
#include "CommonResources.h"
#include "misc.h"
#include "Board.h"
#include "GameEngine.h"

#define TO_RAD PI/180
#define PIECE_MOVING_SPEED 0.25


void HumanPlayer::events()
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
    resources -> engine -> set_state_quit_menu(QUITMENU_RETRY);
  }

}
