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

  public:
  void init();
  void deinit();
  void load_gfx(CL_GraphicContext &gc, std::string skin);
  void unload_gfx();
  void draw(CL_GraphicContext &gc);
  void update(CL_GraphicContext &gc);
  void events(CL_DisplayWindow & window);

  bool front_layer_behind();

  InGameState();
  ~InGameState();


};

#endif
