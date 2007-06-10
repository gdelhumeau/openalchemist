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
      
}

void GameEngine::run()
{
  running = true;
   
  while (running)
  {
    common_state.events();
    common_state.update();
    common_state.draw();

    //draw_game();
    //key_events(); 

    // Get the Framerate
    //fps = fps_getter.get_fps();
    //time_interval = get_time_interval(fps);


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

}


void GameEngine::set_state_gameover()
{

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
