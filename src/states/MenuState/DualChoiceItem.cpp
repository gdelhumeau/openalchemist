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
    _p_normal_sprite_left = NULL;
    _p_selected_sprite_left = NULL;
    _p_normal_sprite_right = NULL;
    _p_selected_sprite_right = NULL;
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

void DualChoiceItem::set_gfx(CL_Sprite *normal_sprite_left_,
			     CL_Sprite *selected_sprite_left_,
			     CL_Sprite *normal_sprite_right_,
			     CL_Sprite *selected_sprite_right_)
{
  unload_gfx();
	_p_normal_sprite_left  = normal_sprite_left_;
	_p_selected_sprite_left = selected_sprite_left_;
	_p_normal_sprite_right = normal_sprite_right_;
	_p_selected_sprite_right = selected_sprite_right_;
   
}

void DualChoiceItem::unload_gfx()
{
    if (_p_normal_sprite_left != NULL)
    {
        my_delete( _p_normal_sprite_left);
        _p_normal_sprite_left = NULL;
    }
    if (_p_selected_sprite_left != NULL)
    {
        my_delete(_p_selected_sprite_left);
        _p_selected_sprite_left = NULL;
    }
    if (_p_normal_sprite_right != NULL)
    {
        my_delete(_p_normal_sprite_right);
        _p_normal_sprite_right = NULL;
    }
    if (_p_selected_sprite_right != NULL)
    {
        my_delete(_p_selected_sprite_right);
        _p_selected_sprite_right = NULL;
    }
  
}

void DualChoiceItem::draw()
{
	_p_selected_sprite_left  -> update();
	_p_selected_sprite_right -> update();
	_p_normal_sprite_left    -> update();
	_p_normal_sprite_right   -> update();
	
	if(_selection == CHOICE_LEFT)
	{
		_p_selected_sprite_left -> set_alpha(alpha);
		_p_normal_sprite_right -> set_alpha(alpha);
		
		_p_selected_sprite_left -> draw(x, y);
		_p_normal_sprite_right -> draw(_x2, _y2);
	}
	else
	{
		_p_normal_sprite_left -> set_alpha(alpha);
		_p_selected_sprite_right -> set_alpha(alpha);
		
		_p_normal_sprite_left -> draw(x, y);
		_p_selected_sprite_right -> draw(_x2, _y2);
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
