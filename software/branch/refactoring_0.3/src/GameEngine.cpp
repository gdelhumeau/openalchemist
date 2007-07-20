/********************************************************************
                          OpenAlchemist

  File : GameEngine.cpp
  Description : 
  License : GNU General Public License 2 or +
  Author : Guillaume Delhumeau <guillaume.delhumeau@gmail.com>


*********************************************************************/

#include <ClanLib/core.h>
#include <ClanLib/display.h>

#include "GameEngine.h"
#include "Preferences.h"
#include "CommonResources.h"

/**
 * This function return a factor to calcul moving with time
 */
inline float get_time_interval(int fps)
{
  
  if(!fps)return 0;
  return 1000.0/((float)fps);
  
}

GameEngine::GameEngine(CL_DisplayWindow *window, bool opengl)
{
  this -> window = window;
  this -> opengl = opengl;
}


GameEngine::~GameEngine()
{
}

void GameEngine::init()
{
  CommonResources *resources = common_resources_get_instance();
  Preferences *pref = pref_get_instance();

  resources -> init(this);
  resources -> load_gfx(pref -> skin);

  common_state.init();
  common_state.load_gfx(pref -> skin);

  ingame_state.init();
  ingame_state.load_gfx(pref -> skin);

  gameover_state.init();
  gameover_state.load_gfx(pref -> skin);

  hightscore_state.init();
  hightscore_state.load_gfx(pref -> skin);

  
      
}

void GameEngine::run()
{
  set_state_ingame();

  CommonResources *resources = common_resources_get_instance();
  resources -> player1.new_game();

  running = true;
   
  while (running)
  {
    common_state.events();
    common_state.update();
    common_state.draw();

    GameState* current_state = states_stack.top();
    current_state -> events();
    current_state -> update();

    // Drawing the front layer behind the current state or not
    if(current_state -> front_layer_behind())
    {
      resources -> front_layer.draw();
      current_state -> draw();
    }
    else
    {
      current_state -> draw();
      resources -> front_layer.draw();            
    }


    // Get the Framerate
    resources -> fps = fps_getter.get_fps();
    resources -> time_interval = get_time_interval(resources->fps);


    CL_Display::flip();

    // This call updates input and performs other "housekeeping"
    // Call this each frame
    // Also, gives the CPU a rest for 10 milliseconds to catch up
    CL_System::keep_alive();
  }
}


void GameEngine::stop()
{
  running = false;
}



void GameEngine::set_state_title()
{

}


void GameEngine::set_state_new_game_menu()
{

}


void GameEngine::set_state_pause_menu()
{

}


void GameEngine::set_state_ingame()
{
  states_stack.push(&ingame_state);
}


void GameEngine::set_state_gameover()
{
  states_stack.push(&gameover_state);
}

void GameEngine::set_state_hightscore()
{
  states_stack.push(&hightscore_state);
}


void GameEngine::set_state_options_menu()
{

}


void GameEngine::set_state_skin_menu()
{

}



void GameEngine::stop_current_state()
{

}




void GameEngine::toggle_screen()
{
  Preferences *pref = pref_get_instance();
  pref -> fullscreen = !pref -> fullscreen;
  if(pref -> fullscreen)
  {
    window->set_fullscreen(800,600,0,0);
    CL_Mouse::hide();
  }
  else
  {
    window->set_windowed();
    CL_Mouse::show();
  }
  
  pref -> write();
}

int GameEngine::get_fps()
{
  return fps_getter.get_fps();
}
