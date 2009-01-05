/********************************************************************
                          OpenAlchemist

  File : MenuItem.cpp
  Description : 
  License : GNU General Public License 2 or +
  Author : Guillaume Delhumeau <guillaume.delhumeau@gmail.com>


*********************************************************************/

#include <iostream>
#include "MenuItem.h"


MenuItem::MenuItem()
{

}

void MenuItem::draw()
{
	std::cout << "MenuItem class may not be used cause it is an abstract class" << std::endl;
}

void MenuItem::events()
{
	std::cout << "MenuItem class may not be used cause it is an abstract class" << std::endl;
}

void MenuItem::set_x(int x)
{
	this -> x = x;
}

void MenuItem::set_y(int y)
{
	this -> y = y;
}

void MenuItem::set_alpha(double alpha)
{
	this -> alpha = alpha;
}

void MenuItem::set_selected(bool selected)
{
	this -> selected = selected;
}

void MenuItem::set_locked(bool locked)
{
	this -> locked = locked;
}