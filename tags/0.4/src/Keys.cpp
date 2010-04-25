// **********************************************************************
//                            OpenAlchemist
//                        ---------------------
//
//  File        : Keys.cpp
//  Description : 
//  Author      : Guillaume Delhumeau <guillaume.delhumeau@gmail.com>
//  License     : GNU General Public License 2 or higher
//
// **********************************************************************

#include <ClanLib/display.h>

#include "Keys.h"
#include "memory.h"

/************************************************************************/
/* Constructor                                                          */
/************************************************************************/
Keys::Keys():
fullscreen(CL_KEY_F11,    false),
left      (CL_KEY_LEFT,   true ),
right     (CL_KEY_RIGHT,  true ),
retry     (CL_KEY_F2,     false),
undo      (CL_KEY_F5,     false),
escape    (CL_KEY_ESCAPE, false),
pause     (CL_KEY_PAUSE,  false),
up        (CL_KEY_UP,     true ),
down      (CL_KEY_DOWN,   true ),
enter     (CL_KEY_ENTER,  false),
options   (CL_KEY_F9,     false),
skins     (CL_KEY_F10,    false),
framerate (CL_KEY_F,      false)
{

}

/************************************************************************/
/* Destructor                                                           */
/************************************************************************/
Keys::~Keys()
{
}
