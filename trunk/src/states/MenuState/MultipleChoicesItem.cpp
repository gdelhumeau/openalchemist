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

MultipleChoicesItem::MultipleChoicesItem()
{
    _choices_list_p.clear();
    _selection = 0;
}

MultipleChoicesItem::~MultipleChoicesItem()
{
   unload_gfx();
}

void MultipleChoicesItem::unload_gfx()
{
    _choices_list_p.clear();
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
    _choices_list_p.push_back(CL_Sprite(gc, name, &gfx));
}

void MultipleChoicesItem::set_current_choice(unsigned int choice)
{
	if(choice < _choices_list_p.size())
	{
		_selection = choice;
	}
}

void MultipleChoicesItem::clear_choices()
{    
    _choices_list_p.clear();
}

void MultipleChoicesItem::draw(CL_GraphicContext &gc)
{
    if(selected)
    {
        _description_selected.set_alpha(alpha);
        _description_selected.draw(gc, x, y);
    }
    else if(locked)
		{
				_description_locked.set_alpha(alpha);
        _description_locked.draw(gc, x, y);
		}
		else				
    {
        _description_normal.set_alpha(alpha);
        _description_normal.draw(gc, x, y);
    }
    if(_selection < _choices_list_p.size())
    {
        _choices_list_p[_selection].set_alpha(alpha);
        _choices_list_p[_selection].draw(gc, _choice_x, _choice_y);
    }
}

void MultipleChoicesItem::action_performed(int action_type)
{
    if(ACTION_TYPE_LEFT == action_type && _selection > 0)
    {
        _selection --;
    }
    else if(ACTION_TYPE_RIGHT == action_type &&
            _selection < _choices_list_p.size()-1)
    {
        _selection ++;
    }

}

