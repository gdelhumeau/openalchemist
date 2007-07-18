/********************************************************************
                          OpenAlchemist

  File : GameOverState.h
  Description : 
  License : GNU General Public License 2 or +
  Author : Guillaume Delhumeau <guillaume.delhumeau@gmail.com>


*********************************************************************/

#ifndef _GAMEOVER_STATE_H_
#define _GAMEOVER_STATE_H_

#include <ClanLib/display.h>

#include "GameState.h"
#include "../KeyboardKey.h"

class GameEngine;


/**
 * InGame State
 */
class GameOverState : public GameState{

  private:

  CL_Surface * panel;
  int panel_x, panel_y;

  public:
  void init();
  void deinit();
  void load_gfx(std::string skin);
  void unload_gfx();
  void draw();
  void update();
  void events();

  GameOverState();
  ~GameOverState();


};

#endif
