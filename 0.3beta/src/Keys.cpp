//#include <ClanLib/display.h>

#include "Keys.h"

// Constructor
Keys::Keys()
{
#ifndef LINUX_MODE
  // We create all the usefull KeysboardKeys
  fullscreen   = new KeyboardKey(0 , false);
  retry        = new KeyboardKey(PSP_CTRL_TRIANGLE , false);
//  change_angle = new KeyboardKey(CL_KEY_UP    , true );
  left         = new KeyboardKey(PSP_CTRL_LEFT  , true );
  right        = new KeyboardKey(PSP_CTRL_RIGHT, true );
//  falling      = new KeyboardKey(CL_KEY_DOWN  , false);
  undo         = new KeyboardKey(PSP_CTRL_CIRCLE    , false);
  escape       = new KeyboardKey(PSP_CTRL_START, false);
  pause        = new KeyboardKey(PSP_CTRL_SELECT , false);
  up           = new KeyboardKey(PSP_CTRL_UP    , true );
  down         = new KeyboardKey(PSP_CTRL_DOWN  , true );
  enter        = new KeyboardKey(PSP_CTRL_CROSS , false);
  options      = new KeyboardKey(PSP_CTRL_LTRIGGER    , false);
  skins        = new KeyboardKey(PSP_CTRL_RTRIGGER   , false);
#else
   // We create all the usefull KeysboardKeys
  fullscreen   = new KeyboardKey(KEY_FULLSCREEN   , false);
  retry        = new KeyboardKey(KEY_RETRY    , false);
//  change_angle = new KeyboardKey(CL_KEY_UP    , true );
  left         = new KeyboardKey(KEY_LEFT  , true );
  right        = new KeyboardKey(KEY_RIGHT , true );
//  falling      = new KeyboardKey(CL_KEY_DOWN  , false);
  undo         = new KeyboardKey(KEY_UNDO    , false);
  escape       = new KeyboardKey(KEY_ESCAPE, false);
  pause        = new KeyboardKey(KEY_PAUSE , false);
  up           = new KeyboardKey(KEY_UP    , true );
  down         = new KeyboardKey(KEY_DOWN  , true );
  enter        = new KeyboardKey(KEY_ENTER , false);
  options      = new KeyboardKey(KEY_OPTIONS    , false);
  skins        = new KeyboardKey(KEY_SKINS   , false);
#endif
  
}

// Destructor
Keys::~Keys()
{
  delete fullscreen;
  delete retry;
//  delete change_angle;
  delete left;
  delete right; 
//  delete falling; 
  delete undo;
  delete escape;
  delete pause;
  delete up;
  delete down;
  delete enter;
  delete options;
  delete skins;
}
