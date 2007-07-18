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


class GameEngine{

  private:
  std::stack<GameState*> states_stack;
  
  /** Window */
  CL_DisplayWindow *window;
  /** To know if OpenGL is used */
  bool opengl;
  /** */
  bool running;
  /** Fps Getter */
  CL_FramerateCounter fps_getter;

  /* States */
  CommonState common_state;
  InGameState ingame_state;
  GameOverState gameover_state;
  
  public:
  void init();
  void run();
  void stop();

  void set_state_title();
  void set_state_new_game_menu();
  void set_state_pause_menu();
  void set_state_ingame();
  void set_state_gameover();
  void set_state_options_menu();
  void set_state_skin_menu();

  void stop_current_state();

  void toggle_screen();
  int get_fps();

  GameEngine(CL_DisplayWindow *window, bool opengl);
  ~GameEngine();

};

#endif
