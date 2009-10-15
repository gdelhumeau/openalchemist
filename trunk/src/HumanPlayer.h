// **********************************************************************
//                            OpenAlchemist
//                        ---------------------
//
//  File        : HumanPlayer.h
//  Description : 
//  Author      : Guillaume Delhumeau <guillaume.delhumeau@gmail.com>
//  License     : GNU General Public License 2 or higher
//
// **********************************************************************

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
	void events(CL_InputContext & ic);

	virtual bool is_human(){ return true; }


};

#endif
