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

enum
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
    CL_Sprite _normal_sprite_left;
    CL_Sprite _selected_sprite_left;
    CL_Sprite _normal_sprite_right;
    CL_Sprite _selected_sprite_right;

	int _selection;
	
	int _x2, _y2;

public:

    void set_gfx(CL_GraphicContext &gc, CL_ResourceManager & gfx,
	            	std::string normal_left, std::string selected_left,
                std::string normal_right, std::string selected_right);
    void unload_gfx();
    
    void set_x2(int x);
    void set_y2(int y);

    void draw(CL_GraphicContext &gc);
    void action_performed(int action_type);
    
    int get_selection(){ return _selection; }
    virtual bool quit_menu_on_action(){ return true; }

    DualChoiceItem();
    ~DualChoiceItem();

};



#endif
