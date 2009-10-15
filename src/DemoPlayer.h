// **********************************************************************
//                            OpenAlchemist
//                        ---------------------
//
//  File        : DemoPlayer.h
//  Description : 
//  Author      : Guillaume Delhumeau <guillaume.delhumeau@gmail.com>
//  License     : GNU General Public License 2 or higher
//
// **********************************************************************

#ifndef _DEMO_PLAYER_H_
#define _DEMO_PLAYER_H_

#include <ClanLib/display.h>

#include "Piece.h"
#include "Board.h"
#include "KeyboardKey.h"
#include "ProgressBar.h"
#include "Player.h"

/**
* Implements the demo player, keys events for going left, right & falling
* and contains his board.
*/
class DemoPlayer : public Player{

public:

	/**
	* Checking key events
	*/
	void events(CL_DisplayWindow & window);

	/**
	* Make a my_new game
	*/
	void new_game();

	virtual bool is_human(){ return false; }


};

#endif
