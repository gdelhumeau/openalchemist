#ifndef _KEYS_H_
#define _KEYS_H_

#include "KeyboardKey.h"

class Keys{

  public:
  KeyboardKey * fullscreen;
//  KeyboardKey * change_angle;
  KeyboardKey * left;
  KeyboardKey * right;
//  KeyboardKey * falling;
  KeyboardKey * retry;
  KeyboardKey * undo;
  KeyboardKey * echap;
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
