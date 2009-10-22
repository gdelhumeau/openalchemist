// **********************************************************************
//                            OpenAlchemist
//                        ---------------------
//
//  File        : MenuState.cpp
//  Description : 
//  Author      : Guillaume Delhumeau <guillaume.delhumeau@gmail.com>
//  License     : GNU General Public License 2 or higher
//
// **********************************************************************

#include "../memory.h"
#include "MenuState.h"
#include "../CommonResources.h"
#include "../GameEngine.h"
#include "../Window.h"

/************************************************************************/
/* State                                                                */
/************************************************************************/
enum{
	STATE_APPEARING,
	STATE_ACTIVE,
	STATE_DISAPPEARING
};

/************************************************************************/
/* Constants                                                            */
/************************************************************************/
static const float APPEARING_SPEED = 0.003f;

/************************************************************************/
/* Constructor                                                          */
/************************************************************************/
MenuState::MenuState ()
{
	_selection = 0;
	_mouse_is_clicked = false;
	_items.clear();
}

/************************************************************************/
/* Front layer behind                                                   */
/************************************************************************/
bool MenuState::front_layer_behind ()
{
	return true;
}

/************************************************************************/
/* Set background sprite                                                */
/************************************************************************/
void MenuState::_set_background_sprite (CL_Sprite & background)
{
	this -> _background = background;
}

/************************************************************************/
/* Draw                                                                 */
/************************************************************************/
void MenuState::draw (CL_GraphicContext & gc)
{
	// Displaying background
	int x = 400 - _background.get_width () / 2;
	int y = 300 - _background.get_height () / 2;
	_background.draw (gc, x, y);

	// Displaying items
	std::vector<MenuItem*>::iterator it = _items.begin ();
	while (it != _items.end ())
	{
		MenuItem *item = (MenuItem*) * it;
		item -> draw (gc);
		++it;
	}

}

/************************************************************************/
/* Update                                                               */
/************************************************************************/
void MenuState::update (CL_GraphicContext & gc)
{
	switch (_state)
	{
	case STATE_APPEARING:
		_appear ();
		break;
	case STATE_DISAPPEARING:
		_disappear ();
		break;
	}
	this -> update_child ();
}

/************************************************************************/
/* Events                                                               */
/************************************************************************/
void MenuState::events (Window & window)
{
	CL_InputContext & ic = window.get_ic();

	// Leaving the state
	if (_p_common_resources -> key.escape->get (ic) || 
		_p_common_resources -> key.pause->get (ic))
	{
		_start_disappear ();
		_selection = -1;
	}

	// Key ENTER
	if (_p_common_resources -> key.enter -> get (ic))
	{
		if(_items[_selection] -> quit_menu_on_action())
		{
			_start_disappear ();
		}
		_items[_selection] -> action_performed(ACTION_TYPE_ENTER);
	}

	// Key LEFT
	if (_p_common_resources -> key.left -> get (ic))
	{
		_items[_selection] -> action_performed(ACTION_TYPE_LEFT);
		this -> action_performed (_selection, ACTION_TYPE_LEFT);
	}

	// Key RIGHT
	if (_p_common_resources -> key.right -> get (ic))
	{
		_items[_selection] -> action_performed(ACTION_TYPE_RIGHT);
		this -> action_performed (_selection, ACTION_TYPE_RIGHT);
	}


	// Key UP
	if (_p_common_resources -> key.up -> get (ic))
	{		
		_items[_selection] -> set_selected (false);
		bool changed = false;
		while (!changed)
		{
			if (_selection == 0)
			{
				_selection = _items.size () - 1;
			}
			else
			{
				_selection--;
			}

			if (!_items[_selection] -> is_locked ())
			{
				changed = true;
				_items[_selection] -> set_selected (true);
			}
		}
		_items[_selection] -> action_performed(ACTION_TYPE_UP);
	}

	// Key DOWN
	if (_p_common_resources -> key.down -> get (ic))
	{
		_items[_selection] -> set_selected (false);
		bool changed = false;
		while (!changed)
		{
			if (_selection == (int) _items.size () - 1)
			{
				_selection = 0;
			}
			else
			{
				_selection++;
			}

			if (!_items[_selection] -> is_locked ())
			{
				changed = true;
				_items[_selection] -> set_selected (true);
			}
		}
		_items[_selection] -> action_performed(ACTION_TYPE_DOWN);
	}

	// Mouse
	_mouse_events(window);
}

