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

protected:
	CL_Sprite _normal_sprite;
	CL_Sprite _selected_sprite;	
	CL_Sprite _locked_sprite;
	bool _has_locked;

public:

	void set_gfx(CL_GraphicContext &gc, CL_ResourceManager & gfx,
		std::string normal, std::string selected, std::string locked_sprite = "");
	void unload_gfx();

	void draw(CL_GraphicContext &gc);
	void action_performed(int action_type);

	virtual bool quit_menu_on_action(){ return true; }
	virtual bool is_inside(int x, int y);
	virtual void mouse_moved(int mouse_x, int mouse_y);

	BasicItem();	
	~BasicItem();

};



#endif
