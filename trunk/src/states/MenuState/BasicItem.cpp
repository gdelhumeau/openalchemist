/********************************************************************
                          OpenAlchemist

  File : BasicItem.cpp
  Description : 
  License : GNU General Public License 2 or +
  Author : Guillaume Delhumeau <guillaume.delhumeau@gmail.com>


*********************************************************************/

#include "BasicItem.h"

BasicItem::BasicItem()
{
	
}

void BasicItem::set_gfx(CL_Sprite *normal_sprite,
												CL_Sprite *selected_sprite,
												CL_Sprite *locked_sprite)
{
	this -> normal_sprite = normal_sprite;
	this -> selected_sprite = selected_sprite;
	this -> locked_sprite = locked_sprite;
}

void BasicItem::draw()
{
	if(selected)
	{
		selected_sprite -> set_alpha(alpha);
		selected_sprite -> draw(x, y);
	}
	else if(locked)
	{
		locked_sprite -> set_alpha(alpha);
		locked_sprite -> draw(x, y);
	}
	else
	{
		normal_sprite -> set_alpha(alpha);
		normal_sprite -> draw(x, y);
	}
}

void BasicItem::events()
{
}