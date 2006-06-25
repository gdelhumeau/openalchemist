/* OpenAlchemist - just a simple game 
 * ----------------------------------
 *
 * Copyright (C) 2005 Guillaume Delhumeau <guillaume.delhumeau at laposte.net>
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
#ifndef _KEYBOARDKEY_H_
#define _KEYBOARDKEY_H_

#include <ClanLib/core.h>

class KeyboardKey
{
private:
  int key;
  bool key_active;

  bool repeat;
  unsigned long int next_time;

public:
  KeyboardKey::KeyboardKey(int key, bool repeat = false)
  {
    this->key = key;
    this->repeat = repeat;
    key_active = false;
    next_time = 0;
  }
  
  bool get()
  {
    if(CL_Keyboard::get_keycode(key))
    {
      if(!key_active || (repeat && CL_System::get_time()>next_time))
      {
        key_active = true;
        next_time = CL_System::get_time()+380;
        return true;
      }
    }
    else
    {
      key_active = false;
    }
    return false;
  }
    
};

#endif
