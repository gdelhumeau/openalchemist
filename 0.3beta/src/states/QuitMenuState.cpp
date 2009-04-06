/********************************************************************
                          OpenAlchemist

  File : QuitMenuState.cpp
  Description : 
  License : GNU General Public License 2 or +
  Author : Guillaume Delhumeau <guillaume.delhumeau@gmail.com>


*********************************************************************/

#include "QuitMenuState.h"
#include "../CommonResources.h"
#include "../GameEngine.h"
#include "../misc.h"
extern "C" {
#include "../psp_sdl.h"
}
#define SELECTION_YES 1
#define SELECTION_NO  0

#define STEP_APPEARING 0
#define STEP_NORMAL 1
#define STEP_DISAPPEARING 2

#define APPEARING_SPEED 0.003


void QuitMenuState::init()
{
  GameState::init();

  panel_exit     = NULL;
  panel_give_up  = NULL;
  panel_retry    = NULL;
  yes_selected   = NULL;
  yes_unselected = NULL;
  no_selected    = NULL;
  no_unselected  = NULL;

  selection = SELECTION_NO;
}

void QuitMenuState::deinit()
{

}

void QuitMenuState::load_gfx(std::string skin)
{
  // Getting skins resources
//TODO : zlib + resources mngt
/*  CL_Zip_Archive zip(skin);
  CL_ResourceManager gfx("menu_quit.xml", &zip, false);
*/
  //panel_exit    = new CL_Sprite("menu_quit/dialog_panel/sprite_exit", &gfx);
  //panel_give_up = new CL_Sprite("menu_quit/dialog_panel/sprite_giveup", &gfx);
  //panel_retry   = new CL_Sprite("menu_quit/dialog_panel/sprite_retry", &gfx);
  panel_exit    = IMG_Load_fromSkin(skin, "dialogs/quit/dialog-exit.png");
  panel_give_up = IMG_Load_fromSkin(skin, "dialogs/quit/dialog-giveup.png");
  panel_retry   = IMG_Load_fromSkin(skin, "dialogs/quit/dialog-retry.png");
 
  panel_x = (PSP_SDL_SCREEN_WIDTH/2) - ((panel_exit->w + panel_exit->w%2 )/2); //CL_Integer_to_int("menu_quit/dialog_panel/left", &gfx);
  panel_y = (PSP_SDL_SCREEN_HEIGHT/2) - ((panel_exit->h + panel_exit->h%2 )/2); ; //CL_Integer_to_int("menu_quit/dialog_panel/top", &gfx); 

  //yes_selected   = new CL_Sprite("menu_quit/dialog_yes/selected", &gfx);
  //yes_unselected = new CL_Sprite("menu_quit/dialog_yes/unselected", &gfx);
  //yes_x = CL_Integer_to_int("menu_quit/dialog_yes/left", &gfx);
  //yes_y = CL_Integer_to_int("menu_quit/dialog_yes/top", &gfx); 
  yes_selected   = IMG_Load_fromSkin(skin, "dialogs/quit/yes-selected.png");
  yes_unselected = IMG_Load_fromSkin(skin, "dialogs/quit/yes-unselected.png");
  yes_x = PSP_SDL_SCREEN_WIDTH*3/10; //CL_Integer_to_int("menu_quit/dialog_yes/left", &gfx);
  yes_y = PSP_SDL_SCREEN_HEIGHT/2; //CL_Integer_to_int("menu_quit/dialog_yes/top", &gfx); 

  //no_selected   = new CL_Sprite("menu_quit/dialog_no/selected", &gfx);
  //no_unselected = new CL_Sprite("menu_quit/dialog_no/unselected", &gfx);
  no_selected   = IMG_Load_fromSkin(skin, "dialogs/quit/no-selected.png");
  no_unselected = IMG_Load_fromSkin(skin, "dialogs/quit/no-unselected.png");
  no_x = PSP_SDL_SCREEN_WIDTH*6/10;//CL_Integer_to_int("menu_quit/dialog_no/left", &gfx);
  no_y = PSP_SDL_SCREEN_HEIGHT/2;//PSP_SDL_SCREEN_HEIGHT*(4/5);//CL_Integer_to_int("menu_quit/dialog_no/top", &gfx); 

}

void QuitMenuState::unload_gfx()
{
  if(panel_exit)
  {
    delete panel_exit;
    panel_exit = NULL;
  }
  if(panel_give_up)
  {
    delete panel_give_up;
    panel_give_up = NULL;
  }
  if(panel_retry)
  {
    delete panel_retry;
    panel_retry = NULL;
  }
  if(yes_selected)
  {
    delete yes_selected;
    yes_selected = NULL;
  }
  if(yes_unselected)
  {
    delete yes_unselected;
    yes_unselected = NULL;
  }
  if(no_selected)
  {
    delete no_selected;
    no_selected = NULL;
  }
  if(no_unselected)
  {
    delete no_unselected;
    no_unselected = NULL;
  }

}


