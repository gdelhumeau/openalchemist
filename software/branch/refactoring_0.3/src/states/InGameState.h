/********************************************************************
                          OpenAlchemist

  File : InGameState.h
  Description : 
  License : GNU General Public License 2 or +
  Author : Guillaume Delhumeau <guillaume.delhumeau@gmail.com>


*********************************************************************/

#ifndef _INGAME_STATE_H_
#define _INGAME_STATE_H_

#include <ClanLib/display.h>

#include "GameState.h"
#include "../KeyboardKey.h"

class GameEngine;

/**
 * InGame State
 */
class InGameState : public GameState{

  private:

  public:
  void init();
  void deinit();
  void load_gfx(std::string skin);
  void unload_gfx();
  void draw();
  void update();
  void events();

  bool front_layer_behind();

  InGameState();
  ~InGameState();


};

#endif
