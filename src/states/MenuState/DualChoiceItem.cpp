/********************************************************************
                          OpenAlchemist

  File : DualChoiceItem.cpp
  Description : 
  License : GNU General Public License 2 or +
  Author : Guillaume Delhumeau <guillaume.delhumeau@gmail.com>


 *********************************************************************/

#include <iostream>
#include "DualChoiceItem.h"

DualChoiceItem::DualChoiceItem()
{
    normal_sprite_left = NULL;
    selected_sprite_left = NULL;
    normal_sprite_right = NULL;
    selected_sprite_right = NULL;
		_selection = CHOICE_LEFT;
}

DualChoiceItem::~DualChoiceItem()
{
    unload_gfx();
}

void DualChoiceItem::set_gfx(CL_Sprite *normal_sprite_left_,
			     CL_Sprite *selected_sprite_left_,
			     CL_Sprite *normal_sprite_right_,
			     CL_Sprite *selected_sprite_right_)
{
  unload_gfx();
	normal_sprite_left  = normal_sprite_left_;
	selected_sprite_left = selected_sprite_left_;
	normal_sprite_right = normal_sprite_right_;
	selected_sprite_right = selected_sprite_right_;
   
}

void DualChoiceItem::unload_gfx()
{
    if (normal_sprite_left != NULL)
    {
        delete normal_sprite_left;
        normal_sprite_left = NULL;
    }
    if (selected_sprite_left != NULL)
    {
        delete selected_sprite_left;
        selected_sprite_left = NULL;
    }
    if (normal_sprite_right != NULL)
    {
        delete normal_sprite_right;
        normal_sprite_right = NULL;
    }
    if (selected_sprite_right != NULL)
    {
        delete selected_sprite_right;
        selected_sprite_right = NULL;
    }
  
}

void DualChoiceItem::draw()
{
	if(_selection == CHOICE_LEFT)
	{
			selected_sprite_left -> set_alpha(alpha);
			normal_sprite_right -> set_alpha(alpha);
		
			selected_sprite_left -> draw(x, y);
			normal_sprite_right -> draw(x + selected_sprite_left -> get_width(), y);
	}
	else
	{
			normal_sprite_left -> set_alpha(alpha);
			selected_sprite_right -> set_alpha(alpha);
		
			normal_sprite_left -> draw(x, y);
			selected_sprite_right -> draw(x + normal_sprite_left -> get_width(), y);
	}
}

void DualChoiceItem::events()
{
}
