// **********************************************************************
//                            OpenAlchemist
//                        ---------------------
//
//  File        : HumanPlayer.cpp
//  Description : 
//  Author      : Guillaume Delhumeau <guillaume.delhumeau@gmail.com>
//  License     : GNU General Public License 2 or higher
//
// **********************************************************************

#include <math.h>
#include <ClanLib/core.h>

#include "memory.h"
#include "HumanPlayer.h"
#include "Piece.h"
#include "Preferences.h"
#include "CommonResources.h"
#include "misc.h"
#include "Board.h"
#include "GameEngine.h"
#include "AudioManager.h"

/************************************************************************/
/* Constants                                                            */
/************************************************************************/
static const float PI     = 3.1415926535897932384f;
static const float TO_RAD = PI / 180;
static const float PIECE_MOVING_SPEED = 0.25;

/************************************************************************/
/* Events                                                               */
/************************************************************************/
void HumanPlayer::events(CL_InputContext& ic)
{
	// Getting resources
	static CommonResources* p_resources = common_resources_get_instance();

	if(GAME_MODE_PLAYING == _game_mode)
	{
		// Change the order of the pieces 
		if(_key_change_angle.get(ic))
		{
			change_angle();
			g_audio_manager.play_sound(SOUND_MOVE);
		}

		// Look the key to know if we have to move the pieces to the left
		if(_key_left.get(ic))
		{
			move_left();
			g_audio_manager.play_sound(SOUND_MOVE);
		}

		// Look the key to know if we have to move the pieces to the right
		if(_key_right.get(ic))
		{
			move_right();
			g_audio_manager.play_sound(SOUND_MOVE);
		}

		// It's time for the pieces to fall
		if(_key_falling.get(ic))
		{
			_is_falling_requested = true; 
		} 

		// Cheatting
		CL_InputDevice& keyboard = ic.get_keyboard();
		if(keyboard.get_keycode(CL_KEY_A) && keyboard.get_keycode(CL_KEY_L))
		{
			_board.unlocked_pieces = NUMBER_OF_PIECES;
			_board.visible_pieces = NUMBER_OF_PIECES;
		}
	}

	// Undo the last move
	if(p_resources->key.undo.get(ic))
	{
		undo();
	}

	// Retry current game
	if(p_resources -> key.retry.get(ic))
	{
		p_resources -> p_engine -> set_state_quit_menu(QUITMENU_RETRY);
	}

}
