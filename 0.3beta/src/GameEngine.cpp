/********************************************************************
                          OpenAlchemist

  File : GameEngine.cpp
  Description : 
  License : GNU General Public License 2 or +
  Author : Guillaume Delhumeau <guillaume.delhumeau@gmail.com>


*********************************************************************/

//#include <ClanLib/core.h>
//#include <ClanLib/display.h>
#include <SDL/SDL_error.h>

#include "GameEngine.h"
#include "Preferences.h"
#include "CommonResources.h"
#include "misc.h"

GameEngine::GameEngine(SDL_Surface * pspScreen,/*CL_DisplayWindow *window,*/ bool opengl)
{
  //this -> window = window;
  this -> opengl = opengl;
}


GameEngine::~GameEngine()
{
}

void GameEngine::init()
{
  // Drawing loading picture

  std::string file_path = get_data_path();
  //CL_Surface loading(file_path+get_path_separator()+"loading.png");
  //CL_Display::clear(CL_Color(0, 0, 0));
  //loading.draw(400-loading.get_width()/2,300-loading.get_height()/2);
  //CL_Display::flip();
  printf("Begining of init, get_data_path returns : %s\n", file_path.c_str());
  CommonResources *resources = common_resources_get_instance();
  printf("Common resources get_instance passed\n");
  Preferences *pref = pref_get_instance();
  printf("Preference get instance done\n");

//  fps_getter.set_fps_limit(pref -> maxfps);

  resources -> init(this);
  common_state.init();
  ingame_state.init();
  gameover_state.init();
  pausemenu_state.init();
  skinsmenu_state.init();
printf("skinmenu state ok\n");
  optionsmenu_state.init();
printf("optionsmenu_state init ok\n");
  title_state.init();
printf("title_state init ok\n");
  quitmenu_state.init();
  printf("quitmennu init ok\n");
  set_skin(pref -> skin);
printf("Game engine init done\n");
      
}

