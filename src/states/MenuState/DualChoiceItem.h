/********************************************************************
                          OpenAlchemist

  File : DualChoiceItem.h
  Description : 
  License : GNU General Public License 2 or +
  Author : Guillaume Delhumeau <guillaume.delhumeau@gmail.com>


 *********************************************************************/

#ifndef _DUAL_CHOICE_ITEM_H_
#define _DUAL_CHOICE_ITEM_H_

#include <ClanLib/display.h>

#include "MenuItem.h"

enum DUAL_CHOICES
{
	CHOICE_LEFT,
	CHOICE_RIGHT
};

/**
 * Dual Choice Item class
 */
class DualChoiceItem : public MenuItem
{
protected:
    CL_Sprite *normal_sprite_left;
    CL_Sprite *selected_sprite_left;
    CL_Sprite *normal_sprite_right;
    CL_Sprite *selected_sprite_right;

		int _selection;

public:

    void set_gfx(CL_Sprite *normal_sprite_left,
                 CL_Sprite *selected_sprite_left,
                 CL_Sprite *normal_sprite_right,
                 CL_Sprite *selected_sprite_right);
    void unload_gfx();

    void draw();
    void events();

    DualChoiceItem();
    ~DualChoiceItem();

};



#endif
