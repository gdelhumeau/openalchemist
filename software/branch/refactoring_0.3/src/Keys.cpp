#include <ClanLib/display.h>

#include "Keys.h"

// Constructor
Keys::Keys()
{
  // We create all the usefull KeysboardKeys
  fullscreen   = new KeyboardKey(CL_KEY_F11   , false);
  retry        = new KeyboardKey(CL_KEY_F2    , false);
//  change_angle = new KeyboardKey(CL_KEY_UP    , true );
  left         = new KeyboardKey(CL_KEY_LEFT  , true );
  right        = new KeyboardKey(CL_KEY_RIGHT , true );
//  falling      = new KeyboardKey(CL_KEY_DOWN  , false);
  undo         = new KeyboardKey(CL_KEY_F5    , false);
  echap        = new KeyboardKey(CL_KEY_ESCAPE, false);
  pause        = new KeyboardKey(CL_KEY_PAUSE , false);
  up           = new KeyboardKey(CL_KEY_UP    , true );
  down         = new KeyboardKey(CL_KEY_DOWN  , true );
  enter        = new KeyboardKey(CL_KEY_ENTER , false);
//  options      = new KeyboardKey(CL_KEY_F3    , false);
  skins        = new KeyboardKey(CL_KEY_F9    , false);
  
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
  delete echap;
  delete pause;
  delete up;
  delete down;
  delete enter;
  delete skins;
}
