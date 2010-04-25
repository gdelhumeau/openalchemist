// **********************************************************************
//                            OpenAlchemist
//                        ---------------------
//
//  File        : CommonState.h
//  Description : 
//  Author      : Guillaume Delhumeau <guillaume.delhumeau@gmail.com>
//  License     : GNU General Public License 2 or higher
//
// **********************************************************************

#ifndef _COMMON_STATE_H_
#define _COMMON_STATE_H_

#include <ClanLib/display.h>

#include "GameState.h"
#include "../KeyboardKey.h"

class GameEngine;

/**
* Common State - the state which is always active.
*/
class CommonState : public GameState{

public:

	/** Constructor */
	CommonState();

	/** Destructor */
	~CommonState();

	virtual void init();

	virtual void term();

	virtual void load_gfx(CL_GraphicContext& gc, std::string skin);

	virtual void unload_gfx();

	virtual void draw(CL_GraphicContext& gc);
	
	virtual void update(CL_GraphicContext& gc);
	
	virtual void events(Window& window);

	virtual bool front_layer_behind();

private:

	/** Background image */
	CL_Image _background;

	/** Enable Framerate drawing */
	bool _enable_framerate_drawing;

};

#endif