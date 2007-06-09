/********************************************************************
                          OpenAlchemist

  File : CommonState.h
  Description : 
  License : GNU General Public License 2 or +
  Author : Guillaume Delhumeau <guillaume.delhumeau@gmail.com>


*********************************************************************/

#ifndef _COMMON_STATE_H_
#define _COMMON_STATE_H_

#include <ClanLib/display.h>

#include "GameState.h"


/**
 * Common State
 */
class CommonState : public GameState{

  public:
  /** Window */
  CL_DisplayWindow *window;
  /** To know if OpenGL is used */
  bool opengl;

  public:
  void init();
  void deinit();
  void load_gfx(std::string skin);
  void unload_gfx();
  void draw();
  void update();
  void events();

  CommonState(CL_DisplayWindow *window, bool opengl);
  ~CommonState();


};

#endif
