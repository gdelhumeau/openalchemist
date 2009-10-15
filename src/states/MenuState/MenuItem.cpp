// **********************************************************************
//                            OpenAlchemist
//                        ---------------------
//
//  File        : MenuItem.cpp
//  Description : 
//  Author      : Guillaume Delhumeau <guillaume.delhumeau@gmail.com>
//  License     : GNU General Public License 2 or higher
//
// **********************************************************************

#include <iostream>
#include "MenuItem.h"
#include "../../memory.h"


MenuItem::MenuItem()
{
	_selected = false;
	_locked = false;
	_alpha = 1.0f;
}

void MenuItem::set_x(int x)
{
	_x = x;
}

void MenuItem::set_y(int y)
{
	_y = y;
}

void MenuItem::set_alpha(double alpha)
{
	_alpha = alpha;
}

void MenuItem::set_selected(bool selected)
{
	_selected = selected;
}

void MenuItem::set_locked(bool locked)
{
	_locked = locked;
}