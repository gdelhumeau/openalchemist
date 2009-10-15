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

BasicItem::BasicItem()
{

}

BasicItem::~BasicItem()
{
	unload_gfx();
}

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
		_has_locked = true;
		_locked_sprite = CL_Sprite(gc, locked, &gfx);;
	}
	else
	{
		_has_locked = false;
	}
}

void BasicItem::unload_gfx()
{

}

void BasicItem::draw(CL_GraphicContext &gc)
{
	if (_selected)
	{
		_selected_sprite.set_alpha(_alpha);
		_selected_sprite.draw(gc, _x, _y);
	}
	else if (_locked)
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

void BasicItem::action_performed(int action_type)
{

}

bool BasicItem::is_inside(int x, int y)
{
	return x >= _x && x <= _x + _normal_sprite.get_width() &&
		y >= _y && y <= _y + _normal_sprite.get_height();
}

void BasicItem::mouse_moved(int mouse_x, int mouse_y)
{

}