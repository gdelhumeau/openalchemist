/********************************************************************
                          OpenAlchemist

  File : BasicItem.cpp
  Description : 
  License : GNU General Public License 2 or +
  Author : Guillaume Delhumeau <guillaume.delhumeau@gmail.com>


 *********************************************************************/

#include "../../memory.h"
#include <iostream>
#include "BasicItem.h"

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
    if (selected)
    {
        _selected_sprite.set_alpha(alpha);
        _selected_sprite.draw(gc, x, y);
    }
    else if (locked)
    {
        _locked_sprite.set_alpha(alpha);
        _locked_sprite.draw(gc, x, y);
    }
    else
    {
        _normal_sprite.set_alpha(alpha);
        _normal_sprite.draw(gc, x, y);
    }
}

void BasicItem::action_performed(int action_type)
{

}
