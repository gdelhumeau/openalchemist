/********************************************************************
                          OpenAlchemist

  File : CommonState.h
  Description : 
  License : GNU General Public License 2 or +
  Author : Guillaume Delhumeau <guillaume.delhumeau@gmail.com>


*********************************************************************/

#ifndef _COMMON_STATE_H_
#define _COMMON_STATE_H_

//#include <ClanLib/display.h>
#include <SDL/SDL.h>

#include "GameState.h"
#include "../KeyboardKey.h"

class GameEngine;


/**
 * Common State
 */
class CommonState : public GameState{

  private:
  SDL_Surface *background;

  public:
  void init();
  void deinit();
  void load_gfx(std::string skin);
  void unload_gfx();
  void draw();
  void update();
  void events();

  bool front_layer_behind();
  void print();
  CommonState();
  ~CommonState();


};

#endif
