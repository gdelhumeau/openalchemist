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
  CL_Zip_Archive zip(skin);
  CL_ResourceManager gfx("menu_quit.xml", &zip, false);

  panel_exit    = new CL_Sprite("menu/quit/dialog-panel/sprite-exit", &gfx);
  panel_give_up = new CL_Sprite("menu/quit/dialog-panel/sprite-giveup", &gfx);
  panel_retry   = new CL_Sprite("menu/quit/dialog-panel/sprite-retry", &gfx);

  panel_x = CL_Integer_to_int("menu/quit/dialog-panel/left", &gfx);
  panel_y = CL_Integer_to_int("menu/quit/dialog-panel/top", &gfx); 

  yes_selected   = new CL_Sprite("menu/quit/dialog-yes/selected", &gfx);
  yes_unselected = new CL_Sprite("menu/quit/dialog-yes/unselected", &gfx);
  yes_x = CL_Integer_to_int("menu/quit/dialog-yes/left", &gfx);
  yes_y = CL_Integer_to_int("menu/quit/dialog-yes/top", &gfx); 

  no_selected   = new CL_Sprite("menu/quit/dialog-no/selected", &gfx);
  no_unselected = new CL_Sprite("menu/quit/dialog-no/unselected", &gfx);
  no_x = CL_Integer_to_int("menu/quit/dialog-no/left", &gfx);
  no_y = CL_Integer_to_int("menu/quit/dialog-no/top", &gfx); 

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
  current_panel -> draw(panel_x, panel_y);
  
  if(SELECTION_YES == selection)
  {
    yes_selected -> draw(yes_x, yes_y);
    no_unselected -> draw(no_x, no_y);
  }
  else
  {
    yes_unselected -> draw(yes_x, yes_y);
    no_selected -> draw(no_x, no_y);
  }
}

void QuitMenuState::update()
{
  current_panel -> update(common_resources -> time_interval);
  yes_selected  -> update(common_resources -> time_interval);
  no_selected   -> update(common_resources -> time_interval);

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
  if(step != STEP_NORMAL)
    return;

  if(common_resources -> key.enter -> get())
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
	break;
      }
    }
    else
    {
      common_resources -> engine -> stop_current_state();
    }
  }

  if(common_resources -> key.escape -> get())
  {
    step = STEP_DISAPPEARING;
  }

  if(common_resources -> key.left -> get())
  {
    selection = SELECTION_YES;
  }

  if(common_resources -> key.right -> get())
  {
    selection = SELECTION_NO;
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
  if(alpha + APPEARING_SPEED * common_resources -> time_interval >= 1.0)
  {
    step = STEP_NORMAL;
    alpha = 1.0;
  }
  else
    alpha += APPEARING_SPEED * common_resources -> time_interval;

  current_panel  -> set_alpha(alpha);
  yes_selected   -> set_alpha(alpha);
  yes_unselected -> set_alpha(alpha);  
  no_selected    -> set_alpha(alpha);
  no_unselected  -> set_alpha(alpha);
  
}


void QuitMenuState::disappear()
{
  alpha -= APPEARING_SPEED * common_resources -> time_interval;

  current_panel  -> set_alpha(alpha);
  yes_selected   -> set_alpha(alpha);
  yes_unselected -> set_alpha(alpha);  
  no_selected    -> set_alpha(alpha);
  no_unselected  -> set_alpha(alpha);

  if(alpha <= 0.0 || !common_resources -> engine -> is_opengl_used())
  {
    switch(action)
    {
    case QUITMENU_GIVE_UP:
      common_resources -> engine -> set_state_title();
      break;
    case QUITMENU_RETRY:
      common_resources -> player1.new_game();
      common_resources -> engine -> set_state_ingame();
      break;
    default:
      common_resources -> engine -> stop_current_state();
      break;
    }
  }

}

void QuitMenuState::start()
{
  step = STEP_APPEARING;
  alpha = 0.0;
}
