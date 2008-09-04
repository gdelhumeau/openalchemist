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
#include "misc.h"

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
  // Drawing loading picture

  std::string file_path = get_data_path();
  CL_Surface loading(file_path+get_path_separator()+"loading.png");
  CL_Display::clear(CL_Color(0, 0, 0));
  loading.draw(400-loading.get_width()/2,300-loading.get_height()/2);
  CL_Display::flip();

  CommonResources *resources = common_resources_get_instance();
  Preferences *pref = pref_get_instance();

  fps_getter.set_fps_limit(pref -> maxfps);

  resources -> init(this);
  common_state.init();
  ingame_state.init();
  gameover_state.init();
  highscore_state.init();
  pausemenu_state.init();
  skinsmenu_state.init();
  optionsmenu_state.init();
  title_state.init();
  quitmenu_state.init();
  
  set_skin(pref -> skin);
      
}

void GameEngine::run()
{
  set_state_title();

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
  while(!states_stack.empty())
  {
    states_stack.pop();
  }
  states_stack.push(&title_state);
  title_state.start();
}


void GameEngine::set_state_new_game_menu()
{

}


void GameEngine::set_state_pause_menu()
{
  if(states_stack.top() != &pausemenu_state)
  {
    states_stack.push(&pausemenu_state);
    pausemenu_state.start();
  }
}


void GameEngine::set_state_ingame()
{
  CommonResources *common_resources = common_resources_get_instance();
  common_resources -> current_player = &(common_resources -> player1);
  states_stack.push(&ingame_state);
}


void GameEngine::set_state_gameover(int mode)
{
  gameover_state.set_mode(mode);
  gameover_state.start();
  states_stack.push(&gameover_state);
}

/*void GameEngine::set_state_highscore()
{
  states_stack.push(&highscore_state);
  }*/


void GameEngine::set_state_options_menu()
{
  if(states_stack.top() != &optionsmenu_state)
  {
    states_stack.push(&optionsmenu_state);
    optionsmenu_state.start();
    pausemenu_state.start();
  }
}


void GameEngine::set_state_skin_menu()
{
  if(states_stack.top() != &skinsmenu_state)
  {
    states_stack.push(&skinsmenu_state);
    skinsmenu_state.start();
    pausemenu_state.start();
    optionsmenu_state.start();
  }
}

void GameEngine::set_state_quit_menu(int action)
{
  if(states_stack.top() != &quitmenu_state)
  {
    quitmenu_state.set_action(action);
    states_stack.push(&quitmenu_state);
    pausemenu_state.start();
    quitmenu_state.start();
  }
}



void GameEngine::stop_current_state()
{
  states_stack.pop();
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

bool GameEngine::is_opengl_used()
{
  return opengl;
}

void GameEngine::set_skin(std::string skin)
{
  CommonResources *resources = common_resources_get_instance();
  Preferences *pref = pref_get_instance();

  std::string old_skin = pref -> skin;

  try{

    pref -> skin = skin;

    resources -> load_gfx(pref -> skin);

    title_state.load_gfx(pref -> skin);

    common_state.load_gfx(pref -> skin);

    ingame_state.load_gfx(pref -> skin);

    gameover_state.load_gfx(pref -> skin);

    highscore_state.load_gfx(pref -> skin);

    pausemenu_state.load_gfx(pref -> skin);

    skinsmenu_state.load_gfx(pref -> skin);

    optionsmenu_state.load_gfx(pref -> skin);

    optionsmenu_state.load_gfx(pref -> skin);

    title_state.load_gfx(pref -> skin);

    quitmenu_state.load_gfx(pref -> skin);

    pref -> write();

  }
  catch(CL_Error err)
  {
    std::cout << "Skin error : " << err.message << std::endl;
    std::cout << "Error in : " << skin << std::endl;
    if(old_skin == skin)
    {
      std::cout << "Now loading default skin." << std::endl;
      skin = get_skins_path() + get_path_separator() + "aqua.zip";
      set_skin(skin);
    }
    else
    {
      std::cout << "Now reloading current skin." << std::endl;
      set_skin(old_skin);
    }
  }
}

void GameEngine::set_skin_element(u_int element)
{
  skinsmenu_state.set_skin_elements(element);
}
