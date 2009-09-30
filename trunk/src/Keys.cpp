#include <ClanLib/display.h>

#include "Keys.h"
#include "memory.h"

// Constructor
Keys::Keys()
{
	// We create all the usefull KeysboardKeys
	fullscreen   = my_new KeyboardKey(CL_KEY_F11   , false);
	retry        = my_new KeyboardKey(CL_KEY_F2    , false);
	//  change_angle = my_new KeyboardKey(CL_KEY_UP    , true );
	left         = my_new KeyboardKey(CL_KEY_LEFT  , true );
	right        = my_new KeyboardKey(CL_KEY_RIGHT , true );
	//  falling      = my_new KeyboardKey(CL_KEY_DOWN  , false);
	undo         = my_new KeyboardKey(CL_KEY_F5    , false);
	escape       = my_new KeyboardKey(CL_KEY_ESCAPE, false);
	pause        = my_new KeyboardKey(CL_KEY_PAUSE , false);
	up           = my_new KeyboardKey(CL_KEY_UP    , true );
	down         = my_new KeyboardKey(CL_KEY_DOWN  , true );
	enter        = my_new KeyboardKey(CL_KEY_ENTER , false);
	options      = my_new KeyboardKey(CL_KEY_F9    , false);
	skins        = my_new KeyboardKey(CL_KEY_F10   , false);

}

// Destructor
Keys::~Keys()
{
	my_delete( fullscreen );
	my_delete( retry );
	my_delete( left );
	my_delete( right ); 
	my_delete( undo );
	my_delete( escape );
	my_delete( pause );
	my_delete( up );
	my_delete( down );
	my_delete( enter );
	my_delete( options );
	my_delete( skins );
}
