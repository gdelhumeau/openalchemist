/********************************************************************
                          OpenAlchemist

  File : OptionsMenuState.h
  Description : 
  License : GNU General Public License 2 or +
  Author : Guillaume Delhumeau <guillaume.delhumeau@gmail.com>


*********************************************************************/

#ifndef _OPTIONSMENU_STATE_H_
#define _OPTIONSMENU_STATE_H_

//#include <ClanLib/display.h>
#include <SDL/SDL.h>

#include "GameState.h"
#include "../KeyboardKey.h"

#define OPTIONS_NUMBER_OF_ITEMS 5

class GameEngine;

/**
 * OptionsMenu State
 */
class OptionsMenuState : public GameState{

  private:
  int step;

  /*float*/ int alpha;

  SDL_Surface *items[OPTIONS_NUMBER_OF_ITEMS];
  SDL_Surface *items_selected[OPTIONS_NUMBER_OF_ITEMS];
  int items_left[OPTIONS_NUMBER_OF_ITEMS];
  int items_top [OPTIONS_NUMBER_OF_ITEMS];
  int sound_level_left;

  SDL_Surface *background;  
  SDL_Surface *sound_level_sprites[11];

  int sound_level;
  int music_level;

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

  OptionsMenuState();
  ~OptionsMenuState();


};

#endif
