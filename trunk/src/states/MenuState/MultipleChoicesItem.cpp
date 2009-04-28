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
    _p_description_normal = NULL;
    _p_description_selected = NULL;
}

MultipleChoicesItem::~MultipleChoicesItem()
{
   unload_gfx();
}

void MultipleChoicesItem::unload_gfx()
{
	  if(_p_description_normal)
    {
        my_delete(_p_description_normal);
				_p_description_normal = NULL;
    }
    if(_p_description_selected)
    {
        my_delete(_p_description_selected);
				_p_description_selected = NULL;
    }
	  for(unsigned int i = 0; i < _choices_list_p.size(); ++i)
    {
        my_delete(_choices_list_p[i]);
    }
    _choices_list_p.clear();
}

void MultipleChoicesItem::set_description_sprites(CL_Sprite * p_normal_sprite, CL_Sprite * p_selected_sprite)
{
    if(_p_description_normal)
    {
        delete _p_description_normal;
    }
    _p_description_normal = p_normal_sprite;

    if(_p_description_selected)
    {
        delete _p_description_selected;
    }
    _p_description_selected = p_selected_sprite;
}

void MultipleChoicesItem::add_choice(CL_Sprite * p_sprite)
{
    _choices_list_p.push_back(p_sprite);
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
    for(unsigned int i = 0; i < _choices_list_p.size(); ++i)
    {
        delete _choices_list_p[i];
    }
    _choices_list_p.clear();
}

void MultipleChoicesItem::draw()
{
    if(selected)
    {
        _p_description_selected -> set_alpha(alpha);
        _p_description_selected -> draw(x, y);
    }
    else
    {
        _p_description_normal -> set_alpha(alpha);
        _p_description_normal -> draw(x, y);
    }
    if(_selection < _choices_list_p.size())
    {
        _choices_list_p[_selection] -> set_alpha(alpha);
        _choices_list_p[_selection] -> draw(_choice_x, _choice_y);
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

