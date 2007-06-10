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

class GameEngine;

class CommonResources{

  public:
  GameEngine *engine;
  CL_Font *main_font;

  void init(GameEngine *engine);
  void load_gfx(std::string skin);
  void unload_gfx();

  CommonResources();
  ~CommonResources();

};

CommonResources* common_resources_get_instance();

#endif
