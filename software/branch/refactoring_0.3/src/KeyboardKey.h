/********************************************************************
                          OpenAlchemist

  File : KeyboardKey.h
  Description : 
  License : GNU General Public License 2 or +
  Author : Guillaume Delhumeau <guillaume.delhumeau@gmail.com>


*********************************************************************/


#ifndef _KEYBOARDKEY_H_
#define _KEYBOARDKEY_H_

#include <ClanLib/core.h>

/**
 * Class for keyboard key
 */
class KeyboardKey
{
private:
  int key;
  bool key_active;

  bool repeat;
  unsigned long int next_time;

public:
  /**
   * Constructor
   */
  KeyboardKey(int key, bool repeat = false)
  {
    this->key = key;
    this->repeat = repeat;
    key_active = false;
    next_time = 0;
  }
  
  /**
   * Return if the key is activated 
   */
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
