/********************************************************************
                          OpenAlchemist

  File : MultipleChoiceItem.h
  Description : 
  License : GNU General Public License 2 or +
  Author : Guillaume Delhumeau <guillaume.delhumeau@gmail.com>


*********************************************************************/

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
	
	std::vector<CL_Sprite*> _choices_list_p;
	CL_Sprite * _p_description_normal;
	CL_Sprite * _p_description_selected;
		
	public:
		
	virtual void draw();
	virtual void action_performed(int action_type);
	virtual bool quit_menu_on_action(){return false;}

	void set_choice_x(int x){_choice_x = x;}
	void set_choice_y(int y){_choice_y = y;}
	
	void set_description_sprites(CL_Sprite * p_normal_sprite, CL_Sprite * p_selected_sprite);
	
	void add_choice(CL_Sprite * p_sprite);
	void set_current_choice(unsigned int choice);
	
	void clear_choices();
	
	MultipleChoicesItem();
	~MultipleChoicesItem();	

};



#endif
