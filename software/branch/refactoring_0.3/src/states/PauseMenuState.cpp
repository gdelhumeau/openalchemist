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
#define PAUSE_ITEM_GIVEUP 3
#define PAUSE_ITEM_QUIT 4

#define STEP_APPEARING 0
#define STEP_NORMAL 1
#define STEP_DISAPPEARING 2

#define APPEARING_SPEED 0.003

void PauseMenuState::init()
{
  GameState::init();

  key_echap  = new KeyboardKey(CL_KEY_ESCAPE, false);
  key_up     = new KeyboardKey(CL_KEY_UP    , true );
  key_down   = new KeyboardKey(CL_KEY_DOWN  , true );
  key_enter  = new KeyboardKey(CL_KEY_ENTER , false);
  key_pause  = new KeyboardKey(CL_KEY_PAUSE , false);
}

void PauseMenuState::deinit()
{
  delete key_echap;
  delete key_up;
  delete key_down;
  delete key_enter;
  delete key_pause;
}

void PauseMenuState::load_gfx(std::string skin)
{
  // Getting skins resources
  CL_Zip_Archive zip(skin);
  CL_ResourceManager gfx("menu_pause.xml", &zip, false);

  // First, the sprites
  background = new CL_Sprite("menu/pause/background", &gfx); 

  items[PAUSE_ITEM_RESUME] = new CL_Sprite("menu/pause/resume/unselected", &gfx);
  items_selected[PAUSE_ITEM_RESUME] = new CL_Sprite("menu/pause/resume/selected", &gfx);

  items[PAUSE_ITEM_UNDO] = new CL_Sprite("menu/pause/undo/unselected", &gfx);
  items_selected[PAUSE_ITEM_UNDO] = new CL_Sprite("menu/pause/undo/selected", &gfx);
  undo_unavailable = new CL_Sprite("menu/pause/undo/unavailable", &gfx);

  items[PAUSE_ITEM_RETRY] = new CL_Sprite("menu/pause/retry/unselected", &gfx);
  items_selected[PAUSE_ITEM_RETRY] = new CL_Sprite("menu/pause/retry/selected", &gfx);

  items[PAUSE_ITEM_GIVEUP] = new CL_Sprite("menu/pause/giveup/unselected", &gfx);
  items_selected[PAUSE_ITEM_GIVEUP] = new CL_Sprite("menu/pause/giveup/selected", &gfx);

  items[PAUSE_ITEM_QUIT] = new CL_Sprite("menu/pause/quit/unselected", &gfx);
  items_selected[PAUSE_ITEM_QUIT] = new CL_Sprite("menu/pause/quit/selected", &gfx);


  // Then, propreties
  items_left[PAUSE_ITEM_RESUME] = CL_Integer_to_int("menu/pause/resume/left", &gfx);
  items_top[PAUSE_ITEM_RESUME] = CL_Integer_to_int("menu/pause/resume/top", &gfx);

  items_left[PAUSE_ITEM_UNDO] = CL_Integer_to_int("menu/pause/undo/left", &gfx);
  items_top[PAUSE_ITEM_UNDO] = CL_Integer_to_int("menu/pause/undo/top", &gfx);

  items_left[PAUSE_ITEM_RETRY] = CL_Integer_to_int("menu/pause/retry/left", &gfx);
  items_top[PAUSE_ITEM_RETRY] = CL_Integer_to_int("menu/pause/retry/top", &gfx);

  items_left[PAUSE_ITEM_GIVEUP] = CL_Integer_to_int("menu/pause/giveup/left", &gfx);
  items_top[PAUSE_ITEM_GIVEUP] = CL_Integer_to_int("menu/pause/giveup/top", &gfx);

  items_left[PAUSE_ITEM_QUIT] = CL_Integer_to_int("menu/pause/quit/left", &gfx);
  items_top[PAUSE_ITEM_QUIT] = CL_Integer_to_int("menu/pause/quit/top", &gfx);
  
}

void PauseMenuState::unload_gfx()
{

}

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
      items_selected[i] -> update();
     
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
        undo_unavailable -> update();
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

  if(key_echap->get() || key_pause->get())
  {   
    step = STEP_DISAPPEARING;
    selection = PAUSE_ITEM_RESUME;
  }

  if(key_up -> get())
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

  if(key_down -> get())
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

  if(key_enter -> get())
  {    
    step = STEP_DISAPPEARING;

    switch(selection)
    {
    case PAUSE_ITEM_RETRY:
      common_resources -> player1.new_game();
      break;
    case PAUSE_ITEM_UNDO:
      common_resources -> player1.undo();
      break;
    case PAUSE_ITEM_QUIT:
      common_resources -> engine -> stop();
      break;
    }

  }
}

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

}

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

  if(alpha <= 0.0 || !common_resources -> engine -> is_opengl_used())
  {
    common_resources -> engine -> stop_current_state();   
  }
 
}

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
}

bool PauseMenuState::front_layer_behind()
{
  return true;
}

PauseMenuState::PauseMenuState()
{

}

PauseMenuState::~PauseMenuState()
{
  deinit();
}



