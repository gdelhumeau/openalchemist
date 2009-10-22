// **********************************************************************
//                            OpenAlchemist
//                        ---------------------
//
//  File        : FrontLayer.h
//  Description : 
//  Author      : Guillaume Delhumeau <guillaume.delhumeau@gmail.com>
//  License     : GNU General Public License 2 or higher
//
// **********************************************************************

#ifndef _FRONTLAYER_H_
#define _FRONTLAYER_H_

#include "memory.h"
#include <ClanLib/core.h>
#include <ClanLib/display.h>

/** 
* A front layer sprite element
*/
struct FrontLayerSprite{

public:

	/** 
	* Sprite
	*/
	CL_Sprite _sprite;

	/** 
	* Coords
	*/
	int left, top;

};

/** 
* Front layer are sprites displayed in front of the body
*/
class FrontLayer{

public:

	/** 
	* Is front layer enabled
	*/
	bool is_enabled;

	/** 
	* List of sprites to display
	*/
	std::list<FrontLayerSprite*> list;

	/** 
	* Load GFX
	*/
	void load_gfx(CL_GraphicContext & gc, std::string skin);

	/** 
	* Unload GFX
	*/
	void unload_gfx();

	/** 
	* Draw
	*/
	void draw(CL_GraphicContext & gc);

private:

	/** 
	* Load GFX
	*/
	void _load_gfx(CL_GraphicContext & gc, CL_ResourceManager *p_gfx_frontlayer);

};

#endif
