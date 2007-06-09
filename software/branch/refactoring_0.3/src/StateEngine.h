/********************************************************************
                          OpenAlchemist

  File : StateEngine.h
  Description : 
  License : GNU General Public License 2 or +
  Author : Guillaume Delhumeau <guillaume.delhumeau@gmail.com>


*********************************************************************/

#ifndef _STATE_ENGINE_H_
#define _STATE_ENGINE_H_

#include <stack>

#include "states/GameState.h"

class StateEngine{

  private:
  std::stack<GameState*> states_stack;
  
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

  StateEngine();
  ~StateEngine();

};

#endif
