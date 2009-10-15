// **********************************************************************
//                            OpenAlchemist
//                        ---------------------
//
//  File        : GameState.h
//  Description : Describe the generic GameState
//  Author      : Guillaume Delhumeau <guillaume.delhumeau@gmail.com>
//  License     : GNU General Public License 2 or higher
//
// **********************************************************************

#ifndef _GAME_STATE_H_
#define _GAME_STATE_H_

#include <string>
#include <ClanLib/display.h>

class CommonResources;
class Window;

/**
 * Generic (Abstract) State Class 
 */
class GameState{

  protected:
  CommonResources *_p_common_resources;

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
  virtual void load_gfx(CL_GraphicContext & gc, std::string skin) = 0;

  /**
   * Unloading GFX
   */
  virtual void unload_gfx() = 0;

  /**
   * Drawing the state
   */
  virtual void draw(CL_GraphicContext & gc) = 0;

  /**
   * Updating the state
   */
  virtual void update(CL_GraphicContext & gc) = 0;

  /**
   * Looking up key events
   */
  virtual void events(Window & window) = 0;

  /**
   * @return true if the front layer should be displayed behind this state
   */
  virtual bool front_layer_behind() = 0;

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