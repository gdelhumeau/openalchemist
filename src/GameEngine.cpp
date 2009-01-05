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

	CL_System::keep_alive();
	
	// Drawing loading picture
  std::string file_path = get_data_path();
  CL_Surface loading(file_path+get_path_separator()+"loading.png");

	for(int i=0; i<100; ++i)
	{
		CL_Display::clear(CL_Color(0, 0, 0));	
		loading.draw(400-loading.get_width()/2, 300-loading.get_height()/2);
		CL_Display::flip();
		CL_System::keep_alive();
	}

  CommonResources *resources = common_resources_get_instance();
  Preferences *pref = pref_get_instance();

  fps_getter.set_fps_limit(pref -> maxfps);

  resources -> init(this);
  common_state.init();
  ingame_state.init();
  gameover_state.init();
  pausemenu_state.init();
  skinsmenu_state.init();
  optionsmenu_state.init();
  title_state.init();
  quitmenu_state.init();	
  
  set_skin(pref -> skin);
	
	resize(window -> get_width(), window -> get_height());
      
}

void GameEngine::run()
{
  set_state_title();

  CommonResources *resources = common_resources_get_instance();
  resources -> player1.new_game();

  running = true;
	
	init();
   
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
		
		//resize(window -> get_width(), window -> get_height());


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
		
		if(pref -> widescreen && opengl)
		{
			CL_GraphicContext *gc = window -> get_gc();
			gc -> set_scale(0.83, 1.0);
			gc -> add_translate(80, 0, 0);					
		}
  }
  else
  {
    window->set_windowed();
    CL_Mouse::show();
		
		CL_GraphicContext *gc = window -> get_gc();
		gc -> set_scale(1.0, 1.0);
		gc -> set_translate(0, 0, 0);
	
  }
  
  pref -> write();
}

/**
 * Called when user resize the window
 */
void GameEngine::resize(int width, int height)
{
	//static int old_width = 0;
	//static int old_height = 0;		
	
	if(!window -> is_fullscreen())
	{
		CL_GraphicContext *gc = window -> get_gc();				
		
		double ratio = (double) width / (double) height;			
		
		/*if(old_width != width || old_height != height)
		{			
			old_width = width;
			old_height = height;			
						
			if(ratio > 800.0 / 600.0 * 1.01)
			{
				width = height * 1.33;
				window -> set_size(width, height);
			}
			else if (ratio < 800.0 / 600.0 * 0.99)
			{
				height = width * 0.75;
				window -> set_size(width, height);
			}
			
			double scale_width = width / 800.0;
			double scale_height= height / 600.0;
			gc -> set_scale(scale_width, scale_height);
		}
		else*/
		{
			
			if(ratio > 800.0 / 600.0 * 1.01)
			{
				double n_width = height * 1.333333;
				int dx = (width - n_width) / 2;
				double scale_width = n_width / 800.0;
				double scale_height= height / 600.0;
				gc -> set_scale(scale_width, scale_height);	
				gc -> add_translate(dx, 0, 0);			
				
			}
			else if (ratio < 800.0 / 600.0 * 0.99)
			{
				double n_height = width * 0.75;
				int dy = (height - n_height) / 2;
				double scale_width = width / 800.0;
				double scale_height= n_height / 600.0;
				gc -> set_scale(scale_width, scale_height);	
				gc -> add_translate(0, dy, 0);
			} 
			
		}
		
	}
}


int GameEngine::get_fps()
{
  return fps_getter.get_fps();
}

bool GameEngine::is_opengl_used()
{
  return opengl;
}

bool GameEngine::is_fullscreen()
{
	Preferences *pref = pref_get_instance();
	return pref -> fullscreen;
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
    if(old_skin.compare(skin))
    {
      std::cout << "Now loading default skin." << std::endl;
      skin = get_skins_path() + get_path_separator() + "aqua.zip";
      set_skin(skin);
    }
    else
    {
      throw err;
    }
  }
}

void GameEngine::set_skin_element(u_int element)
{
  skinsmenu_state.set_skin_elements(element);
}