void GameEngine::run()
{
  int previousKey = 0;
  int repeat = 0;
  set_state_title();
  CommonResources *resources = common_resources_get_instance();
  resources -> player1.new_game();

  running = true;

  while (running)
  {
#ifndef LINUX_MODE
    SceCtrlData pad;
    sceCtrlPeekBufferPositive(&pad, 1);
    if ( (previousKey != pad.Buttons)|| (repeat >25))
	{
	   repeat = 0;
	   printf("previous key : %d\n",previousKey);
           resources -> CurrentKeyPressed = pad.Buttons;
           previousKey = pad.Buttons;
	}
#else
    SDL_Event event;
    SDL_PollEvent(&event);
    if (event.type == SDL_KEYDOWN)
       if ( (previousKey != event.key.keysym.sym) || (repeat >25))
	{
	   repeat = 0;
	   printf("previous key : %d\n",previousKey);
           resources -> CurrentKeyPressed = event.key.keysym.sym;
           previousKey = event.key.keysym.sym;
	}
#endif
    repeat++;
    common_state.events();
    common_state.update();
    common_state.draw();

    GameState* current_state = states_stack.top();
    //current_state -> print();
    current_state -> events();
    current_state -> update();
    // Drawing the front layer behind the current state or not
///TODO : we do not manage the front layer yet, see that later
/*    if(current_state -> front_layer_behind())
    {
      resources -> front_layer.draw();
      current_state -> draw();
    }
    else
    {
      current_state -> draw();
      resources -> front_layer.draw();            
    }
*/
      current_state -> draw();
    // Get the Framerate
 //   resources -> fps = fps_getter.get_fps();
    resources -> time_interval = get_time_interval(65/*resources->fps*/);


    //CL_Display::flip();
    psp_sdl_flip();

    // This call updates input and performs other "housekeeping"
    // Call this each frame
    // Also, gives the CPU a rest for 10 milliseconds to catch up
    //CL_System::keep_alive();
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
  /*Preferences *pref = pref_get_instance();
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
  
  pref -> write();*/
}

int GameEngine::get_fps()
{
  return 60;//fps_getter.get_fps();
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
#ifndef LINUX_MODE     
FILE * debugFile;
  debugFile=fopen("debug.log", "a+");
  
  fprintf(debugFile, "Load skin gameengine began\n");
  fclose(debugFile);
#else
  printf( "Load skin gameengine began\n");
#endif

    pref -> skin = skin;
#ifndef LINUX_MODE     
    freopen(  "debug.log","a+",debugFile);
    fprintf(debugFile, "pref -> skin = skin %s ok\n",skin.c_str());
    fclose(debugFile);
#else
    printf( "pref -> skin = skin %s ok\n",skin.c_str());
#endif

    resources -> load_gfx(pref -> skin);
#ifndef LINUX_MODE     
    freopen(  "debug.log","a+",debugFile);
    fprintf(debugFile, "resources -> load_gfx(pref -> skin);n %s ok\n",skin.c_str());
    fclose(debugFile);
#else
    printf("resources -> load_gfx(pref -> skin);n %s ok\n",skin.c_str());
#endif
    title_state.load_gfx(pref -> skin);
#ifndef LINUX_MODE     
    freopen(  "debug.log","a+",debugFile);
    fprintf(debugFile, "title_state.load_gfx(pref -> skin); %s ok\n",skin.c_str());
    fclose(debugFile);
#else
    printf("title_state.load_gfx(pref -> skin); %s ok\n",skin.c_str());
#endif
    common_state.load_gfx(pref -> skin);
#ifndef LINUX_MODE     
    freopen(  "debug.log","a+",debugFile);
    fprintf(debugFile, "common_state.load_gfx(pref -> skin); %s ok\n",skin.c_str());
    fclose(debugFile);
#else
    printf("common_state.load_gfx(pref -> skin); %s ok\n",skin.c_str());
#endif
    ingame_state.load_gfx(pref -> skin);
#ifndef LINUX_MODE     
    freopen(  "debug.log","a+",debugFile);
    fprintf(debugFile, "ingame_state.load_gfx(pref -> skin); %s ok\n",skin.c_str());
    fclose(debugFile);
#else
    printf("ingame_state.load_gfx(pref -> skin); %s ok\n",skin.c_str());
#endif
    gameover_state.load_gfx(pref -> skin);
#ifndef LINUX_MODE     
    freopen(  "debug.log","a+",debugFile);
    fprintf(debugFile, "gameover_state.load_gfx(pref -> skin); %s ok\n",skin.c_str());
    fclose(debugFile);
#else
    printf( "gameover_state.load_gfx(pref -> skin); %s ok\n",skin.c_str());
#endif
    pausemenu_state.load_gfx(pref -> skin);
#ifndef LINUX_MODE     
    freopen(  "debug.log","a+",debugFile);
    fprintf(debugFile, "pausemenu_state.load_gfx(pref -> skin); %s ok\n",skin.c_str());
    fclose(debugFile);
#else
    printf( "pausemenu_state.load_gfx(pref -> skin); %s ok\n",skin.c_str());
#endif
    skinsmenu_state.load_gfx(pref -> skin);
#ifndef LINUX_MODE     
    freopen(  "debug.log","a+",debugFile);
    fprintf(debugFile, "skinsmenu_state.load_gfx(pref -> skin); %s ok\n",skin.c_str());
    fclose(debugFile);
#else
    printf( "skinsmenu_state.load_gfx(pref -> skin); %s ok\n",skin.c_str());
#endif
    optionsmenu_state.load_gfx(pref -> skin);
#ifndef LINUX_MODE     
    freopen(  "debug.log","a+",debugFile);
    fprintf(debugFile, "optionsmenu_state.load_gfx(pref -> skin); %s ok\n",skin.c_str());
    fclose(debugFile);
    //optionsmenu_state.load_gfx(pref -> skin);
#else
    printf("optionsmenu_state.load_gfx(pref -> skin); %s ok\n",skin.c_str());
#endif
    title_state.load_gfx(pref -> skin);
#ifndef LINUX_MODE     
    freopen(  "debug.log","a+",debugFile);
    fprintf(debugFile, " title_state.load_gfx(pref -> skin); %s ok\n",skin.c_str());
    fclose(debugFile);
#else
    printf(" title_state.load_gfx(pref -> skin); %s ok\n",skin.c_str());
#endif
    quitmenu_state.load_gfx(pref -> skin);
#ifndef LINUX_MODE     
    freopen(  "debug.log","a+",debugFile);
    fprintf(debugFile, "quitmenu_state.load_gfx(pref -> skin); %s ok\n",skin.c_str());
    fclose(debugFile);
#else
    printf("quitmenu_state.load_gfx(pref -> skin); %s ok\n",skin.c_str());
#endif
    pref -> write();
#ifndef LINUX_MODE     
    freopen(  "debug.log","a+",debugFile);
    fprintf(debugFile, "pref -> write(); %s ok\n",skin.c_str());
    fclose(debugFile);
#else
    printf("pref -> write(); %s ok\n",skin.c_str());
#endif
  }
  catch(SDL_Error err)
  {
    std::cout << "Skin error : " /*<< err.message */<< std::endl;
    std::cout << "Error in : " << skin << std::endl;
    if(old_skin.compare(skin))
    {
      std::cout << "Now loading default skin." << std::endl;
      skin = /*get_skins_path() + get_path_separator() + */"aqua";/*.zip";*/
      set_skin(skin);
    }
    else
    {
      //throw err;
	std::cout << "should throw an error" << std::endl;
    }
  }
}

void GameEngine::set_skin_element(u_int element)
{
  skinsmenu_state.set_skin_elements(element);
}
