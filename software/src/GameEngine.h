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
#include "states/HighScoreState.h"
#include "states/PauseMenuState.h"
#include "states/SkinsMenuState.h"
#include "states/OptionsMenuState.h"
#include "states/TitleState.h"
#include "states/QuitMenuState.h"


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
  HighScoreState highscore_state;
  PauseMenuState pausemenu_state;
  SkinsMenuState skinsmenu_state;
  OptionsMenuState optionsmenu_state;
  TitleState title_state;
  QuitMenuState quitmenu_state;
  
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
  void set_state_gameover(int mode);
  void set_state_highscore();
  void set_state_options_menu();
  void set_state_skin_menu();
  void set_state_quit_menu(int action);

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

  void set_skin(std::string skin);

  void set_skin_element(u_int element);

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
