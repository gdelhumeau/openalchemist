// **********************************************************************
//                            OpenAlchemist
//                        ---------------------
//
//  File        : OptionsMenuState.h
//  Description : 
//  Author      : Guillaume Delhumeau <guillaume.delhumeau@gmail.com>
//  License     : GNU General Public License 2 or higher
//
// **********************************************************************

#ifndef _OPTIONSMENU_STATE_H_
#define _OPTIONSMENU_STATE_H_

#include <ClanLib/display.h>

#include "MenuState.h"
#include "MenuState/BasicItem.h"
#include "MenuState/MultipleChoicesItem.h"

class GameEngine;

/**
* OptionsMenu State
*/
class OptionsMenuState : public MenuState
{

public:

	/** Constructor */
	OptionsMenuState();

	/** Destructor */
	~OptionsMenuState();

	virtual void init();

	virtual void term();

	virtual void load_gfx(CL_GraphicContext &gc, std::string skin);

	virtual void unload_gfx();
	
	virtual void action_performed(int selection, ActionType action_type);

	virtual void update_child();
	
	/** Toggle screen */
	void toggle_screen();

private:

	/** Item to choice render engine */
	MultipleChoicesItem _render_item;

	/** Item to switch from fullscreen to window */
	MultipleChoicesItem _fullscreen_item;

	/** Item to set max framerate */
	MultipleChoicesItem _framerate_item;

	/** Item to set sound level */
	MultipleChoicesItem _sound_level_item;

	/** Item to set music level */
	MultipleChoicesItem _music_level_item;

	/** Item to quit the menu */
	BasicItem _quit_item;

};

#endif
