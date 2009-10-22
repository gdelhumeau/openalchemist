// **********************************************************************
//                            OpenAlchemist
//                        ---------------------
//
//  File        : DualChoiceItem.cpp
//  Description : 
//  Author      : Guillaume Delhumeau <guillaume.delhumeau@gmail.com>
//  License     : GNU General Public License 2 or higher
//
// **********************************************************************

#include <iostream>
#include "../../CommonResources.h"
#include "DualChoiceItem.h"
#include "../../memory.h"

/************************************************************************/
/* Constructor                                                          */
/************************************************************************/
DualChoiceItem::DualChoiceItem()
{
	_selection = CHOICE_LEFT;
}

/************************************************************************/
/* Destructor                                                           */
/************************************************************************/
DualChoiceItem::~DualChoiceItem()
{
	unload_gfx();
}

/************************************************************************/
/* Set X2                                                               */
/************************************************************************/
void DualChoiceItem::set_x2(int x)
{
	_x2 = x;
}

/************************************************************************/
/* Set Y2                                                               */
/************************************************************************/
void DualChoiceItem::set_y2(int y)
{
	_y2 = y;
}

/************************************************************************/
/* Set GFX                                                              */
/************************************************************************/
void DualChoiceItem::set_gfx(CL_GraphicContext &gc, CL_ResourceManager & gfx,
							 std::string normal_left, std::string selected_left,
							 std::string normal_right, std::string selected_right)
{
	unload_gfx();
	_normal_sprite_left  = CL_Sprite(gc, normal_left, &gfx);
	_selected_sprite_left = CL_Sprite(gc, selected_left, &gfx);
	_normal_sprite_right = CL_Sprite(gc, normal_right, &gfx);
	_selected_sprite_right = CL_Sprite(gc, selected_right, &gfx);   
}

/************************************************************************/
/* Unload GFX                                                           */
/************************************************************************/
void DualChoiceItem::unload_gfx()
{
}

/************************************************************************/
/* Draw                                                                 */
/************************************************************************/
void DualChoiceItem::draw(CL_GraphicContext &gc)
{
	_selected_sprite_left  .update();
	_selected_sprite_right .update();
	_normal_sprite_left    .update();
	_normal_sprite_right   .update();

	if(_selection == CHOICE_LEFT)
	{
		_selected_sprite_left.set_alpha(_alpha);
		_normal_sprite_right.set_alpha(_alpha);

		_selected_sprite_left.draw(gc, _x, _y);
		_normal_sprite_right.draw(gc, _x2, _y2);
	}
	else
	{
		_normal_sprite_left.set_alpha(_alpha);
		_selected_sprite_right.set_alpha(_alpha);

		_normal_sprite_left.draw(gc, _x, _y);
		_selected_sprite_right.draw(gc, _x2, _y2);
	}
}

/************************************************************************/
/* Action performed                                                     */
/************************************************************************/
void DualChoiceItem::action_performed(ActionType action_type)
{
	if(ACTION_TYPE_LEFT == action_type)
	{
		_selection = CHOICE_LEFT;
	}

	if(ACTION_TYPE_RIGHT == action_type)
	{
		_selection = CHOICE_RIGHT;
	}
}

/************************************************************************/
/* Is inside                                                            */
/************************************************************************/
bool DualChoiceItem::is_inside(int x, int y)
{
	return x >= _x && x <= _x2 + _normal_sprite_right.get_width() &&
		y >= _y && y <= _y2 + _normal_sprite_right.get_height();
}

/************************************************************************/
/* Mouse moved                                                          */
/************************************************************************/
void DualChoiceItem::mouse_moved(int mouse_x, int mouse_y)
{
	if(mouse_x <= _x + _normal_sprite_left.get_width())
	{
		_selection = CHOICE_LEFT;
	}
	else if(mouse_x >= _x2)
	{
		_selection = CHOICE_RIGHT;
	}
}