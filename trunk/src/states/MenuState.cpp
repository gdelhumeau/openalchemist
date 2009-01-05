/********************************************************************
                          OpenAlchemist

  File : MenuState.cpp
  Description : 
  License : GNU General Public License 2 or +
  Author : Guillaume Delhumeau <guillaume.delhumeau@gmail.com>


*********************************************************************/


#include "MenuState.h"
#include "../CommonResources.h"
#include "../GameEngine.h"

#define STEP_APPEARING 0
#define STEP_NORMAL 1
#define STEP_DISAPPEARING 2

#define APPEARING_SPEED 0.003

MenuState::MenuState()
{
}

bool MenuState::front_layer_behind()
{
  return true;
}

void MenuState::init()
{
	std::cout << "MenuState class may not be used cause it is an abstract class" << std::endl;
}

void MenuState::deinit()
{
	std::cout << "MenuState class may not be used cause it is an abstract class" << std::endl;
}

void MenuState::load_gfx(std::string skin)
{
	std::cout << "MenuState class may not be used cause it is an abstract class" << std::endl;
}

void MenuState::unload_gfx()
{
	std::cout << "MenuState class may not be used cause it is an abstract class" << std::endl;
}

void MenuState::action_performed(int selection)
{
	std::cout << "MenuState class may not be used cause it is an abstract class" << std::endl;
}

void MenuState::set_background_sprite(CL_Sprite *background)
{
	this -> background = background;
}

void MenuState::draw()
{
	// Displaying background
	int x = 400 - background -> get_width()/2;
  int y = 300 - background -> get_height()/2;
  background -> draw(x,y);
	
	// Displaying items
	std::vector<MenuItem*>::iterator it = items.begin();
	while(it != items.end())
	{
		MenuItem *item = (MenuItem*) *it;
		item -> draw();		
		++it;
	}
				
}

void MenuState::update()
{
	switch(step)
  {
  case STEP_APPEARING:
    appear();
    break;
  case STEP_DISAPPEARING:
    disappear();
    break;
  }
}

void MenuState::events()
{
	// Leaving the state
	if(common_resources -> key.escape->get() || common_resources -> key.pause->get())
  {   
 	  step = STEP_DISAPPEARING;
    selection = -1;
  }
	
	// Key UP
	if(common_resources -> key.up -> get())
  {
		items[selection] -> set_selected(false);
		bool changed = false;
		while(!changed)
		{
			if(selection == 0)
			{
				selection = items.size() - 1;
			}
			else
			{
				selection --;				
			}
			
			if(!items[selection] -> is_locked())
			{
				changed = true;
				items[selection] -> set_selected(true);
			}
		}
  }

	// Key DOWN
  if(common_resources -> key.down -> get())
  {
		items[selection] -> set_selected(false);
    bool changed = false;
		while(!changed)
		{
			if(selection == (int)items.size() - 1)
			{
				selection = 0;
			}
			else
			{
				selection ++;				
			}
			
			if(!items[selection] -> is_locked())
			{
				changed = true;
				items[selection] -> set_selected(true);
			}
		}
  }
}

void MenuState::start()
{
	selection = 0;
	items[selection] -> set_selected(true);
  if(common_resources -> engine -> is_opengl_used())
  {
    step = STEP_APPEARING;
    alpha = 0.0;
  }
  else
  {
    step = STEP_NORMAL;
  }
}

void MenuState::appear()
{
	// Updating alpha value
	if(alpha + APPEARING_SPEED * common_resources -> time_interval >= 1.0)
  {
    step = STEP_NORMAL;
    alpha = 1.0;
  }
  else
	{
    alpha += APPEARING_SPEED * common_resources -> time_interval;
	}

	// Updating background sprite
  background -> set_alpha(alpha);

	// Updating items
	std::vector<MenuItem*>::iterator it = items.begin();
	while(it != items.end())
	{
		MenuItem *item = (MenuItem*) *it;
		item -> set_alpha(alpha);		
		++it;
	}	
 
}

void MenuState::disappear()
{
	// Updating alpha value
	alpha -= APPEARING_SPEED * common_resources -> time_interval;

	// Updating background sprite
  background -> set_alpha(alpha);

	// Updating items
	std::vector<MenuItem*>::iterator it = items.begin();
	while(it != items.end())
	{
		MenuItem *item = (MenuItem*) *it;
		item -> set_alpha(alpha);		
		++it;
	}
	
	// Now perfom child action or leaving the state
	if(selection == -1)
		common_resources -> engine -> stop_current_state();
	else
		this -> action_performed(selection);
}

