/********************************************************************
                          OpenAlchemist

  File : MenuState.h
  Description : 
  License : GNU General Public License 2 or +
  Author : Guillaume Delhumeau <guillaume.delhumeau@gmail.com>


*********************************************************************/

#ifndef _MENU_STATE_H_
#define _MENU_STATE_H_

#include <ClanLib/display.h>

#include "GameState.h"
#include "../KeyboardKey.h"
#include "MenuState/MenuItem.h"


class GameEngine;

/**
* Menu State
*/
class MenuState : public GameState{

protected:

	int _step;
	double _alpha;
	std::vector<MenuItem*> _items;
	CL_Sprite _background;  
	int _selection;

	void _set_background_sprite(CL_Sprite & background);

	void _appear();
	void _disappear();

	void _start_disappear();

public:
	virtual void init() = 0;
	virtual void deinit() = 0;
	virtual void load_gfx(CL_GraphicContext &gc, std::string skin) = 0;
	virtual void unload_gfx() = 0;
	virtual void action_performed(int selection, int action_type) = 0;
	virtual void update_child() = 0;

	void draw(CL_GraphicContext &gc);
	void update(CL_GraphicContext &gc);
	void events(CL_DisplayWindow & window);

	void start();

	bool front_layer_behind();

	MenuState();


};

#endif
