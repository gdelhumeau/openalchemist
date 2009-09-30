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
	int _key;
	bool _is_key_active;

	bool _should_repeat;
	unsigned long int _next_time;

public:
	/**
	* Constructor
	*/
	KeyboardKey(int key, bool repeat = false)
	{
		this->_key = key;
		this->_should_repeat = repeat;
		_is_key_active = true;
		_next_time = 0;
	}

	/**
	* Return if the key is activated 
	*/
	bool get(CL_DisplayWindow & window)
	{
		CL_InputDevice &keyboard = window.get_ic().get_keyboard();
		if(keyboard.get_keycode(_key))
		{
			if(!_is_key_active || (_should_repeat && CL_System::get_time()>_next_time))
			{
				_is_key_active = true;
				_next_time = CL_System::get_time()+380;
				return true;
			}
		}
		else
		{
			_is_key_active = false;
		}
		return false;
	}

};

#endif
