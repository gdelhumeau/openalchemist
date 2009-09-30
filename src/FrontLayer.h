/********************************************************************
                          OpenAlchemist

  File : FrontLayer.h
  Description : 
  License : GNU General Public License 2 or +
  Author : Guillaume Delhumeau <guillaume.delhumeau@gmail.com>


*********************************************************************/

#ifndef _FRONTLAYER_H_
#define _FRONTLAYER_H_

#include "memory.h"
#include <ClanLib/core.h>
#include <ClanLib/display.h>

struct FrontLayerSprite{

public:
	CL_Sprite _sprite;
	unsigned int left, top;

};


class FrontLayer{

private:
	void _load_gfx(CL_GraphicContext & gc, CL_ResourceManager *p_gfx_frontlayer);


public:
	bool is_enabled;

	std::list<FrontLayerSprite*> list;
	void load_gfx(CL_GraphicContext & gc, std::string skin);
	void unload_gfx();
	void draw(CL_GraphicContext & gc);

};

#endif
