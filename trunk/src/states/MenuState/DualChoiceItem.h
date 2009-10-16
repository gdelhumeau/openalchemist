// **********************************************************************
//                            OpenAlchemist
//                        ---------------------
//
//  File        : DualChoiceItem.h
//  Description : 
//  Author      : Guillaume Delhumeau <guillaume.delhumeau@gmail.com>
//  License     : GNU General Public License 2 or higher
//
// **********************************************************************

#ifndef _DUAL_CHOICE_ITEM_H_
#define _DUAL_CHOICE_ITEM_H_

#include <ClanLib/display.h>

#include "MenuItem.h"

/** DualChoice possible choices */
enum DualChoiceChoice
{
	CHOICE_LEFT,
	CHOICE_RIGHT
};

/**
* Dual Choice Item class
*/
class DualChoiceItem : public MenuItem
{

public:

	/** Constructor */
	DualChoiceItem();

	/** Destructor */
	~DualChoiceItem();

	/** Set item GFX */
	void set_gfx(CL_GraphicContext &gc, CL_ResourceManager & gfx,
		std::string normal_left, std::string selected_left,
		std::string normal_right, std::string selected_right);

	/** Unload GFX */
	void unload_gfx();

	/** Set choice 2 x coord */
	void set_x2(int x);

	/** Set choice 2 y coord */
	void set_y2(int y);

	/** Return current selection */
	DualChoiceChoice get_selection(){ return _selection; }
	
	virtual void draw(CL_GraphicContext &gc);
	
	virtual void action_performed(ActionType action_type);

	virtual bool quit_menu_on_action(){ return true; }

	virtual bool is_inside(int x, int y);

	virtual void mouse_moved(int mouse_x, int mouse_y);

protected:

	/** Default left sprite */
	CL_Sprite _normal_sprite_left;

	/** Selected left sprite */
	CL_Sprite _selected_sprite_left;

	/** Default right sprite */
	CL_Sprite _normal_sprite_right;

	/** Selected right sprite */
	CL_Sprite _selected_sprite_right;

	/** Current selection */
	DualChoiceChoice _selection;

	/** Right sprite coords */
	int _x2, _y2;

};



#endif
