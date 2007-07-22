/********************************************************************
                          OpenAlchemist

  File : GameEngine.h
  Description : 
  License : GNU General Public License 2 or +
  Author : Guillaume Delhumeau <guillaume.delhumeau@gmail.com>


*********************************************************************/

#ifndef _GAME_ENGINE_H_
#define _GAME_ENGINE_H_

#include <stack>
#include <ClanLib/display.h>

#include "states/GameState.h"
#include "states/CommonState.h"
#include "states/InGameState.h"
#include "states/GameOverState.h"
#include "states/HightScoreState.h"
#include "states/PauseMenuState.h"
#include "states/SkinsMenuState.h"

/**
 * GameEngine class - controls the states
 */
class GameEngine{

  private:
  
  /**
   * Stack of states, the current state is on the top
   */
  std::stack<GameState*> states_stack;
  
  /**
   * Window
   */
  CL_DisplayWindow *window;


  /**
   * To know if OpenGL is used
   */

  bool opengl;


  /** 
   * Controling main loop
   */
  bool running;
  

  /**
   * Fps Getter
   */
  CL_FramerateCounter fps_getter;

  /** 
   * States
   */
  CommonState common_state;
  InGameState ingame_state;
  GameOverState gameover_state;
  HightScoreState hightscore_state;
  PauseMenuState pausemenu_state;
  SkinsMenuState skinsmenu_state;
  
  public:

  /**
   * Initializing game engine
   */
  void init();

  /**
   * Main loop
   */
  void run();

  /**
   * Stoping the game engine
   */
  void stop();

  void set_state_title();
  void set_state_new_game_menu();
  void set_state_pause_menu();
  void set_state_ingame();
  void set_state_gameover();
  void set_state_hightscore();
  void set_state_options_menu();
  void set_state_skin_menu();

  /**
   * Deleting current state of the stack
   */
  void stop_current_state();

  /**
   * Switching to full screen mode or windowed mode
   */
  void toggle_screen();

  /**
   * Returning Frame Rate
   */
  int get_fps();

  /**
   * Returning if OpenGL is used
   */
  bool is_opengl_used();

  /**
   * Constructor
   */
  GameEngine(CL_DisplayWindow *window, bool opengl);

  /**
   * Destructor
   */
  ~GameEngine();

};

#endif
