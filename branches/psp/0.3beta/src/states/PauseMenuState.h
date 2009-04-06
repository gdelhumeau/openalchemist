/********************************************************************
                          OpenAlchemist

  File : PauseMenuState.h
  Description : 
  License : GNU General Public License 2 or +
  Author : Guillaume Delhumeau <guillaume.delhumeau@gmail.com>


*********************************************************************/

#ifndef _PAUSEMENU_STATE_H_
#define _PAUSEMENU_STATE_H_

//#include <ClanLib/display.h>

#include "GameState.h"
#include "../KeyboardKey.h"

#define PAUSE_NUMBER_OF_ITEMS 6

class GameEngine;

/**
 * PauseMenu State
 */
class PauseMenuState : public GameState{

  private:
  int step;

  int alpha;

  SDL_Surface *items[PAUSE_NUMBER_OF_ITEMS];
  SDL_Surface *items_selected[PAUSE_NUMBER_OF_ITEMS];
  int items_left[PAUSE_NUMBER_OF_ITEMS];
  int items_top [PAUSE_NUMBER_OF_ITEMS];

  SDL_Surface *background;  
  SDL_Surface *undo_unavailable;

  int selection;

  void appear();
  void disappear();

  public:
  void init();
  void deinit();
  void load_gfx(std::string skin);
  void unload_gfx();
  void draw();
  void update();
  void events();

  void start();

  bool front_layer_behind();

  void print();

  PauseMenuState();
  ~PauseMenuState();


};

#endif
