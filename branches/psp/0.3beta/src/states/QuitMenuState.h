/********************************************************************
                          OpenAlchemist

  File : QuitMenuSate.h
  Description : 
  License : GNU General Public License 2 or +
  Author : Guillaume Delhumeau <guillaume.delhumeau@gmail.com>


*********************************************************************/

#ifndef _QUITMENU_STATE_H_
#define _QUITMENU_STATE_H_

//#include <ClanLib/display.h>

#include <SDL/SDL.h>

#include "GameState.h"
#include "../KeyboardKey.h"

#define QUITMENU_GIVE_UP 1
#define QUITMENU_RETRY 2
#define QUITMENU_EXIT 3


class GameEngine;


/**
 * QuitMenuGame State
 */
class QuitMenuState : public GameState{

  private:

  SDL_Surface * panel_give_up, *panel_retry, *panel_exit;
  SDL_Surface * current_panel;
  int panel_x, panel_y;

  SDL_Surface * yes_selected, * yes_unselected;
  SDL_Surface * no_selected,  * no_unselected;
  int yes_x, yes_y;
  int no_x, no_y;
  int selection;

  int action;
  int step;

  /*double*/ Uint8 alpha;

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

  void set_action(int a);
  void start();

  void print();

  private:
  void appear();
  void disappear();


};

#endif
