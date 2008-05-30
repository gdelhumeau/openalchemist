/********************************************************************
                          OpenAlchemist

  File : QuitMenuSate.h
  Description : 
  License : GNU General Public License 2 or +
  Author : Guillaume Delhumeau <guillaume.delhumeau@gmail.com>


*********************************************************************/

#ifndef _QUITMENU_STATE_H_
#define _QUITMENU_STATE_H_

#include <ClanLib/display.h>

#include "GameState.h"
#include "../KeyboardKey.h"

class GameEngine;


/**
 * InGame State
 */
class QuitMenuState : public GameState{

  private:

  CL_Sprite * panel;
  int panel_x, panel_y;

  CL_Sprite * yes_selected, * yes_unselected;
  CL_Sprite * no_selected,  * no_unselected;
  int yes_x, yes_y;
  int no_x, no_y;
  int selection;

  public:
  void init();
  void deinit();
  void load_gfx(std::string skin);
  void unload_gfx();
  void draw();
  void update();
  void events();
  
  bool front_layer_behind();

  QuitMenuState();
  ~QuitMenuState();


};

#endif
