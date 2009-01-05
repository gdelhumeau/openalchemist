/********************************************************************
                          OpenAlchemist

  File : MenuState.h
  Description : 
  License : GNU General Public License 2 or +
  Author : Guillaume Delhumeau <guillaume.delhumeau@gmail.com>


*********************************************************************/

#ifndef _MENU_STATE_H_
#define _MENU_STATE_H_

#include <ClanLib/display.h>

#include "GameState.h"
#include "../KeyboardKey.h"
#include "MenuState/MenuItem.h"


class GameEngine;

/**
 * Menu State
 */
class MenuState : public GameState{

  protected:

  int step;
  double alpha;
  std::vector<MenuItem*> items;
  CL_Sprite *background;  
  int selection;
  
  void set_background_sprite(CL_Sprite *background);
  
  void appear();
  void disappear();

  public:
  virtual void init();
  virtual void deinit();
  virtual void load_gfx(std::string skin);
  virtual void unload_gfx();
  virtual void action_performed(int selection);
  void draw();
  void update();
  void events();

  void start();

  bool front_layer_behind();

  MenuState();


};

#endif
