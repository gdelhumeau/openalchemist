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
  // First, the sprites
  //background = new CL_Sprite("menu_pause/background", &gfx); 
  background = IMG_Load_fromSkin(skin, "dialogs/pause/pause.png");

  //items[PAUSE_ITEM_RESUME] = new CL_Sprite("menu_pause/resume/unselected", &gfx);
  //items_selected[PAUSE_ITEM_RESUME] = new CL_Sprite("menu_pause/resume/selected", &gfx);
  items[PAUSE_ITEM_RESUME] = IMG_Load_fromSkin(skin, "dialogs/pause/resume-unselected.png");
  items_selected[PAUSE_ITEM_RESUME] = IMG_Load_fromSkin(skin, "dialogs/pause/resume-selected.png");

  //items[PAUSE_ITEM_UNDO] = new CL_Sprite("menu_pause/undo/unselected", &gfx);
  //items_selected[PAUSE_ITEM_UNDO] = new CL_Sprite("menu_pause/undo/selected", &gfx);
  //undo_unavailable = new CL_Sprite("menu_pause/undo/unavailable", &gfx);
  items[PAUSE_ITEM_UNDO] = IMG_Load_fromSkin(skin, "dialogs/pause/undo-unselected.png");
  items_selected[PAUSE_ITEM_UNDO] = IMG_Load_fromSkin(skin, "dialogs/pause/undo-selected.png");
  undo_unavailable = IMG_Load_fromSkin(skin, "dialogs/pause/undo-unavailable.png");

  //items[PAUSE_ITEM_RETRY] = new CL_Sprite("menu_pause/retry/unselected", &gfx);
  //items_selected[PAUSE_ITEM_RETRY] = new CL_Sprite("menu_pause/retry/selected", &gfx);
  items[PAUSE_ITEM_RETRY] = IMG_Load_fromSkin(skin, "dialogs/pause/retry-unselected.png");
  items_selected[PAUSE_ITEM_RETRY] = IMG_Load_fromSkin(skin, "dialogs/pause/retry-selected.png");

  //items[PAUSE_ITEM_OPTIONS] = new CL_Sprite("menu_pause/options/unselected", &gfx);
  //items_selected[PAUSE_ITEM_OPTIONS] = new CL_Sprite("menu_pause/options/selected", &gfx);
  items[PAUSE_ITEM_OPTIONS] = IMG_Load_fromSkin(skin, "dialogs/pause/options-unselected.png");
  items_selected[PAUSE_ITEM_OPTIONS] = IMG_Load_fromSkin(skin, "dialogs/pause/options-selected.png");

  //items[PAUSE_ITEM_GIVEUP] = new CL_Sprite("menu_pause/giveup/unselected", &gfx);
  //items_selected[PAUSE_ITEM_GIVEUP] = new CL_Sprite("menu_pause/giveup/selected", &gfx);
  items[PAUSE_ITEM_GIVEUP] = IMG_Load_fromSkin(skin, "dialogs/pause/giveup-unselected.png");
  items_selected[PAUSE_ITEM_GIVEUP] = IMG_Load_fromSkin(skin, "dialogs/pause/giveup-selected.png");

  //items[PAUSE_ITEM_QUIT] = new CL_Sprite("menu_pause/quit/unselected", &gfx);
  //items_selected[PAUSE_ITEM_QUIT] = new CL_Sprite("menu_pause/quit/selected", &gfx);
  items[PAUSE_ITEM_QUIT] = IMG_Load_fromSkin(skin, "dialogs/pause/quit-unselected.png");
  items_selected[PAUSE_ITEM_QUIT] = IMG_Load_fromSkin(skin, "dialogs/pause/quit-selected.png");


  // Then, propreties
  items_left[PAUSE_ITEM_RESUME] =   50;   //CL_Integer_to_int("menu_pause/resume/left", &gfx);
  items_top[PAUSE_ITEM_RESUME] =    50;   //CL_Integer_to_int("menu_pause/resume/top", &gfx);

  items_left[PAUSE_ITEM_UNDO] =     50;   //CL_Integer_to_int("menu_pause/undo/left", &gfx);
  items_top[PAUSE_ITEM_UNDO] =      75;   //CL_Integer_to_int("menu_pause/undo/top", &gfx);

  items_left[PAUSE_ITEM_RETRY] =    50;   //CL_Integer_to_int("menu_pause/retry/left", &gfx);
  items_top[PAUSE_ITEM_RETRY] =    100;   //CL_Integer_to_int("menu_pause/retry/top", &gfx);

  items_left[PAUSE_ITEM_OPTIONS] =  50;   //CL_Integer_to_int("menu_pause/options/left", &gfx);
  items_top[PAUSE_ITEM_OPTIONS] =  125;   //CL_Integer_to_int("menu_pause/options/top", &gfx);

  items_left[PAUSE_ITEM_GIVEUP] =   50;   //CL_Integer_to_int("menu_pause/giveup/left", &gfx);
  items_top[PAUSE_ITEM_GIVEUP] =   150;   //CL_Integer_to_int("menu_pause/giveup/top", &gfx);

  items_left[PAUSE_ITEM_QUIT] =     50;   //CL_Integer_to_int("menu_pause/quit/left", &gfx);
  items_top[PAUSE_ITEM_QUIT] =     175;   //CL_Integer_to_int("menu_pause/quit/top", &gfx);
  
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
//TODO : choose or determine correct position of option menu
// using PSP_SDL_SCREEN_WIDTH and PSP_SDL_SCREEN_HEIGHT
	//  int x = 400 - background -> get_width()/2;
	//  int y = 300 - background -> get_height()/2;
	//  background -> draw(x,y);
   int x = PSP_SDL_SCREEN_WIDTH/2 - (background->w + background->w%2)/2;
   int y = PSP_SDL_SCREEN_HEIGHT/10;
   psp_sdl_blit_on_screen_at_XY(background, x, y);

  // Drawing 
  for(int i=0; i<PAUSE_NUMBER_OF_ITEMS; ++i)
  {

    if(i == selection)
    {
      //items_selected[i] -> draw(x + items_left[i], y + items_top[i]);
      psp_sdl_blit_on_screen_at_XY(items_selected[i], x + items_left[i], y + items_top[i]);
      //items_selected[i] -> update(common_resources -> time_interval);
      //TODO: find equivalent to CL_Sprite::update
      /* ???? SDL_Flip(screen_surface);*/
     
    }
    else
    {
      if(i != PAUSE_ITEM_UNDO || common_resources -> player1.is_undo_available())
      {
        //items[i] -> draw(x + items_left[i], y + items_top[i]);
	psp_sdl_blit_on_screen_at_XY(items[i], x + items_left[i], y + items_top[i]);
       // items[i] -> update();
        //TODO: find equivalent to CL_Sprite::update
      /* ???? SDL_Flip(screen_surface);*/
      }
      else
      {
        //undo_unavailable -> draw(x + items_left[i], y + items_top[i]);
        psp_sdl_blit_on_screen_at_XY(undo_unavailable,x + items_left[i], y + items_top[i]);
       // undo_unavailable -> update(common_resources -> time_interval);
        //TODO: find equivalent to CL_Sprite::update
      /* ???? SDL_Flip(screen_surface);*/
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
  if(alpha + ( (int)(ALPHA_OPAQUE * APPEARING_SPEED*common_resources -> time_interval) >= ALPHA_OPAQUE))
  {
    step = STEP_NORMAL;
    alpha = ALPHA_OPAQUE;
  }
  else
    alpha += (int)(ALPHA_OPAQUE * APPEARING_SPEED * common_resources -> time_interval);

  //background -> set_alpha(alpha);
  SDL_SetAlpha(background, SDL_SRCALPHA, alpha);

  for(int i=0; i<PAUSE_NUMBER_OF_ITEMS; ++i)
  {
    //items[i] -> set_alpha(alpha);
    SDL_SetAlpha(items[i], SDL_SRCALPHA, alpha);
    //items_selected[i] -> set_alpha(alpha);
    SDL_SetAlpha(items_selected[i], SDL_SRCALPHA, alpha);
  }

  //undo_unavailable -> set_alpha(alpha);
  SDL_SetAlpha(undo_unavailable, SDL_SRCALPHA, alpha);

}

void PauseMenuState::disappear()
{  
  alpha -= (int)(ALPHA_OPAQUE * APPEARING_SPEED * common_resources -> time_interval);

  //background -> set_alpha(alpha);
  SDL_SetAlpha(background, SDL_SRCALPHA, alpha);
  
  for(int i=0; i<PAUSE_NUMBER_OF_ITEMS; ++i)
  {
    //items[i] -> set_alpha(alpha);
    SDL_SetAlpha(items[i], SDL_SRCALPHA, alpha);
    //items_selected[i] -> set_alpha(alpha);
    SDL_SetAlpha(items_selected[i], SDL_SRCALPHA, alpha);
  }

  //undo_unavailable -> set_alpha(alpha);*/
  SDL_SetAlpha(undo_unavailable, SDL_SRCALPHA, alpha);

  // all is completly disappeared
  if(alpha <= ALPHA_TRANSPARENT || !common_resources -> engine -> is_opengl_used())
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
    alpha = ALPHA_TRANSPARENT;
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



