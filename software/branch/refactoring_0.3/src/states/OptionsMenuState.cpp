/********************************************************************
                          OpenAlchemist

  File : OptionsMenuState.cpp
  Description : 
  License : GNU General Public License 2 or +
  Author : Guillaume Delhumeau <guillaume.delhumeau@gmail.com>


*********************************************************************/

#include <ClanLib/core.h>

#include "OptionsMenuState.h"
#include "../CommonResources.h"
#include "../GameEngine.h"
#include "../misc.h"
#include "../Preferences.h"

#define OPTIONS_ITEM_CHANGESKIN 0
#define OPTIONS_ITEM_FULLSCREEN 1
#define OPTIONS_ITEM_SOUND 2
#define OPTIONS_ITEM_MUSIC 3
#define OPTIONS_ITEM_QUIT 4

#define STEP_APPEARING 0
#define STEP_NORMAL 1
#define STEP_DISAPPEARING 2

#define APPEARING_SPEED 0.003

void OptionsMenuState::init()
{
  GameState::init();

  Preferences *pref = pref_get_instance();
  
  sound_level = pref -> sound_level;
  music_level = pref -> music_level;
}

void OptionsMenuState::deinit()
{
  Preferences *pref = pref_get_instance();
  
  pref -> sound_level = sound_level;
  pref -> music_level = music_level;

  pref -> write();
}

void OptionsMenuState::load_gfx(std::string skin)
{
  // Getting skins resources
  CL_Zip_Archive zip(skin);
  CL_ResourceManager gfx("menu_options.xml", &zip, false);

  // First, the sprites
  background = new CL_Sprite("menu/options/background", &gfx); 

  items[OPTIONS_ITEM_CHANGESKIN] = new CL_Sprite("menu/options/changeskin/unselected", &gfx);
  items_selected[OPTIONS_ITEM_CHANGESKIN] = new CL_Sprite("menu/options/changeskin/selected", &gfx);

  items[OPTIONS_ITEM_FULLSCREEN] = new CL_Sprite("menu/options/fullscreen/unselected", &gfx);
  items_selected[OPTIONS_ITEM_FULLSCREEN] = new CL_Sprite("menu/options/fullscreen/selected", &gfx);

  items[OPTIONS_ITEM_SOUND] = new CL_Sprite("menu/options/sound/unselected", &gfx);
  items_selected[OPTIONS_ITEM_SOUND] = new CL_Sprite("menu/options/sound/selected", &gfx);

  items[OPTIONS_ITEM_MUSIC] = new CL_Sprite("menu/options/music/unselected", &gfx);
  items_selected[OPTIONS_ITEM_MUSIC] = new CL_Sprite("menu/options/music/selected", &gfx);

  items[OPTIONS_ITEM_QUIT] = new CL_Sprite("menu/options/quit/unselected", &gfx);
  items_selected[OPTIONS_ITEM_QUIT] = new CL_Sprite("menu/options/quit/selected", &gfx);

  
  for(int i=0; i<=10; ++i)
  {
    sound_level_sprites[i] = new CL_Sprite("menu/options/sound-level/"+to_string(i), &gfx);
  }


  // Then, propreties
 
  items_left[OPTIONS_ITEM_CHANGESKIN] = CL_Integer_to_int("menu/options/changeskin/left", &gfx);
  items_top[OPTIONS_ITEM_CHANGESKIN] = CL_Integer_to_int("menu/options/changeskin/top", &gfx);

  items_left[OPTIONS_ITEM_FULLSCREEN] = CL_Integer_to_int("menu/options/fullscreen/left", &gfx);
  items_top[OPTIONS_ITEM_FULLSCREEN] = CL_Integer_to_int("menu/options/fullscreen/top", &gfx);

  items_left[OPTIONS_ITEM_SOUND] = CL_Integer_to_int("menu/options/sound/left", &gfx);
  items_top[OPTIONS_ITEM_SOUND] = CL_Integer_to_int("menu/options/sound/top", &gfx);

  items_left[OPTIONS_ITEM_MUSIC] = CL_Integer_to_int("menu/options/music/left", &gfx);
  items_top[OPTIONS_ITEM_MUSIC] = CL_Integer_to_int("menu/options/music/top", &gfx);

  items_left[OPTIONS_ITEM_QUIT] = CL_Integer_to_int("menu/options/quit/left", &gfx);
  items_top[OPTIONS_ITEM_QUIT] = CL_Integer_to_int("menu/options/quit/top", &gfx);
  

  sound_level_left = CL_Integer_to_int("menu/options/sound-level/left", &gfx);

  
}

