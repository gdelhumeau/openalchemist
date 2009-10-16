// **********************************************************************
//                            OpenAlchemist
//                        ---------------------
//
//  File        : BasicItem.cpp
//  Description : 
//  Author      : Guillaume Delhumeau <guillaume.delhumeau@gmail.com>
//  License     : GNU General Public License 2 or higher
//
// **********************************************************************

#include "../../memory.h"
#include <iostream>
#include "BasicItem.h"

#pragma warning(disable:4244)

/************************************************************************/
/* Constructor                                                          */
/************************************************************************/
BasicItem::BasicItem()
{

}

/************************************************************************/
/* Destructor                                                           */
/************************************************************************/
BasicItem::~BasicItem()
{
	unload_gfx();
}

/************************************************************************/
/* Set GFX                                                              */
/************************************************************************/
void BasicItem::set_gfx(CL_GraphicContext &gc, CL_ResourceManager &gfx,
						std::string normal,
						std::string selected,
						std::string locked)
{
	unload_gfx();
	_normal_sprite = CL_Sprite(gc, normal, &gfx);
	_selected_sprite = CL_Sprite(gc, selected, &gfx);
	if(locked != "")
	{
		_is_locked = true;
		_locked_sprite = CL_Sprite(gc, locked, &gfx);;
	}
	else
	{
		_is_locked = false;
	}
}

/************************************************************************/
/* Unload GFX                                                           */
/************************************************************************/
void BasicItem::unload_gfx()
{

}

/************************************************************************/
/* Draw                                                                 */
/************************************************************************/
void BasicItem::draw(CL_GraphicContext &gc)
{
	if (_is_selected)
	{
		_selected_sprite.set_alpha(_alpha);
		_selected_sprite.draw(gc, _x, _y);
	}
	else if (_is_locked)
	{
		_locked_sprite.set_alpha(_alpha);
		_locked_sprite.draw(gc, _x, _y);
	}
	else
	{
		_normal_sprite.set_alpha(_alpha);
		_normal_sprite.draw(gc, _x, _y);
	}
}

/************************************************************************/
/* Action performed                                                     */
/************************************************************************/
void BasicItem::action_performed(ActionType action_type)
{

}

/************************************************************************/
/* Is inside                                                            */
/************************************************************************/
bool BasicItem::is_inside(int x, int y)
{
	return x >= _x && x <= _x + _normal_sprite.get_width() &&
		y >= _y && y <= _y + _normal_sprite.get_height();
}

/************************************************************************/
/* Mouse moved                                                          */
/************************************************************************/
void BasicItem::mouse_moved(int mouse_x, int mouse_y)
{

}