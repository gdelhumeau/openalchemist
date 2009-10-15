// **********************************************************************
//                            OpenAlchemist
//                        ---------------------
//
//  File        : MultipleChoiceItem.h
//  Description : 
//  Author      : Guillaume Delhumeau <guillaume.delhumeau@gmail.com>
//  License     : GNU General Public License 2 or higher
//
// **********************************************************************

#ifndef _MULTIPLE_CHOICES_ITEM_H_
#define _MULTIPLE_CHOICES_ITEM_H_

#include <vector>
#include <ClanLib/display.h>
#include "MenuItem.h"

/**
* Generic (abstract) Menu Item class
*/
class MultipleChoicesItem : public MenuItem{

protected:
	int _choice_x;
	int _choice_y;
	unsigned int _selection;
	bool _has_locked;

	std::vector<CL_Sprite> _choices_list;
	CL_Sprite _description_normal;
	CL_Sprite _description_selected;
	CL_Sprite _description_locked;

public:

	virtual void draw(CL_GraphicContext &gc);
	virtual void action_performed(int action_type);
	virtual bool quit_menu_on_action(){return false;}
	virtual bool is_inside(int x, int y);
	virtual void mouse_moved(int mouse_x, int mouse_y);

	void set_choice_x(int x){_choice_x = x;}
	void set_choice_y(int y){_choice_y = y;}

	void set_description_sprites(CL_GraphicContext &gc, CL_ResourceManager & gfx,
		std::string normal, std::string selected, std::string locked = "");

	void add_choice(CL_GraphicContext & gc, CL_ResourceManager & gfx, std::string name);
	void set_current_choice(unsigned int choice);
	unsigned int get_current_choice(){ return _selection; }

	void clear_choices();

	void unload_gfx();

	MultipleChoicesItem();
	~MultipleChoicesItem();	

};



#endif
