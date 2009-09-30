/********************************************************************
                          OpenAlchemist
 
  File : MenuState.cpp
  Description : 
  License : GNU General Public License 2 or +
  Author : Guillaume Delhumeau <guillaume.delhumeau@gmail.com>
 
 
 *********************************************************************/

#include "../memory.h"
#include "MenuState.h"
#include "../CommonResources.h"
#include "../GameEngine.h"

enum{
	STEP_APPEARING,
	STEP_NORMAL,
	STEP_DISAPPEARING
};

static const float APPEARING_SPEED = 0.003;

MenuState::MenuState ()
{
	_selection = 0;
}

bool MenuState::front_layer_behind ()
{
	return true;
}

void MenuState::_set_background_sprite (CL_Sprite & background)
{
	this -> _background = background;
}

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

void MenuState::update (CL_GraphicContext & gc)
{
	switch (_step)
	{
	case STEP_APPEARING:
		_appear ();
		break;
	case STEP_DISAPPEARING:
		_disappear ();
		break;
	}
	this -> update_child ();
}

void MenuState::events (CL_DisplayWindow & window)
{
	// Leaving the state
	if (_p_common_resources -> key.escape->get (window) || _p_common_resources -> key.pause->get (window))
	{
		_start_disappear ();
		_selection = -1;
	}

	// Key ENTER
	if (_p_common_resources -> key.enter -> get (window))
	{
		if(_items[_selection] -> quit_menu_on_action())
		{
			_start_disappear ();
		}
		_items[_selection] -> action_performed(ACTION_TYPE_ENTER);
	}

	// Key LEFT
	if (_p_common_resources -> key.left -> get (window))
	{
		_items[_selection] -> action_performed(ACTION_TYPE_LEFT);
		this -> action_performed (_selection, ACTION_TYPE_LEFT);
	}

	// Key RIGHT
	if (_p_common_resources -> key.right -> get (window))
	{
		_items[_selection] -> action_performed(ACTION_TYPE_RIGHT);
		this -> action_performed (_selection, ACTION_TYPE_RIGHT);
	}


	// Key UP
	if (_p_common_resources -> key.up -> get (window))
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
	}

	// Key DOWN
	if (_p_common_resources -> key.down -> get (window))
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
	}

}

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

	// Now, begining appearing
	if (_p_common_resources -> p_engine -> is_opengl_used ())
	{
		_step = STEP_APPEARING;
		_alpha = 0.0;
	}
	else
	{
		_step = STEP_NORMAL;
	}
}

void MenuState::_appear ()
{
	// Updating alpha value
	if (_alpha + APPEARING_SPEED * _p_common_resources -> time_interval >= 1.0)
	{
		_step = STEP_NORMAL;
		_alpha = 1.0;
	}
	else
	{
		_alpha += APPEARING_SPEED * _p_common_resources -> time_interval;
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

void MenuState::_disappear ()
{
	// Updating alpha value
	_alpha -= APPEARING_SPEED * _p_common_resources -> time_interval;

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

	if (_alpha <= 0)
	{
		// Now perfom child action or leaving the state
		if (_selection == -1)
			_p_common_resources -> p_engine -> stop_current_state ();
		else
			this -> action_performed (_selection, ACTION_TYPE_ENTER);
	}
}

void MenuState::_start_disappear ()
{
	_step = STEP_DISAPPEARING;
}

