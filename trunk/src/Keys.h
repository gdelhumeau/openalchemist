// **********************************************************************
//                            OpenAlchemist
//                        ---------------------
//
//  File        : Keys.h
//  Description : 
//  Author      : Guillaume Delhumeau <guillaume.delhumeau@gmail.com>
//  License     : GNU General Public License 2 or higher
//
// **********************************************************************

#ifndef _KEYS_H_
#define _KEYS_H_

#include "KeyboardKey.h"

/** Most common keys */
class Keys{

public:
	KeyboardKey * fullscreen;
	KeyboardKey * left;
	KeyboardKey * right;
	KeyboardKey * retry;
	KeyboardKey * undo;
	KeyboardKey * escape;
	KeyboardKey * pause;
	KeyboardKey * up;
	KeyboardKey * down;
	KeyboardKey * enter;
	KeyboardKey * options;
	KeyboardKey * skins;

	/** Constructor */
	Keys();

	/** Destructor */
	~Keys();


};

#endif
