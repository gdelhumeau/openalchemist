/********************************************************************
                          OpenAlchemist

  File : HumanPlayer.h
  Description : Implements Player Class
  License : GNU General Public License 2 or +
  Author : Guillaume Delhumeau <guillaume.delhumeau@gmail.com>


*********************************************************************/

#ifndef _HUMAN_PLAYER_H_
#define _HUMAN_PLAYER_H_

#include <ClanLib/display.h>

#include "Piece.h"
#include "Board.h"
#include "KeyboardKey.h"
#include "ProgressBar.h"
#include "Player.h"


/**
 * Implements the human player, keys events for going left, right & falling
 * and contains his board.
 */
class HumanPlayer : public Player{

  public:

  /**
   * Checking key events
   */
  void events();


};

#endif
