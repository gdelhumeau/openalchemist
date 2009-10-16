// **********************************************************************
//                            OpenAlchemist
//                        ---------------------
//
//  File        : MenuState.h
//  Description : 
//  Author      : Guillaume Delhumeau <guillaume.delhumeau@gmail.com>
//  License     : GNU General Public License 2 or higher
//
// **********************************************************************

#ifndef _MENU_STATE_H_
#define _MENU_STATE_H_

#include <ClanLib/display.h>

#include "GameState.h"
#include "../KeyboardKey.h"
#include "MenuState/MenuItem.h"

class GameEngine;

/**
* Menu State - a based class for all menus
*/
class MenuState : public GameState{

public:

	/** Constructor */
	MenuState();

	virtual void init() = 0;

	virtual void deinit() = 0;

	virtual void load_gfx(CL_GraphicContext &gc, std::string skin) = 0;

	virtual void unload_gfx() = 0;

	virtual void draw(CL_GraphicContext &gc);

	virtual void update(CL_GraphicContext &gc);

	virtual void events(Window & window);

	virtual bool front_layer_behind();
	
	/** Action performed - propaged to derivated class */
	virtual void action_performed(int selection, int action_type) = 0;

	/** Update derivated class */
	virtual void update_child() = 0;
	
	/** Start the menu */
	void start();

protected:

	/** Menu state (is it appearing, active, disappearing...) */
	int _state;

	/** Alpha value of the menu */
	float _alpha;

	/** Menu Items (widgets) */
	std::vector<MenuItem*> _items;

	/** Background sprite */
	CL_Sprite _background;  

	/** Current selection inside the menu */
	int _selection;

	/** X mouse coord */
	int _mouse_x;

	/** Y mouse coord */
	int _mouse_y;

	/** Is mouse button clicked */
	bool _mouse_is_clicked;

	/** Set background sprite */
	void _set_background_sprite(CL_Sprite & background);

	/** Make menu appear */
	void _appear();

	/** Make menu disappear */
	void _disappear();

	/** Start menu apparition */
	void _start_disappear();

	/** Mouse events */
	void _mouse_events(Window & window);

};

#endif
