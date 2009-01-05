/********************************************************************
                          OpenAlchemist

  File : MenuState.cpp
  Description : 
  License : GNU General Public License 2 or +
  Author : Guillaume Delhumeau <guillaume.delhumeau@gmail.com>


*********************************************************************/


#include "MenuState.h"

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

void MenuState::draw()
{
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
}

void MenuState::events()
{
}

void MenuState::start()
{
}