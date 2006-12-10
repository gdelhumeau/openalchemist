/* OpenAlchemist - just a simple game 
 * ----------------------------------
 *
 * Copyright (C) 2005, 2006 Guillaume Delhumeau <guillaume.delhumeau at laposte.net>
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.
 */

#include "headers.h"

// Constructor
Key::Key()
{
  // We create all the usefull KeyboardKeys
  fullscreen   = new KeyboardKey(CL_KEY_F11   , false);
  retry        = new KeyboardKey(CL_KEY_F2    , false);
  change_angle = new KeyboardKey(CL_KEY_UP    , true );
  left         = new KeyboardKey(CL_KEY_LEFT  , true );
  right        = new KeyboardKey(CL_KEY_RIGHT , true );
  falling      = new KeyboardKey(CL_KEY_DOWN  , false);
  undo         = new KeyboardKey(CL_KEY_F5    , false);
  echap        = new KeyboardKey(CL_KEY_ESCAPE, false);
  up           = new KeyboardKey(CL_KEY_UP    , true );
  down         = new KeyboardKey(CL_KEY_DOWN  , true );
  enter        = new KeyboardKey(CL_KEY_ENTER , false);
  options      = new KeyboardKey(CL_KEY_F3    , false);
  
}

// Destructor
Key::~Key()
{
  delete fullscreen;
  delete retry;
  delete change_angle;
  delete left;
  delete right; 
  delete falling; 
  delete undo;
  delete echap;
  delete up;
  delete down;
  delete enter;
}
