// **********************************************************************
//                            OpenAlchemist
//                        ---------------------
//
//  File        : PauseMenuState.h
//  Description : 
//  Author      : Guillaume Delhumeau <guillaume.delhumeau@gmail.com>
//  License     : GNU General Public License 2 or higher
//
// **********************************************************************

#ifndef _PAUSEMENU_STATE_H_
#define _PAUSEMENU_STATE_H_

#include "MenuState.h"
#include "MenuState/BasicItem.h"
#include "../KeyboardKey.h"

/**
* PauseMenu State
*/
class PauseMenuState : public MenuState{

public:

	/** Constructor */
	PauseMenuState();

	/** Destructor */
	~PauseMenuState();

	virtual void init();

	virtual void deinit();

	virtual void load_gfx(CL_GraphicContext &gc, std::string skin);

	virtual void unload_gfx();

	virtual void action_performed(int selection, int action_type);

	virtual void update_child();	

private:

	/** Item to quit this menu */
	BasicItem _resume_item;

	/** Item to undo last move */
	BasicItem _undo_item;

	/** Item to restart a new game */
	BasicItem _retry_item;

	/** Item to open options menu */
	BasicItem _options_item;

	/** Item to give up current game */
	BasicItem _giveup_item;

	/** Item to quit the game */
	BasicItem _quit_item;

};

#endif
