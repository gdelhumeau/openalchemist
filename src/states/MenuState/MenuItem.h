/********************************************************************
                          OpenAlchemist

  File : MenuItem.h
  Description : 
  License : GNU General Public License 2 or +
  Author : Guillaume Delhumeau <guillaume.delhumeau@gmail.com>


*********************************************************************/

#ifndef _MENU_ITEM_H_
#define _MENU_ITEM_H_

/**
 * Generic (abstract) Menu Item class
 */
class MenuItem{

	protected:
	
	int x, y;
	bool selected;
	double alpha;
	bool locked;
	
	public:
		
	virtual void draw();
	virtual void events();

	void set_x(int x);
	void set_y(int y);
	void set_alpha(double alpha);
	void set_selected(bool selected);
	void set_locked(bool locked);

	bool is_locked(){return locked;};
	
	MenuItem();	

};



#endif
