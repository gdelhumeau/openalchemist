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
#include "states/PauseMenuState.h"
#include "states/SkinsMenuState.h"
#include "states/OptionsMenuState.h"
#include "states/TitleState.h"
#include "states/QuitMenuState.h"

class LoadingScreen;


/**
 * GameEngine class - controls the states
 */
class GameEngine{

  private:
  
  /**
   * Stack of states, the current state is on the top
   */
  std::stack<GameState*> _states_stack;
  
  /**
   * Window
   */
  CL_DisplayWindow *_p_window;


  /**
   * To know if OpenGL is used
   */

  bool _render_mode;


  /** 
   * Controling main loop
   */
  bool _running;
  

  /**
   * Fps Getter
   */
  CL_FramerateCounter _fps_getter;

  /** 
   * States
   */
  CommonState _common_state;
  InGameState _ingame_state;
  GameOverState _gameover_state;
  PauseMenuState _pausemenu_state;
  SkinsMenuState _skinsmenu_state;
  OptionsMenuState _optionsmenu_state;
  TitleState _title_state;
  QuitMenuState _quitmenu_state;
  
  LoadingScreen * _p_loading_screen;
  
  public:

  /**
   * Initializing game engine
   */
  void init();
	void deinit();

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
	 * Called when the window is resized by the user
   */
	void resize(int width, int height);

  /**
   * Returning Frame Rate
   */
  int get_fps();

  /**
   * Returning if OpenGL is used
   */
  bool is_opengl_used();

	bool is_fullscreen();

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
