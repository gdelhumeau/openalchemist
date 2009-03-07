/********************************************************************
                          OpenAlchemist

  File : OptionsMenuState.h
  Description : 
  License : GNU General Public License 2 or +
  Author : Guillaume Delhumeau <guillaume.delhumeau@gmail.com>


*********************************************************************/

#ifndef _OPTIONSMENU_STATE_H_
#define _OPTIONSMENU_STATE_H_

#include <ClanLib/display.h>

#include "GameState.h"
#include "../KeyboardKey.h"

#define OPTIONS_NUMBER_OF_ITEMS 5

class GameEngine;

/**
 * OptionsMenu State
 */
class OptionsMenuState : public GameState{

  private:
  int _step;

  float _alpha;

  CL_Sprite *_items_p[OPTIONS_NUMBER_OF_ITEMS];
  CL_Sprite *_items_selected_p[OPTIONS_NUMBER_OF_ITEMS];
  int _items_left[OPTIONS_NUMBER_OF_ITEMS];
  int _items_top [OPTIONS_NUMBER_OF_ITEMS];
  int _sound_level_left;

  CL_Sprite *_p_background;  
  CL_Sprite *_sound_level_sprites_p[11];

  int _sound_level;
  int _music_level;

  int _selection;

  void _appear();
  void _disappear();

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

  OptionsMenuState();
  ~OptionsMenuState();


};

#endif
