/********************************************************************
                          OpenAlchemist

  File : FrontLayer.h
  Description : 
  License : GNU General Public License 2 or +
  Author : Guillaume Delhumeau <guillaume.delhumeau@gmail.com>


*********************************************************************/

#ifndef _FRONTLAYER_H_
#define _FRONTLAYER_H_

#include <ClanLib/core.h>
#include <ClanLib/display.h>

class FrontLayerSprite{

  public:
  CL_Sprite *p_sprite;
  u_int left, top;

};


class FrontLayer{

  private:
  void _load_gfx(CL_ResourceManager *p_gfx_frontlayer);


  public:
  bool is_enabled;
  
  std::list<FrontLayerSprite*> list;
  void load_gfx(std::string skin);
  void unload_gfx();
  void draw();

};

#endif
