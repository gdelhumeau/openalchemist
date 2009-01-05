/********************************************************************
                          OpenAlchemist

  File : PauseMenuState.cpp
  Description : 
  License : GNU General Public License 2 or +
  Author : Guillaume Delhumeau <guillaume.delhumeau@gmail.com>


*********************************************************************/

#include <ClanLib/core.h>

#include "PauseMenuState.h"
#include "../CommonResources.h"
#include "../GameEngine.h"
#include "../misc.h"

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
	items.insert(items.end(), &resume_item);
	items.insert(items.end(), &undo_item);
	items.insert(items.end(), &retry_item);
}

void PauseMenuState::deinit()
{
}

void PauseMenuState::load_gfx(std::string skin)
{
  // Getting skins resources
  CL_Zip_Archive zip(skin);
  CL_ResourceManager gfx("menu_pause.xml", &zip, false);

  // First, the sprites
  background = new CL_Sprite("menu_pause/background", &gfx); 
	
	int x = 400 - background -> get_width()/2;
  int y = 300 - background -> get_height()/2;
	

	resume_item.set_gfx(new CL_Sprite("menu_pause/resume/unselected", &gfx),
											new CL_Sprite("menu_pause/resume/selected"  , &gfx),
											NULL);
	resume_item.set_x(x + CL_Integer_to_int("menu_pause/resume/left", &gfx));
	resume_item.set_y(y + CL_Integer_to_int("menu_pause/resume/top" , &gfx));
	
	undo_item.set_gfx(new CL_Sprite("menu_pause/undo/unselected"    , &gfx),
										new CL_Sprite("menu_pause/undo/selected"      , &gfx),
										new CL_Sprite("menu_pause/undo/unavailable"   , &gfx)
										);
	undo_item.set_x(x + CL_Integer_to_int("menu_pause/undo/left"    , &gfx));
	undo_item.set_y(y + CL_Integer_to_int("menu_pause/undo/top"     , &gfx));
	undo_item.set_locked(true);

	retry_item.set_gfx(new CL_Sprite("menu_pause/retry/unselected"  , &gfx),
										 new CL_Sprite("menu_pause/retry/selected"    , &gfx),
										 NULL);
	retry_item.set_x(x + CL_Integer_to_int("menu_pause/retry/left"  , &gfx));
	retry_item.set_y(y + CL_Integer_to_int("menu_pause/retry/top"   , &gfx));
	
	

  /*
  items[PAUSE_ITEM_UNDO] = new CL_Sprite("menu_pause/undo/unselected", &gfx);
  items_selected[PAUSE_ITEM_UNDO] = new CL_Sprite("menu_pause/undo/selected", &gfx);
  undo_unavailable = new CL_Sprite("menu_pause/undo/unavailable", &gfx);

  items[PAUSE_ITEM_RETRY] = new CL_Sprite("menu_pause/retry/unselected", &gfx);
  items_selected[PAUSE_ITEM_RETRY] = new CL_Sprite("menu_pause/retry/selected", &gfx);

  items[PAUSE_ITEM_OPTIONS] = new CL_Sprite("menu_pause/options/unselected", &gfx);
  items_selected[PAUSE_ITEM_OPTIONS] = new CL_Sprite("menu_pause/options/selected", &gfx);

  items[PAUSE_ITEM_GIVEUP] = new CL_Sprite("menu_pause/giveup/unselected", &gfx);
  items_selected[PAUSE_ITEM_GIVEUP] = new CL_Sprite("menu_pause/giveup/selected", &gfx);

  items[PAUSE_ITEM_QUIT] = new CL_Sprite("menu_pause/quit/unselected", &gfx);
  items_selected[PAUSE_ITEM_QUIT] = new CL_Sprite("menu_pause/quit/selected", &gfx);


  // Then, propreties
  items_left[PAUSE_ITEM_RESUME] = CL_Integer_to_int("menu_pause/resume/left", &gfx);
  items_top[PAUSE_ITEM_RESUME] = CL_Integer_to_int("menu_pause/resume/top", &gfx);

  items_left[PAUSE_ITEM_UNDO] = CL_Integer_to_int("menu_pause/undo/left", &gfx);
  items_top[PAUSE_ITEM_UNDO] = CL_Integer_to_int("menu_pause/undo/top", &gfx);

  items_left[PAUSE_ITEM_RETRY] = CL_Integer_to_int("menu_pause/retry/left", &gfx);
  items_top[PAUSE_ITEM_RETRY] = CL_Integer_to_int("menu_pause/retry/top", &gfx);

  items_left[PAUSE_ITEM_OPTIONS] = CL_Integer_to_int("menu_pause/options/left", &gfx);
  items_top[PAUSE_ITEM_OPTIONS] = CL_Integer_to_int("menu_pause/options/top", &gfx);

  items_left[PAUSE_ITEM_GIVEUP] = CL_Integer_to_int("menu_pause/giveup/left", &gfx);
  items_top[PAUSE_ITEM_GIVEUP] = CL_Integer_to_int("menu_pause/giveup/top", &gfx);

  items_left[PAUSE_ITEM_QUIT] = CL_Integer_to_int("menu_pause/quit/left", &gfx);
  items_top[PAUSE_ITEM_QUIT] = CL_Integer_to_int("menu_pause/quit/top", &gfx);*/
  
}

