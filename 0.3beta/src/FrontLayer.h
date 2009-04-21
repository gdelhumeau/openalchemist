/********************************************************************
                          OpenAlchemist

  File : FrontLayer.h
  Description : 
  License : GNU General Public License 2 or +
  Author : Guillaume Delhumeau <guillaume.delhumeau@gmail.com>


*********************************************************************/

#ifndef _FRONTLAYER_H_
#define _FRONTLAYER_H_

//#include <ClanLib/core.h>
//#include <ClanLib/display.h>
#include <list>
#include <SDL/SDL.h>
#include <string>

class FrontLayerSprite{

  public:
  SDL_Surface *sprite;
  u_int left, top;

  FrontLayerSprite();

};


class FrontLayer{

  private:
  void load_gfx(FILE * front_layer_ini, std::string skin);


  public:
  bool enabled;

  std::list<FrontLayerSprite*> list;
  void load_gfx(std::string skin);
  void unload_gfx();
  void draw();

};

#endif
