/********************************************************************
                          OpenAlchemist
 
  File : MultipleChoiceItem.cpp
  Description : 
  License : GNU General Public License 2 or +
  Author : Guillaume Delhumeau <guillaume.delhumeau@gmail.com>
 
 
*********************************************************************/

#include <iostream>
#include "MultipleChoicesItem.h"
#include "../../memory.h"

#pragma warning(disable:4244)

MultipleChoicesItem::MultipleChoicesItem()
{
	_choices_list.clear();
	_selection = 0;
}

MultipleChoicesItem::~MultipleChoicesItem()
{
	unload_gfx();
}

void MultipleChoicesItem::unload_gfx()
{
	_choices_list.clear();
}

bool MultipleChoicesItem::is_inside(int x, int y)
{
	return x >= _x && x <= _choice_x + _choices_list[_selection].get_width() &&
		y >= _y && y <= _y + _description_normal.get_height();
}

void MultipleChoicesItem::set_description_sprites(CL_GraphicContext &gc,
												  CL_ResourceManager & gfx,
												  std::string normal,
												  std::string selected,
												  std::string locked)
{
	_description_normal = CL_Sprite(gc, normal, &gfx);
	_description_selected = CL_Sprite(gc, selected, &gfx);
	if(locked == "")
	{
		_has_locked = false;
	}
	else
	{
		_description_locked = CL_Sprite(gc, locked, &gfx);
		_has_locked = true;
	}
}

void MultipleChoicesItem::add_choice(CL_GraphicContext & gc,
									 CL_ResourceManager & gfx,
									 std::string name)
{
	_choices_list.push_back(CL_Sprite(gc, name, &gfx));
}

void MultipleChoicesItem::set_current_choice(unsigned int choice)
{
	if(choice < _choices_list.size())
	{
		_selection = choice;
	}
}

void MultipleChoicesItem::clear_choices()
{    
	_choices_list.clear();
}

void MultipleChoicesItem::draw(CL_GraphicContext &gc)
{
	if(_selected)
	{
		_description_selected.set_alpha(_alpha);
		_description_selected.draw(gc, _x, _y);
	}
	else if(_locked)
	{
		_description_locked.set_alpha(_alpha);
		_description_locked.draw(gc, _x, _y);
	}
	else				
	{
		_description_normal.set_alpha(_alpha);
		_description_normal.draw(gc, _x, _y);
	}
	if(_selection < _choices_list.size())
	{
		_choices_list[_selection].set_alpha(_alpha);
		_choices_list[_selection].draw(gc, _choice_x, _choice_y);
	}
}

void MultipleChoicesItem::action_performed(int action_type)
{
	if(ACTION_TYPE_LEFT == action_type && _selection > 0)
	{
		_selection --;
	}
	else if(ACTION_TYPE_RIGHT == action_type &&
		_selection < _choices_list.size()-1)
	{
		_selection ++;
	}
	else if(ACTION_TYPE_ENTER == action_type)
	{
		_selection++;
		if(_selection >= _choices_list.size())
		{
			_selection = 0;
		}
	}

}

void MultipleChoicesItem::mouse_moved(int mouse_x, int mouse_y)
{

}