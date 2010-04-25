// **********************************************************************
//                            OpenAlchemist
//                        ---------------------
//
//  File        : SkinMenuState.h
//  Description : 
//  Author      : Guillaume Delhumeau <guillaume.delhumeau@gmail.com>
//  License     : GNU General Public License 2 or higher
//
// **********************************************************************

#ifndef _SKINSMENU_STATE_H_
#define _SKINSMENU_STATE_H_

#include <ClanLib/display.h>

#include "MenuState.h"
#include "MenuState/TableChoicesItem.h"

class GameEngine;

/**
* SkinsMenu State
*/
class SkinsMenuState : public MenuState, ITableChoicesItemParent{

public:

	/** Constructor */
	SkinsMenuState();

	/** Destructor */
	~SkinsMenuState();
	
	virtual void init();

	virtual void term();

	virtual void load_gfx(CL_GraphicContext& gc, std::string skin);

	virtual void unload_gfx();

	virtual void action_performed(int selection, ActionType action_type);

	virtual void update_child();

	virtual void choice_selected(int choice);

private:

	/** Skin chooser item */
	TableChoicesItem _skin_chooser;

};

#endif