/********************************************************************
                          OpenAlchemist

  File : DualChoiceItem.cpp
  Description : 
  License : GNU General Public License 2 or +
  Author : Guillaume Delhumeau <guillaume.delhumeau@gmail.com>


 *********************************************************************/

#include <iostream>
#include "../../CommonResources.h"
#include "DualChoiceItem.h"
#include "../../memory.h"

DualChoiceItem::DualChoiceItem()
{
	_selection = CHOICE_LEFT;
}

DualChoiceItem::~DualChoiceItem()
{
    unload_gfx();
}

void DualChoiceItem::set_x2(int x)
{
	_x2 = x;
}

void DualChoiceItem::set_y2(int y)
{
	_y2 = y;
}

void DualChoiceItem::set_gfx(CL_GraphicContext &gc, CL_ResourceManager & gfx,
	            	std::string normal_left, std::string selected_left,
                std::string normal_right, std::string selected_right)
{
  unload_gfx();
	_p_normal_sprite_left  = CL_Sprite(gc, normal_left, &gfx);
	_p_selected_sprite_left = CL_Sprite(gc, selected_left, &gfx);
	_p_normal_sprite_right = CL_Sprite(gc, normal_right, &gfx);
	_p_selected_sprite_right = CL_Sprite(gc, selected_right, &gfx);   
}

void DualChoiceItem::unload_gfx()
{
  
  
}

void DualChoiceItem::draw(CL_GraphicContext &gc)
{
	_p_selected_sprite_left  .update();
	_p_selected_sprite_right .update();
	_p_normal_sprite_left    .update();
	_p_normal_sprite_right   .update();
	
	if(_selection == CHOICE_LEFT)
	{
		_p_selected_sprite_left.set_alpha(alpha);
		_p_normal_sprite_right.set_alpha(alpha);
		
		_p_selected_sprite_left.draw(gc, x, y);
		_p_normal_sprite_right.draw(gc, _x2, _y2);
	}
	else
	{
		_p_normal_sprite_left.set_alpha(alpha);
		_p_selected_sprite_right.set_alpha(alpha);
		
		_p_normal_sprite_left.draw(gc, x, y);
		_p_selected_sprite_right.draw(gc, _x2, _y2);
	}
}

void DualChoiceItem::action_performed(int action_type)
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
