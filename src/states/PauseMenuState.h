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

	PauseMenuState();

	~PauseMenuState();

	virtual void init();

	virtual void deinit();

	virtual void load_gfx(CL_GraphicContext &gc, std::string skin);

	virtual void unload_gfx();

	virtual void action_performed(int selection, int action_type);

	virtual void update_child();	

private:

	BasicItem _resume_item;
	BasicItem _undo_item;
	BasicItem _retry_item;
	BasicItem _options_item;
	BasicItem _giveup_item;
	BasicItem _quit_item;

};

#endif
