/********************************************************************
                          OpenAlchemist

  File : CommonState.h
  Description : 
  License : GNU General Public License 2 or +
  Author : Guillaume Delhumeau <guillaume.delhumeau@gmail.com>


*********************************************************************/

#ifndef _COMMON_STATE_H_
#define _COMMON_STATE_H_

#include <ClanLib/display.h>

#include "GameState.h"
#include "../KeyboardKey.h"

class GameEngine;


/**
 * Common State
 */
class CommonState : public GameState{

  private:
  GameEngine *engine;
  CL_Surface * background;
  CL_Font *main_font;

  KeyboardKey *key_fullscreen;

  public:
  void init();
  void deinit();
  void load_gfx(std::string skin);
  void unload_gfx();
  void draw();
  void update();
  void events();

  CommonState(GameEngine* engine);
  ~CommonState();


};

#endif
