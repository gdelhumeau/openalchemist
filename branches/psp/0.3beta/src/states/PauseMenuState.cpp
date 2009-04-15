/********************************************************************
                          OpenAlchemist

  File : PauseMenuState.cpp
  Description : 
  License : GNU General Public License 2 or +
  Author : Guillaume Delhumeau <guillaume.delhumeau@gmail.com>


*********************************************************************/

//#include <ClanLib/core.h>

#include <SDL/SDL.h>
#include <SDL/SDL_image.h>

#include "PauseMenuState.h"
#include "../CommonResources.h"
#include "../GameEngine.h"
#include "../misc.h"
#include "../IniFile.h"
extern "C" {
#include "../psp_sdl.h"
}
#define PAUSE_ITEM_RESUME 0
#define PAUSE_ITEM_UNDO 1
#define PAUSE_ITEM_RETRY 2
#define PAUSE_ITEM_OPTIONS 3
#define PAUSE_ITEM_GIVEUP 4
#define PAUSE_ITEM_QUIT 5

#define STEP_APPEARING 0
#define STEP_NORMAL 1
#define STEP_DISAPPEARING 2

#define APPEARING_SPEED 0.003

void PauseMenuState::init()
{
  GameState::init();
  for (int i=0; i<PAUSE_NUMBER_OF_ITEMS; i++)
  {
	items[i] = NULL;
        items_selected[i] = NULL;
  }
  background = NULL;
  undo_unavailable = NULL;
}

void PauseMenuState::deinit()
{
}

void PauseMenuState::load_gfx(std::string skin)
{
  // Getting skins resources
/*  CL_Zip_Archive zip(skin);
  CL_ResourceManager gfx("menu_pause.xml", &zip, false);
*/
  unload_gfx();
  FILE * pause_menu_ini;
  std::string pause_menu_ini_path = "skins/" + skin + "/menu_pause.ini";
  IniFile pause_menu_resources;
  pause_menu_ini = fopen(pause_menu_ini_path.c_str(), "r");
  if (pause_menu_ini != NULL)
     pause_menu_resources.read(pause_menu_ini);

  // First, the sprites
  background = IMG_Load_fromSkin(skin, "dialogs/pause/pause.png");

  items[PAUSE_ITEM_RESUME] = IMG_Load_fromSkin(skin, "dialogs/pause/resume-unselected.png");
  items_selected[PAUSE_ITEM_RESUME] = IMG_Load_fromSkin(skin, "dialogs/pause/resume-selected.png");

  items[PAUSE_ITEM_UNDO] = IMG_Load_fromSkin(skin, "dialogs/pause/undo-unselected.png");
  items_selected[PAUSE_ITEM_UNDO] = IMG_Load_fromSkin(skin, "dialogs/pause/undo-selected.png");
  undo_unavailable = IMG_Load_fromSkin(skin, "dialogs/pause/undo-unavailable.png");

  items[PAUSE_ITEM_RETRY] = IMG_Load_fromSkin(skin, "dialogs/pause/retry-unselected.png");
  items_selected[PAUSE_ITEM_RETRY] = IMG_Load_fromSkin(skin, "dialogs/pause/retry-selected.png");

  items[PAUSE_ITEM_OPTIONS] = IMG_Load_fromSkin(skin, "dialogs/pause/options-unselected.png");
  items_selected[PAUSE_ITEM_OPTIONS] = IMG_Load_fromSkin(skin, "dialogs/pause/options-selected.png");

  items[PAUSE_ITEM_GIVEUP] = IMG_Load_fromSkin(skin, "dialogs/pause/giveup-unselected.png");
  items_selected[PAUSE_ITEM_GIVEUP] = IMG_Load_fromSkin(skin, "dialogs/pause/giveup-selected.png");

  items[PAUSE_ITEM_QUIT] = IMG_Load_fromSkin(skin, "dialogs/pause/quit-unselected.png");
  items_selected[PAUSE_ITEM_QUIT] = IMG_Load_fromSkin(skin, "dialogs/pause/quit-selected.png");


  // Then, propreties

  // Compute y coord of first option entry
  // Considering that all entries have same height
  int y_first_entry = pause_menu_resources.get("y_first_entry",0);
  int x_first_entry = pause_menu_resources.get("x_first_entry",0);
  int y_space_entry = pause_menu_resources.get("y_space_entry",0);

  for(int item = 0; item < PAUSE_NUMBER_OF_ITEMS; item++)
  {
     items_left[item] = x_first_entry; 
     items_top[item]  = y_first_entry + y_space_entry*item;
  }

}

