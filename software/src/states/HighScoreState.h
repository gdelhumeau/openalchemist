/********************************************************************
                          OpenAlchemist

  File : HighScoreState.h
  Description : 
  License : GNU General Public License 2 or +
  Author : Guillaume Delhumeau <guillaume.delhumeau@gmail.com>


*********************************************************************/

#ifndef _HIGHSCORE_STATE_H_
#define _HIGHSCORE_STATE_H_

#include <ClanLib/display.h>

#include "GameState.h"
#include "../KeyboardKey.h"

class GameEngine;


/**
 * InGame State
 */
class HighScoreState : public GameState{

  private:

  CL_Sprite * panel;
  int panel_x, panel_y;
  int new_score_x;
  int new_score_y;
  int old_score_x;
  int old_score_y;

  public:
  void init();
  void deinit();
  void load_gfx(std::string skin);
  void unload_gfx();
  void draw();
  void update();
  void events();
  
  bool front_layer_behind();

  HighScoreState();
  ~HighScoreState();


};

#endif
