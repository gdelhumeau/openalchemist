/********************************************************************
                          OpenAlchemist

  File : CommonResources.h
  Description : 
  License : GNU General Public License 2 or +
  Author : Guillaume Delhumeau <guillaume.delhumeau@gmail.com>


*********************************************************************/

#ifndef _COMMON_RESOURCES_H_
#define _COMMON_RESOURCES_H_

#include <ClanLib/display.h>

#include "Board.h"
#include "Player.h"

class GameEngine;

class CommonResources{

  public:
  GameEngine *engine;
  CL_Font *main_font;

  int score;

  Player player1;

  /** Sprites */
  int pieces_width, pieces_height;

  float time_interval;
  int fps;


  void init(GameEngine *engine);
  void load_gfx(std::string skin);
  void unload_gfx();

  CommonResources();
  ~CommonResources();

};

CommonResources* common_resources_get_instance();

#endif
