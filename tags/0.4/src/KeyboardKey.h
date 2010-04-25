// **********************************************************************
//                            OpenAlchemist
//                        ---------------------
//
//  File        : KeyboardKey.h
//  Description : 
//  Author      : Guillaume Delhumeau <guillaume.delhumeau@gmail.com>
//  License     : GNU General Public License 2 or higher
//
// **********************************************************************

#ifndef _KEYBOARDKEY_H_
#define _KEYBOARDKEY_H_

#include <ClanLib/core.h>

/**
* Class for keyboard key
*/
class KeyboardKey
{

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
	bool get(CL_InputContext& ic)
	{
		CL_InputDevice& keyboard = ic.get_keyboard();
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

private:
	
	/** Key code */
	int _key;

	/** Is the key pushed */
	bool _is_key_active;

	/** Is repeat enable */
	bool _should_repeat;

	/** Next repeat moment */
	unsigned long int _next_time;

};

#endif
