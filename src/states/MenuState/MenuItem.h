// **********************************************************************
//                            OpenAlchemist
//                        ---------------------
//
//  File        : MenuItem.h
//  Description : 
//  Author      : Guillaume Delhumeau <guillaume.delhumeau@gmail.com>
//  License     : GNU General Public License 2 or higher
//
// **********************************************************************

#ifndef _MENU_ITEM_H_
#define _MENU_ITEM_H_

#include <ClanLib/display.h>

/** Action performed type */
enum ActionType{
	ACTION_TYPE_ENTER,
	ACTION_TYPE_LEFT,
	ACTION_TYPE_RIGHT,
	ACTION_TYPE_UP,
	ACTION_TYPE_DOWN,
	ACTION_TYPE_MOUSE
};

/**
* Generic (abstract) Menu Item class
*/
class MenuItem{

public:

	/** Constructor */
	MenuItem();	

	/** Draw item */
	virtual void draw(CL_GraphicContext &gc) = 0;

	/** Action is performed on the item */
	virtual void action_performed(ActionType action_type) = 0;

	/** A mouse moved event */
	virtual void mouse_moved(int mouse_x, int mouse_y) = 0;

	/** Return if the menu should quit after an action performed */
	virtual bool quit_menu_on_action() = 0;

	/** Return if the give coords are inside the item or not */
	virtual bool is_inside(int x, int y) = 0;
	
	/** Set X coord */
	void set_x(int x);

	/** Set Y coord */
	void set_y(int y);

	/** Set item alpha blending */
	void set_alpha(float alpha);

	/** Set if the item is selected */
	void set_selected(bool selected);

	/** Set if the item is locked */
	void set_locked(bool locked);

	/** Return if the item is locked */
	bool is_locked(){return _is_locked;};

protected:

	/** Item coords */
	int _x, _y;

	/** If items is selected */
	bool _is_selected;

	/** Item alpha blending */
	float _alpha;

	/** Lock state */
	bool _is_locked;

};



#endif
