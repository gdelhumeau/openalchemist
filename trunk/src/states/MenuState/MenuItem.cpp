/********************************************************************
                          OpenAlchemist

  File : MenuItem.cpp
  Description : 
  License : GNU General Public License 2 or +
  Author : Guillaume Delhumeau <guillaume.delhumeau@gmail.com>


*********************************************************************/

#include <iostream>
#include "MenuItem.h"
#include "../../memory.h"


MenuItem::MenuItem()
{
	selected = false;
	locked = false;
	alpha = 1.0f;
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