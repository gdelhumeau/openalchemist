/********************************************************************
                          OpenAlchemist

  File : BasicItem.h
  Description : 
  License : GNU General Public License 2 or +
  Author : Guillaume Delhumeau <guillaume.delhumeau@gmail.com>


*********************************************************************/

#ifndef _BASIC_ITEM_H_
#define _BASIC_ITEM_H_

#include <ClanLib/display.h>

#include "MenuItem.h"

/**
 * Basic Item class
 */
class BasicItem : public MenuItem{

	protected:
	CL_Sprite *normal_sprite;
	CL_Sprite *selected_sprite;	
	CL_Sprite *locked_sprite;
	
	public:
		
	void set_gfx(CL_Sprite *normal_sprite, CL_Sprite *selected_sprite, CL_Sprite *locked_sprite);
	void unload_gfx();

	void draw();
	void events();
	
	BasicItem();	
	~BasicItem();

};



#endif
