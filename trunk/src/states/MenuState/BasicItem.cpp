/********************************************************************
                          OpenAlchemist

  File : BasicItem.cpp
  Description : 
  License : GNU General Public License 2 or +
  Author : Guillaume Delhumeau <guillaume.delhumeau@gmail.com>


 *********************************************************************/

#include <iostream>
#include "BasicItem.h"

BasicItem::BasicItem()
{
    normal_sprite = NULL;
    selected_sprite = NULL;
    locked_sprite = NULL;
}

BasicItem::~BasicItem()
{
    unload_gfx();
}

void BasicItem::set_gfx(CL_Sprite *normal_sprite,
                        CL_Sprite *selected_sprite,
                        CL_Sprite *locked_sprite)
{
    unload_gfx();
    this -> normal_sprite = normal_sprite;
    this -> selected_sprite = selected_sprite;
    this -> locked_sprite = locked_sprite;
}

void BasicItem::unload_gfx()
{
    if (normal_sprite != NULL)
    {
        delete normal_sprite;
        normal_sprite = NULL;
    }
    if (selected_sprite != NULL)
    {
        delete selected_sprite;
        selected_sprite = NULL;
    }
    if (locked_sprite != NULL)
    {
        delete locked_sprite;
        locked_sprite = NULL;
    }
}

void BasicItem::draw()
{
    if (selected)
    {
        selected_sprite -> set_alpha(alpha);
        selected_sprite -> draw(x, y);
    }
    else if (locked)
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

void BasicItem::action_performed(int action_type)
{

}
