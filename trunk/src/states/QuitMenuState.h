// **********************************************************************
//                            OpenAlchemist
//                        ---------------------
//
//  File        : QuitMenuState.h
//  Description : 
//  Author      : Guillaume Delhumeau <guillaume.delhumeau@gmail.com>
//  License     : GNU General Public License 2 or higher
//
// **********************************************************************

#ifndef _QUITMENU_STATE_H_
#define _QUITMENU_STATE_H_

#include <ClanLib/display.h>

#include "MenuState.h"
#include "GameState.h"
#include "../KeyboardKey.h"
#include "MenuState/BasicItem.h"
#include "MenuState/DualChoiceItem.h"

class GameEngine;

/** Menu action */
enum QuitMenuAction
{
	QUITMENU_GIVE_UP,
	QUITMENU_RETRY,
	QUITMENU_EXIT
};

/**
* QuitMenuGame State : used in 3 cases : give up, retry or exit
*/
class QuitMenuState : public MenuState
{
public:

	/** Constructor */
	QuitMenuState();

	/** Destructor */
	~QuitMenuState();

	virtual void init();

	virtual void term();

	virtual void load_gfx(CL_GraphicContext &gc, std::string skin);

	virtual void unload_gfx();

	virtual void action_performed(int selection, ActionType action_type);

	virtual void update_child();

	/** Set current action */
	void set_action(QuitMenuAction a);

private:

	/** Current action */
	QuitMenuAction _action;

	/** Item to choice to leave or to continue the game */
	DualChoiceItem _choice_item;

	/** Background panels */
	CL_Sprite _panel_give_up, _panel_retry, _panel_exit;

	/** Panel coords */
	int _panel_x, _panel_y;

};

#endif