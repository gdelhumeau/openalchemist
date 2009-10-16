// **********************************************************************
//                            OpenAlchemist
//                        ---------------------
//
//  File        : MultipleChoiceItem.cpp
//  Description : 
//  Author      : Guillaume Delhumeau <guillaume.delhumeau@gmail.com>
//  License     : GNU General Public License 2 or higher
//
// **********************************************************************

#include <iostream>
#include "MultipleChoicesItem.h"
#include "../../memory.h"

#pragma warning(disable:4244)

/************************************************************************/
/* Constructor                                                          */
/************************************************************************/
MultipleChoicesItem::MultipleChoicesItem()
{
	_choices_list.clear();
	_selection = 0;
}

/************************************************************************/
/* Destructor                                                           */
/************************************************************************/
MultipleChoicesItem::~MultipleChoicesItem()
{
	unload_gfx();
}

/************************************************************************/
/* Unload GFX                                                           */
/************************************************************************/
void MultipleChoicesItem::unload_gfx()
{
	_choices_list.clear();
}

/************************************************************************/
/* Is inside                                                            */
/************************************************************************/
bool MultipleChoicesItem::is_inside(int x, int y)
{
	return x >= _x && x <= _choice_x + _choices_list[_selection].get_width() &&
		y >= _y && y <= _y + _description_normal.get_height();
}

/************************************************************************/
/* Set description sprites                                              */
/************************************************************************/
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
		_is_locked = false;
	}
	else
	{
		_description_locked = CL_Sprite(gc, locked, &gfx);
		_is_locked = true;
	}
}

/************************************************************************/
/* Add choice                                                           */
/************************************************************************/
void MultipleChoicesItem::add_choice(CL_GraphicContext & gc,
									 CL_ResourceManager & gfx,
									 std::string name)
{
	_choices_list.push_back(CL_Sprite(gc, name, &gfx));
}

/************************************************************************/
/* Set current choice                                                   */
/************************************************************************/
void MultipleChoicesItem::set_current_choice(unsigned int choice)
{
	if(choice < _choices_list.size())
	{
		_selection = choice;
	}
}

/************************************************************************/
/* Clear choices                                                        */
/************************************************************************/
void MultipleChoicesItem::clear_choices()
{    
	_choices_list.clear();
}

/************************************************************************/
/* Draw                                                                 */
/************************************************************************/
void MultipleChoicesItem::draw(CL_GraphicContext &gc)
{
	if(_is_selected)
	{
		_description_selected.set_alpha(_alpha);
		_description_selected.draw(gc, _x, _y);
	}
	else if(_is_locked)
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

/************************************************************************/
/* Action performed                                                     */
/************************************************************************/
void MultipleChoicesItem::action_performed(ActionType action_type)
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
	else if(ACTION_TYPE_MOUSE == action_type)
	{
		_selection++;
		if(_selection >= _choices_list.size())
		{
			_selection = 0;
		}
	}

}

/************************************************************************/
/* Mouse moved                                                          */
/************************************************************************/
void MultipleChoicesItem::mouse_moved(int mouse_x, int mouse_y)
{

}