// **********************************************************************
//                            OpenAlchemist
//                        ---------------------
//
//  File        : BasicItem.h
//  Description : 
//  Author      : Guillaume Delhumeau <guillaume.delhumeau@gmail.com>
//  License     : GNU General Public License 2 or higher
//
// **********************************************************************

#ifndef _BASIC_ITEM_H_
#define _BASIC_ITEM_H_

#include <ClanLib/display.h>

#include "MenuItem.h"

/**
* Basic Item class
*/
class BasicItem : public MenuItem{

public:

	/** Constructor */
	BasicItem();	

	/** Destructor */
	~BasicItem();

	/** Set item gfx */
	void set_gfx(CL_GraphicContext &gc, CL_ResourceManager & gfx,
		std::string normal, std::string selected, std::string locked_sprite = "");
	
	/** Unload GFX */
	void unload_gfx();
	
	virtual void draw(CL_GraphicContext &gc);
	
	virtual void action_performed(ActionType action_type);
	
	virtual void mouse_moved(int mouse_x, int mouse_y);
	
	virtual bool quit_menu_on_action(){ return true; }
	
	virtual bool is_inside(int x, int y);

protected:

	/** Default sprite */
	CL_Sprite _normal_sprite;

	/** Sprite when the item is selected */
	CL_Sprite _selected_sprite;	

	/** Sprite when the item is locked */
	CL_Sprite _locked_sprite;

	/** Is the item locked */
	bool _is_locked;

};



#endif
