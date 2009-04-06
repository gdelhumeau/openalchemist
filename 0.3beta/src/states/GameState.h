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
  /**
   * Initializing the state
   */
  virtual void init();

  /**
   * Deleting the initialized values
   */
  virtual void deinit();

  /**
   * Loading GFX
   */
  virtual void load_gfx(std::string skin);

  /**
   * Unloading GFX
   */
  virtual void unload_gfx();

  /**
   * Drawing the state
   */
  virtual void draw();

  /**
   * Updating the state
   */
  virtual void update();

  /**
   * Looking up key events
   */
  virtual void events();

  /**
   * @return true if the front layer should be displayed behind this state
   */
  virtual bool front_layer_behind();

  virtual void print();

  /**
   * Constructor
   */
  GameState();

  /**
   * Destructor
   */
  virtual ~GameState();


};

#endif
