/********************************************************************
                          OpenAlchemist

  File : GameState.h
  Description : describe the generic GameState
  License : GNU General Public License 2 or +
  Author : Guillaume Delhumeau <guillaume.delhumeau@gmail.com>


*********************************************************************/

#ifndef _GAME_STATE_H_
#define _GAME_STATE_H_

#include <string>

class CommonResources;

/**
 * Generic (Abstract) State Class 
 */
class GameState{

  protected:
  CommonResources *common_resources;

  public:
  virtual void init();
  virtual void deinit();
  virtual void load_gfx(std::string skin);
  virtual void unload_gfx();
  virtual void draw();
  virtual void update();
  virtual void events();

  virtual bool front_layer_behind();

  GameState();
  virtual ~GameState();


};

#endif