void QuitMenuState::draw()
{
//  current_panel -> draw(panel_x, panel_y);
  psp_sdl_blit_on_screen_at_XY(current_panel, panel_x, panel_y);  

  if(SELECTION_YES == selection)
  {
    //yes_selected -> draw(yes_x, yes_y);
    psp_sdl_blit_on_screen_at_XY(yes_selected, yes_x, yes_y);
    //no_unselected -> draw(no_x, no_y);
    psp_sdl_blit_on_screen_at_XY(no_unselected, no_x, no_y);
  }
  else
  {
    //yes_unselected -> draw(yes_x, yes_y);
    psp_sdl_blit_on_screen_at_XY(yes_unselected, yes_x, yes_y);
    //no_selected -> draw(no_x, no_y);
    psp_sdl_blit_on_screen_at_XY(no_selected, no_x, no_y);
  }
}

void QuitMenuState::update()
{

//TODO : search for SDL update equivalent
// Split?
 /* current_panel -> update(common_resources -> time_interval);
  yes_selected  -> update(common_resources -> time_interval);
  no_selected   -> update(common_resources -> time_interval);
*/
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

void QuitMenuState::events()
{
 //if(step != STEP_NORMAL)
 //   return;
 switch(common_resources->CurrentKeyPressed)
  {

  case KEY_ENTER:
  {
    if(SELECTION_YES == selection)
    {
      switch(action)
      {
      case QUITMENU_EXIT:
	common_resources -> engine -> stop();
	break;
      case QUITMENU_GIVE_UP:
      case QUITMENU_RETRY:
	step = STEP_DISAPPEARING;
	common_resources -> player1.new_game();
	break;
      }
    }
    else
    {
      common_resources -> engine -> stop_current_state();
    }
  common_resources->CurrentKeyPressed = 0;
  break;
  }

  case KEY_ESCAPE:
  {
    step = STEP_DISAPPEARING;
    common_resources->CurrentKeyPressed = 0;
    break;
  }

  case KEY_LEFT:
  {
    selection = SELECTION_YES;
    common_resources->CurrentKeyPressed = 0;
    break;
  }

  case KEY_RIGHT:
  {
    selection = SELECTION_NO;
    common_resources->CurrentKeyPressed = 0;
    break;
  }
}

}

bool QuitMenuState::front_layer_behind()
{
  return true;
}

QuitMenuState::QuitMenuState()
{

}

QuitMenuState::~QuitMenuState()
{
  unload_gfx();
}



void QuitMenuState::set_action(int a)
{
  action = a;
  switch(action)
  {
  case QUITMENU_EXIT:
    current_panel = panel_exit;
    break;
  case QUITMENU_GIVE_UP:
    current_panel = panel_give_up;
    break;
  case QUITMENU_RETRY:
    current_panel = panel_retry;
    break;
  }
}

void QuitMenuState::appear()
{
  if(alpha + ( (int)(ALPHA_OPAQUE * APPEARING_SPEED * common_resources -> time_interval)) >= ALPHA_OPAQUE)
  {
    step = STEP_NORMAL;
    alpha = ALPHA_OPAQUE;
  }
  else
    alpha += (int)(ALPHA_OPAQUE * APPEARING_SPEED * common_resources -> time_interval);


  //current_panel  -> set_alpha(alpha);
  SDL_SetAlpha(current_panel, SDL_SRCALPHA, alpha);
  //yes_selected   -> set_alpha(alpha);
  SDL_SetAlpha(yes_selected, SDL_SRCALPHA, alpha);
  //yes_unselected -> set_alpha(alpha);  
  SDL_SetAlpha(yes_unselected, SDL_SRCALPHA, alpha);
  //no_selected    -> set_alpha(alpha);
  SDL_SetAlpha(no_selected, SDL_SRCALPHA, alpha);
  //no_unselected  -> set_alpha(alpha);
  SDL_SetAlpha(no_unselected, SDL_SRCALPHA, alpha);
  
}


void QuitMenuState::disappear()
{
  alpha -= (int)(ALPHA_OPAQUE * APPEARING_SPEED * common_resources -> time_interval);

//current_panel  -> set_alpha(alpha);
  SDL_SetAlpha(current_panel, SDL_SRCALPHA, alpha);
  //yes_selected   -> set_alpha(alpha);
  SDL_SetAlpha(yes_selected, SDL_SRCALPHA, alpha);
  //yes_unselected -> set_alpha(alpha);  
  SDL_SetAlpha(yes_unselected, SDL_SRCALPHA, alpha);
  //no_selected    -> set_alpha(alpha);
  SDL_SetAlpha(no_selected, SDL_SRCALPHA, alpha);
  //no_unselected  -> set_alpha(alpha);
  SDL_SetAlpha(no_unselected, SDL_SRCALPHA, alpha);

  if(alpha <= ALPHA_TRANSPARENT || !common_resources -> engine -> is_opengl_used())
  {
    common_resources -> engine -> stop_current_state();
    switch(action)
    {
    case QUITMENU_GIVE_UP:
      common_resources -> engine -> set_state_title();
      break;
    case QUITMENU_RETRY:
      common_resources -> engine -> set_state_ingame();
      break;
    }
  }

}

void QuitMenuState::start()
{
  step = STEP_APPEARING;
  alpha = ALPHA_TRANSPARENT;
}

void QuitMenuState::print()
{
  printf("QuitMenuState\n");
}

