/********************************************************************
                          OpenAlchemist

  File : KeyboardKey.h
  Description : 
  License : GNU General Public License 2 or +
  Author : Guillaume Delhumeau <guillaume.delhumeau@gmail.com>


*********************************************************************/


#ifndef _KEYBOARDKEY_H_
#define _KEYBOARDKEY_H_

//#include <ClanLib/core.h>
#include <pspctrl.h>
#include <SDL/SDL.h>


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
    key_active = true;
    next_time = 0;
  }

  /**
   * Return true if the key is activated 
   */

bool get()
{

	return this->key;
#if 0
int keyPressed = 0;
#ifndef LINUX_MODE
    SceCtrlData pad;
    sceCtrlPeekBufferPositive(&pad, 1);
    keyPressed = pad.Buttons;
#else
    SDL_Event event;
    SDL_PollEvent(&event);
    if (event.type == SDL_KEYDOWN)
        keyPressed = event.key.keysym.sym;
#endif
//   printf("-----------------------------\n");
//   printf("got this : %d\n",keyPressed);
//   printf("was checking for this : %d\n", key);
   if(keyPressed == key)
   {
	printf("well that's ok\n");
        if(!key_active || (repeat && SDL_GetTicks()))
        {
          key_active = true;
          next_time = SDL_GetTicks()+380;
          return true;
        }
    }
    else
    {
      key_active = false;
    }
    return false;
#endif
}

};

#endif
