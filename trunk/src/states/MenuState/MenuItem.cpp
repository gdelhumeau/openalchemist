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

/************************************************************************/
/* Constructor                                                          */
/************************************************************************/
MenuItem::MenuItem()
{
	_is_selected = false;
	_is_locked = false;
	_alpha = 1.0f;
}

/************************************************************************/
/* Set X                                                                */
/************************************************************************/
void MenuItem::set_x(int x)
{
	_x = x;
}

/************************************************************************/
/* Set Y                                                                */
/************************************************************************/
void MenuItem::set_y(int y)
{
	_y = y;
}

/************************************************************************/
/* Set alpha                                                            */
/************************************************************************/
void MenuItem::set_alpha(double alpha)
{
	_alpha = alpha;
}

/************************************************************************/
/* Set selected                                                         */
/************************************************************************/
void MenuItem::set_selected(bool selected)
{
	_is_selected = selected;
}

/************************************************************************/
/* Set locked                                                           */
/************************************************************************/
void MenuItem::set_locked(bool locked)
{
	_is_locked = locked;
}