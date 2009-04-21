#ifndef _KEYS_H_
#define _KEYS_H_

#include "KeyboardKey.h"
#include <pspctrl.h>
#include <SDL/SDL.h>

#ifndef LINUX_MODE
#define KEY_FULLSCREEN     0 
#define KEY_RETRY          PSP_CTRL_TRIANGLE 
#define KEY_LEFT           PSP_CTRL_LEFT  
#define KEY_RIGHT          PSP_CTRL_RIGHT
#define KEY_UNDO           PSP_CTRL_CIRCLE    
#define KEY_ESCAPE         PSP_CTRL_START
#define KEY_PAUSE          PSP_CTRL_SELECT 
#define KEY_UP             PSP_CTRL_UP    
#define KEY_DOWN           PSP_CTRL_DOWN  
#define KEY_ENTER          PSP_CTRL_CROSS 
#define KEY_OPTIONS        PSP_CTRL_LTRIGGER    
#define KEY_SKINS          PSP_CTRL_RTRIGGER   
#define KEY_CHEAT	   PSP_CTRL_SQUARE | PSP_CTRL_RTRIGGER | PSP_CTRL_LTRIGGER
#define KEY_CHANGE_ANGLE   PSP_CTRL_CROSS

#else
#define KEY_FULLSCREEN     SDLK_F11
#define KEY_RETRY          SDLK_F2
#define KEY_LEFT           SDLK_LEFT
#define KEY_RIGHT          SDLK_RIGHT
#define KEY_UNDO           SDLK_F5
#define KEY_ESCAPE         SDLK_ESCAPE
#define KEY_PAUSE          SDLK_SPACE
#define KEY_UP             SDLK_UP
#define KEY_DOWN           SDLK_DOWN
#define KEY_ENTER          SDLK_RETURN
#define KEY_OPTIONS        SDLK_F9
#define KEY_SKINS          SDLK_F10
#define KEY_CHEAT	   SDLK_a
#define KEY_CHANGE_ANGLE   SDLK_p
#endif


#define KEY_FALL	   KEY_DOWN


class Keys{

  public:
  KeyboardKey * fullscreen;
//  KeyboardKey * change_angle;
  KeyboardKey * left;
  KeyboardKey * right;
//  KeyboardKey * falling;
  KeyboardKey * retry;
  KeyboardKey * undo;
  KeyboardKey * escape;
  KeyboardKey * pause;
  KeyboardKey * up;
  KeyboardKey * down;
  KeyboardKey * enter;
  KeyboardKey * options;
  KeyboardKey * skins;

  // Constructor
  Keys();

  // Destructor
  ~Keys();


};

#endif
