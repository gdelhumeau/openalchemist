/********************************************************************
                          OpenAlchemist

  File : HumanPlayer.cpp
  Description : Player implementation
  License : GNU General Public License 2 or +
  Author : Guillaume Delhumeau <guillaume.delhumeau@gmail.com>


*********************************************************************/

#include <math.h>

//#include <ClanLib/core.h>

#include "HumanPlayer.h"
#include "Piece.h"
#include "Preferences.h"
#include "CommonResources.h"
#include "misc.h"
#include "Board.h"
#include "GameEngine.h"

#define TO_RAD PI/180
#define PIECE_MOVING_SPEED 4


void HumanPlayer::events()
{
  // Getting resources
  static CommonResources *resources = common_resources_get_instance();

  if(GAME_MODE_PLAYING == game_mode)
  {
   switch(resources->CurrentKeyPressed)
   {
    // Change the order of the pieces 
    case KEY_CHANGE_ANGLE:
    {
      change_angle();
      resources->CurrentKeyPressed = 0;
      break;
    }

    // Look the key to know if we have to move the pieces to the left
    case KEY_LEFT:
    {
      move_left();
      resources->CurrentKeyPressed = 0;
      break;
    }

    // Look the key to know if we have to move the pieces to the right
    case KEY_RIGHT:
    {
      move_right();
      resources->CurrentKeyPressed = 0;
      break;
    }

    // It's time for the pieces to fall
    case KEY_FALL:
    {
      falling_requested = true; 
      resources->CurrentKeyPressed = 0;
      break;
    } 
    
    // Cheatting
    case KEY_CHEAT:
    {
      board.unlocked_pieces = NUMBER_OF_PIECES;
      board.visible_pieces = NUMBER_OF_PIECES;
      resources->CurrentKeyPressed = 0;
      break;
    }
   }
  }
  switch(resources->CurrentKeyPressed)
  { 
  // Undo the last move
  case KEY_UNDO:
  {
    undo();
    resources->CurrentKeyPressed = 0;
    break;
  }

  // Retry current game
  case KEY_RETRY:
  {
    resources -> engine -> set_state_quit_menu(QUITMENU_RETRY);
    resources->CurrentKeyPressed = 0;
    break;
  }
 }
}