void PauseMenuState::unload_gfx()
{
	resume_item.unload_gfx();
	undo_item.unload_gfx();
	retry_item.unload_gfx();
}

/*
void PauseMenuState::draw()
{
  int x = 400 - background -> get_width()/2;
  int y = 300 - background -> get_height()/2;
  background -> draw(x,y);

  // Drawing 
  for(int i=0; i<PAUSE_NUMBER_OF_ITEMS; ++i)
  {

    if(i == selection)
    {
      items_selected[i] -> draw(x + items_left[i], y + items_top[i]);
      items_selected[i] -> update(common_resources -> time_interval);
     
    }
    else
    {
      if(i != PAUSE_ITEM_UNDO || common_resources -> player1.is_undo_available())
      {
        items[i] -> draw(x + items_left[i], y + items_top[i]);
        items[i] -> update();
      }
      else
      {
        undo_unavailable -> draw(x + items_left[i], y + items_top[i]);
        undo_unavailable -> update(common_resources -> time_interval);
      }
    }
  }

}
*/

/*
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
*/

/*
void PauseMenuState::events()
{
  if(step != STEP_NORMAL)
    return;

  if(common_resources -> key.escape->get() || common_resources -> key.pause->get())
  {   
    step = STEP_DISAPPEARING;
    selection = PAUSE_ITEM_RESUME;
  }

  if(common_resources -> key.skins->get())
  {   
    step = STEP_DISAPPEARING;
    selection = PAUSE_ITEM_RESUME;
    common_resources -> engine -> set_state_skin_menu();
  }

  if(common_resources -> key.up -> get())
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
  }

  if(common_resources -> key.down -> get())
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
  }

  if(common_resources -> key.enter -> get())
  {    
    step = STEP_DISAPPEARING;
  }

  if(common_resources->key.options -> get() )
  {
    selection = PAUSE_ITEM_OPTIONS;
    step = STEP_DISAPPEARING;
  }
  
}*/

/*
void PauseMenuState::appear()
{ 
  if(alpha + APPEARING_SPEED*common_resources -> time_interval >= 1.0)
  {
    step = STEP_NORMAL;
    alpha = 1.0;
  }
  else
    alpha += APPEARING_SPEED * common_resources -> time_interval;

  background -> set_alpha(alpha);

  for(int i=0; i<PAUSE_NUMBER_OF_ITEMS; ++i)
  {
    items[i] -> set_alpha(alpha);
    items_selected[i] -> set_alpha(alpha);
  }

  undo_unavailable -> set_alpha(alpha);

}*/

/*
void PauseMenuState::disappear()
{  
  alpha -= APPEARING_SPEED * common_resources -> time_interval;

  background -> set_alpha(alpha);

  for(int i=0; i<PAUSE_NUMBER_OF_ITEMS; ++i)
  {
    items[i] -> set_alpha(alpha);
    items_selected[i] -> set_alpha(alpha);
  }

  undo_unavailable -> set_alpha(alpha);

  // all is completly disappeared
  if(alpha <= 0.0 || !common_resources -> engine -> is_opengl_used())
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
 
}*/

/*
void PauseMenuState::start()
{
  selection = 0;
  if(common_resources -> engine -> is_opengl_used())
  {
    step = STEP_APPEARING;
    alpha = 0.0;
  }
  else
  {
    step = STEP_NORMAL;
  }
}*/

/*
bool PauseMenuState::front_layer_behind()
{
  return true;
}*/

void PauseMenuState::action_performed(int selection)
{
	common_resources -> engine -> stop_current_state();
}

PauseMenuState::PauseMenuState()
{

}

PauseMenuState::~PauseMenuState()
{
  deinit();
}