/************************************************************************/
/* Mouse events                                                         */
/************************************************************************/
void MenuState::_mouse_events(Window & window)
{
	CL_InputContext & ic = window.get_ic();
	if(ic.get_mouse_count() > 0)
	{
		CL_InputDevice & mouse = ic.get_mouse();

		float scale = 1/window.get_scale();
		float dx = (float)window.get_dx();
		float dy = (float)window.get_dy();

		// Mouse moved or clicked
		if(mouse.get_x() != _mouse_x || mouse.get_y() != _mouse_y
			|| mouse.get_keycode(CL_MOUSE_LEFT))
		{
			_mouse_x = mouse.get_x();
			_mouse_y = mouse.get_y();

			// Checking the selected item
			bool found = false;
			unsigned int i = 0;
			while (i<_items.size() && !found)
			{
				if(_items[i]->is_inside((int)(_mouse_x*scale-dx),
					(int)(_mouse_y*scale-dy) ))
				{
					found = true;
					if(!_items[i]->is_locked())
					{
						if(_selection >= 0)
						{
							_items[_selection] -> set_selected(false);
						}
						_selection = i;
						_items[i] -> set_selected(true);
						_items[i] -> mouse_moved((int)(_mouse_x*scale-dx),
							(int)(_mouse_y*scale-dy));
					}					
				}
				i++;
			}

			// If user click
			if(mouse.get_keycode(CL_MOUSE_LEFT))
			{
				if(!_mouse_is_clicked && !_items[_selection]->is_locked())
				{
					_mouse_is_clicked = true;
					if(_items[_selection] -> quit_menu_on_action())
					{
						_start_disappear ();
					}
					_items[_selection] -> action_performed(ACTION_TYPE_MOUSE);
				}
			}			
		}

		if(_mouse_is_clicked && !mouse.get_keycode(CL_MOUSE_LEFT))
		{
			_mouse_is_clicked = false;
		}
	}
}

/************************************************************************/
/* Start                                                                */
/************************************************************************/
void MenuState::start ()
{
	_selection = 0;
	// All items are not selected

	std::vector<MenuItem*>::iterator it = _items.begin ();
	while (it != _items.end ())
	{
		MenuItem *item = (MenuItem*) * it;
		item -> set_selected (false);
		++it;
	}
	// Except the selection
	_items[_selection] -> set_selected (true);

	// Now, beginning appearing
	_state = STATE_APPEARING;
	_alpha = 0.0;
}

/************************************************************************/
/* Appear                                                               */
/************************************************************************/
void MenuState::_appear ()
{
	// Updating alpha value
	if (_alpha + APPEARING_SPEED * _p_common_resources -> delta_time >= 1.0)
	{
		_state = STATE_ACTIVE;
		_alpha = 1.0;
	}
	else
	{
		_alpha += APPEARING_SPEED * _p_common_resources -> delta_time;
	}

	// Updating background sprite
	_background.set_alpha (_alpha);

	// Updating items
	std::vector<MenuItem*>::iterator it = _items.begin ();
	while (it != _items.end ())
	{
		MenuItem *item = (MenuItem*) * it;
		item -> set_alpha (_alpha);
		++it;
	}

}

/************************************************************************/
/* Disappear                                                            */
/************************************************************************/
void MenuState::_disappear ()
{
	// Updating alpha value
	_alpha -= APPEARING_SPEED * _p_common_resources -> delta_time;

	if (_alpha <= 0)
	{
		// Now perform child action or leaving the state
		if (_selection == -1)
			_p_common_resources -> p_engine -> stop_current_state ();
		else
			this -> action_performed (_selection, ACTION_TYPE_ENTER);

		_alpha = 0;
	}

	// Updating background sprite
	_background.set_alpha (_alpha);

	// Updating items
	std::vector<MenuItem*>::iterator it = _items.begin ();
	while (it != _items.end ())
	{
		MenuItem *item = (MenuItem*) * it;
		item -> set_alpha (_alpha);
		++it;
	}

	
}

/************************************************************************/
/* Start appear                                                         */
/************************************************************************/
void MenuState::_start_disappear ()
{
	_state = STATE_DISAPPEARING;
}