void PauseMenuState::unload_gfx()
{
  for (int i=0; i<PAUSE_NUMBER_OF_ITEMS; i++)
  {
     if (items[i])
     {
	SDL_FreeSurface(items[i]);
	items[i] = NULL;
     }
     if (items_selected[i])
     {
	SDL_FreeSurface(items_selected[i]);
        items_selected[i] = NULL;
     }
  }
  printf("Unload des items ok\n");
  if (background)
  {
    SDL_FreeSurface(background);
    background = NULL;
  }
  if (undo_unavailable)
  {
    SDL_FreeSurface(undo_unavailable);
    undo_unavailable = NULL;
  }
 
}

void PauseMenuState::draw()
{
// Center background dialog
   int x = PSP_SDL_SCREEN_WIDTH/2 - (background->w + background->w%2)/2;
   int y = PSP_SDL_SCREEN_HEIGHT/2 - (background->h + background->h%2)/2;
   psp_sdl_blit_on_screen_at_XY(background, x, y);

  // Drawing 
  for(int i=0; i<PAUSE_NUMBER_OF_ITEMS; ++i)
  {

    if(i == selection)
    {
      //items_selected[i] -> draw(x + items_left[i], y + items_top[i]);
      psp_sdl_blit_on_screen_at_XY(items_selected[i], items_left[i], items_top[i]);
      //items_selected[i] -> update(common_resources -> time_interval);
    }
    else
    {
      if(i != PAUSE_ITEM_UNDO || common_resources -> player1.is_undo_available())
      {
        //items[i] -> draw(x + items_left[i], y + items_top[i]);
	psp_sdl_blit_on_screen_at_XY(items[i], items_left[i], items_top[i]);
      }
      else
      {
        //undo_unavailable -> draw(x + items_left[i], y + items_top[i]);
        psp_sdl_blit_on_screen_at_XY(undo_unavailable, items_left[i], items_top[i]);
       // undo_unavailable -> update(common_resources -> time_interval);
      }
    }
  }

}

void PauseMenuState::update()
{
  switch(step)
  {
  case STEP_APPEARING:
    appear();
    break;
  case STEP_DISAPPEARING:
    disappear();
    break;
  }
}

void PauseMenuState::events()
{
  if(step != STEP_NORMAL)
    return;

  switch(common_resources->CurrentKeyPressed)
  {
  	case KEY_ESCAPE:
	case KEY_PAUSE:
  	{   
  	  step = STEP_DISAPPEARING;
  	  selection = PAUSE_ITEM_RESUME;
	  common_resources->CurrentKeyPressed = 0;
	  break;
  	}
	
	case KEY_SKINS:
	{   
	  step = STEP_DISAPPEARING;
	  selection = PAUSE_ITEM_RESUME;
	  common_resources -> engine -> set_state_skin_menu();
	  common_resources->CurrentKeyPressed = 0;
	  break;
	}
	
	case KEY_UP:
	{
	  if(selection == 0)
	      selection = PAUSE_ITEM_QUIT;
	  else
	  {
	      selection --;
	      if(selection == PAUSE_ITEM_UNDO && !common_resources -> player1.is_undo_available())
	      {
	        selection --;
	      }
	  }
	common_resources->CurrentKeyPressed = 0;
	break;
	}
	
	case KEY_DOWN:
	{
	  if(selection == PAUSE_ITEM_QUIT)
	      selection = 0;
	  else
	  {
	      selection ++;
	      if(selection == PAUSE_ITEM_UNDO && !common_resources -> player1.is_undo_available())
	      {
	        selection ++;
	      }
	  }
	common_resources->CurrentKeyPressed = 0;
	break;
	}
	
	case KEY_ENTER:
	{    
	  step = STEP_DISAPPEARING;
	  common_resources->CurrentKeyPressed = 0;
	  break;
	}
	
	case KEY_OPTIONS:
	{
	    selection = PAUSE_ITEM_OPTIONS;
	    step = STEP_DISAPPEARING;
	    common_resources->CurrentKeyPressed = 0;
	    break;
	}
  }	  
}
void PauseMenuState::appear()
{ 
  if(alpha + ( (int)(SDL_ALPHA_OPAQUE * APPEARING_SPEED*common_resources -> time_interval) >= SDL_ALPHA_OPAQUE))
  {
    step = STEP_NORMAL;
    alpha = SDL_ALPHA_OPAQUE;
  }
  else
    alpha += (int)(SDL_ALPHA_OPAQUE * APPEARING_SPEED * common_resources -> time_interval);

  //background -> set_alpha(alpha);
  SDL_SetAlpha(background, SDL_SRCALPHA | SDL_RLEACCEL, alpha);

  for(int i=0; i<PAUSE_NUMBER_OF_ITEMS; ++i)
  {
    //items[i] -> set_alpha(alpha);
    SDL_SetAlpha(items[i], SDL_SRCALPHA | SDL_RLEACCEL, alpha);
    //items_selected[i] -> set_alpha(alpha);
    SDL_SetAlpha(items_selected[i], SDL_SRCALPHA | SDL_RLEACCEL, alpha);
  }

  //undo_unavailable -> set_alpha(alpha);
  SDL_SetAlpha(undo_unavailable, SDL_SRCALPHA | SDL_RLEACCEL, alpha);

}

