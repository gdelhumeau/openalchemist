// **********************************************************************
//                            OpenAlchemist
//                        ---------------------
//
//  File        : MenuItem.h
//  Description : 
//  Author      : Guillaume Delhumeau <guillaume.delhumeau@gmail.com>
//  License     : GNU General Public License 2 or higher
//
// **********************************************************************

#ifndef _MENU_ITEM_H_
#define _MENU_ITEM_H_

#include <ClanLib/display.h>

enum ACTION_TYPE
{
	ACTION_TYPE_ENTER,
	ACTION_TYPE_LEFT,
	ACTION_TYPE_RIGHT
};

/**
* Generic (abstract) Menu Item class
*/
class MenuItem{

protected:

	int _x, _y;
	bool _selected;
	double _alpha;
	bool _locked;

public:

	virtual void draw(CL_GraphicContext &gc) = 0;
	virtual void action_performed(int action_type) = 0;
	virtual bool quit_menu_on_action() = 0;
	virtual bool is_inside(int x, int y) = 0;
	virtual void mouse_moved(int mouse_x, int mouse_y) = 0;

	void set_x(int x);
	void set_y(int y);
	void set_alpha(double alpha);
	void set_selected(bool selected);
	void set_locked(bool locked);

	bool is_locked(){return _locked;};

	MenuItem();	

};



#endif
