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
* Multiples choices item
*/
class MultipleChoicesItem : public MenuItem{

public:

	/** Constructor */
	MultipleChoicesItem();

	/** Destructor */
	~MultipleChoicesItem();	

	virtual void draw(CL_GraphicContext& gc);

	virtual void action_performed(ActionType action_type);

	virtual bool quit_menu_on_action(){return false;}

	virtual bool is_inside(int x, int y);

	virtual void mouse_moved(int mouse_x, int mouse_y);

	/** Set choices X coord */
	void set_choice_x(int x){_choice_x = x;}

	/** Set choices Y coord */
	void set_choice_y(int y){_choice_y = y;}

	/** Set sprites for item description (not choice) */
	void set_description_sprites(CL_GraphicContext& gc, CL_ResourceManager& gfx,
		std::string normal, std::string selected, std::string locked = "");

	/** Add a choice */
	void add_choice(CL_GraphicContext& gc, CL_ResourceManager& gfx, std::string name);

	/** Set current choice */
	void set_current_choice(unsigned int choice);

	/** Return current choice */
	unsigned int get_current_choice(){ return _selection; }

	/** Clear choices */
	void clear_choices();

	/** Unload GFX */
	void unload_gfx();

protected:

	/** Choices list */
	std::vector<CL_Sprite> _choices_list;

	/** Choices X coord */
	int _choice_x;

	/** Choices Y coord */
	int _choice_y;

	/** Current selection */
	unsigned int _selection;

	/** Lock status */
	bool _is_locked;

	/** Default description sprite  */
	CL_Sprite _description_normal;

	/** Description sprite when the item is selected in the menu */
	CL_Sprite _description_selected;

	/** Description sprite when the item is locked */
	CL_Sprite _description_locked;

};



#endif
