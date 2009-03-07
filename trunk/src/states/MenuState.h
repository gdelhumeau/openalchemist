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

  int _step;
  double _alpha;
  std::vector<MenuItem*> _items;
  CL_Sprite *_background;  
  int _selection;
  
  void _set_background_sprite(CL_Sprite *background);
  
  void _appear();
  void _disappear();
  
  void _start_disappear();

  public:
  virtual void init();
  virtual void deinit();
  virtual void load_gfx(std::string skin);
  virtual void unload_gfx();
  virtual void action_performed(int selection, int action_type);
  virtual void update_child();
  
  void draw();
  void update();
  void events();

  void start();

  bool front_layer_behind();

  MenuState();


};

#endif