void OptionsMenuState::unload_gfx()
{

}

void OptionsMenuState::draw()
{
  int x = 400 - background -> get_width()/2;
  int y = 300 - background -> get_height()/2;
  background -> draw(x,y);

  // Drawing 
  for(int i=0; i<OPTIONS_NUMBER_OF_ITEMS; ++i)
  {

    if(i == selection)
    {
      items_selected[i] -> draw(x + items_left[i], y + items_top[i]);
      items_selected[i] -> update();
     
    }
    else
    {
        items[i] -> draw(x + items_left[i], y + items_top[i]);
        items[i] -> update();
    }
  }

  sound_level_sprites[sound_level] -> draw(x + sound_level_left, y 
                                           + items_top[OPTIONS_ITEM_SOUND]);
  sound_level_sprites[music_level] -> draw(x + sound_level_left, y 
                                           + items_top[OPTIONS_ITEM_MUSIC]);
  sound_level_sprites[sound_level] -> update();
  sound_level_sprites[music_level] -> update();

}

void OptionsMenuState::update()
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

void OptionsMenuState::events()
{
  if(step != STEP_NORMAL)
    return;

  if(common_resources -> key.echap->get())
  {   
    step = STEP_DISAPPEARING;
    selection = -1;
  }

  if(common_resources -> key.skins->get())
  {   
    step = STEP_DISAPPEARING;
    //selection = OPTIONS_ITEM_OPTIONS;
  }
  if(common_resources -> key.up -> get())
  {
    if(selection == 0)
      selection = OPTIONS_ITEM_QUIT;
    else
    {
      selection --;
    }
  }

  if(common_resources -> key.down -> get())
  {
    if(selection == OPTIONS_ITEM_QUIT)
      selection = 0;
    else
    {
      selection ++;
    }
  }

  if(selection == OPTIONS_ITEM_SOUND && common_resources -> key.left -> get())
  {
    if(sound_level > 0)
      sound_level--;
  }

  if(selection == OPTIONS_ITEM_SOUND && common_resources -> key.right -> get())
  {
    if(sound_level < 10)
      sound_level++;
  }

  if(selection == OPTIONS_ITEM_MUSIC && common_resources -> key.left -> get())
  {
    if(music_level > 0)
      music_level--;
  }

  if(selection == OPTIONS_ITEM_MUSIC && common_resources -> key.right -> get())
  {
    if(music_level < 10)
      music_level++;
  }

  if(common_resources -> key.enter -> get())
  {    
    switch(selection)
    {
    case OPTIONS_ITEM_FULLSCREEN:
      common_resources -> engine -> toggle_screen();
      break;
    case OPTIONS_ITEM_CHANGESKIN:
    case OPTIONS_ITEM_QUIT:
      step = STEP_DISAPPEARING;
      break;
    }

  }
}

void OptionsMenuState::appear()
{ 
  if(alpha + APPEARING_SPEED*common_resources -> time_interval >= 1.0)
  {
    step = STEP_NORMAL;
    alpha = 1.0;
  }
  else
    alpha += APPEARING_SPEED * common_resources -> time_interval;

  background -> set_alpha(alpha);

  for(int i=0; i<OPTIONS_NUMBER_OF_ITEMS; ++i)
  {
    items[i] -> set_alpha(alpha);
    items_selected[i] -> set_alpha(alpha);
  }

  sound_level_sprites[sound_level] -> set_alpha(alpha);
  sound_level_sprites[music_level] -> set_alpha(alpha);

}

void OptionsMenuState::disappear()
{  
  alpha -= APPEARING_SPEED * common_resources -> time_interval;

  background -> set_alpha(alpha);

  for(int i=0; i<OPTIONS_NUMBER_OF_ITEMS; ++i)
  {
    items[i] -> set_alpha(alpha);
    items_selected[i] -> set_alpha(alpha);
  }

  sound_level_sprites[sound_level] -> set_alpha(alpha);
  sound_level_sprites[music_level] -> set_alpha(alpha);


  if(alpha <= 0.0 || !common_resources -> engine -> is_opengl_used())
  {
    switch(selection)
    {
    case OPTIONS_ITEM_CHANGESKIN:
      common_resources -> engine -> set_state_skin_menu();
      break;
    default:
      common_resources -> engine -> stop_current_state();           
    }
  }
 
}

void OptionsMenuState::start()
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

bool OptionsMenuState::front_layer_behind()
{
  return true;
}

OptionsMenuState::OptionsMenuState()
{

}

OptionsMenuState::~OptionsMenuState()
{
  deinit();
}