void PauseMenuState::disappear()
{  
  alpha -= (int)(SDL_ALPHA_OPAQUE * APPEARING_SPEED * common_resources -> time_interval);

  //background -> set_alpha(alpha);
  SDL_SetAlpha(background, SDL_SRCALPHA | SDL_RLEACCEL, alpha);
  
  for(int i=0; i<PAUSE_NUMBER_OF_ITEMS; ++i)
  {
    //items[i] -> set_alpha(alpha);
    SDL_SetAlpha(items[i], SDL_SRCALPHA | SDL_RLEACCEL, alpha);
    //items_selected[i] -> set_alpha(alpha);
    SDL_SetAlpha(items_selected[i], SDL_SRCALPHA | SDL_RLEACCEL, alpha);
  }

  //undo_unavailable -> set_alpha(alpha);*/
  SDL_SetAlpha(undo_unavailable, SDL_SRCALPHA | SDL_RLEACCEL, alpha);

  // all is completly disappeared
  if(alpha <= SDL_ALPHA_TRANSPARENT || !common_resources -> engine -> is_opengl_used())
  {
    common_resources -> engine -> stop_current_state();
    switch(selection)
    {
    case PAUSE_ITEM_RETRY:
    {
      if(common_resources -> player1.is_game_over())
      {
	common_resources -> player1.new_game();
	common_resources -> engine -> set_state_ingame();
      }
      else
      {
	common_resources -> engine -> set_state_quit_menu(QUITMENU_RETRY);
      }
      break;
    }
    case PAUSE_ITEM_UNDO:
    {
      common_resources -> player1.undo();
      common_resources -> engine -> set_state_ingame();
      break;
    }
    case PAUSE_ITEM_GIVEUP:
    {
      if(common_resources -> player1.is_game_over())
	common_resources -> engine -> set_state_title();
      else
      {
        common_resources -> player1.give_up();
	common_resources -> engine -> set_state_quit_menu(QUITMENU_GIVE_UP);
      }
      break;
    }
    case PAUSE_ITEM_OPTIONS:
    {
      start();
      common_resources -> engine -> set_state_options_menu(); 
      break;
    }
    case PAUSE_ITEM_QUIT:
    {
      common_resources -> engine -> set_state_quit_menu(QUITMENU_EXIT);
      break;
    }
    }
  }
 
}

void PauseMenuState::start()
{
  selection = 0;
  if(common_resources -> engine -> is_opengl_used())
  {
    step = STEP_APPEARING;
    alpha = SDL_ALPHA_TRANSPARENT;
  }
  else
  {
    step = STEP_NORMAL;
  }
}

bool PauseMenuState::front_layer_behind()
{
  return true;
}

void PauseMenuState::print()
{
  printf("PauseMenuState\n");
}


PauseMenuState::PauseMenuState()
{

}

PauseMenuState::~PauseMenuState()
{
  deinit();
}



