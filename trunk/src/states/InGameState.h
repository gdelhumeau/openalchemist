// **********************************************************************
//                            OpenAlchemist
//                        ---------------------
//
//  File        : InGameState.h
//  Description : 
//  Author      : Guillaume Delhumeau <guillaume.delhumeau@gmail.com>
//  License     : GNU General Public License 2 or higher
//
// **********************************************************************

#ifndef _INGAME_STATE_H_
#define _INGAME_STATE_H_

#include <ClanLib/display.h>

#include "GameState.h"
#include "../KeyboardKey.h"

class GameEngine;

/**
* InGame State - main state
*/
class InGameState : public GameState{

public:

	/** Constructor */
	InGameState();

	/** Destructor */
	~InGameState();
	
	virtual void init();

	virtual void term();
	
	virtual void load_gfx(CL_GraphicContext& gc, std::string skin);
	
	virtual void unload_gfx();

	virtual void draw(CL_GraphicContext& gc);
	
	virtual void update(CL_GraphicContext& gc);
	
	virtual void events(Window& window);

	virtual bool front_layer_behind();

};

#endif