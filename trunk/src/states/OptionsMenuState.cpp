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
  
  _sound_level = pref -> sound_level;
  _music_level = pref -> music_level;
}

void OptionsMenuState::deinit()
{
  Preferences *pref = pref_get_instance();
  
  pref -> sound_level = _sound_level;
  pref -> music_level = _music_level;

  pref -> write();
}

void OptionsMenuState::load_gfx(std::string skin)
{
  // Getting skins resources
  CL_Zip_Archive zip(skin);
  CL_ResourceManager gfx("menu_options.xml", &zip, false);

  // First, the sprites
  _p_background = new CL_Sprite("menu_options/dialog_background", &gfx); 

  _items_p[OPTIONS_ITEM_CHANGESKIN] = new CL_Sprite("menu_options/changeskin/unselected", &gfx);
  _items_selected_p[OPTIONS_ITEM_CHANGESKIN] = new CL_Sprite("menu_options/changeskin/selected", &gfx);

  _items_p[OPTIONS_ITEM_FULLSCREEN] = new CL_Sprite("menu_options/fullscreen/unselected", &gfx);
  _items_selected_p[OPTIONS_ITEM_FULLSCREEN] = new CL_Sprite("menu_options/fullscreen/selected", &gfx);

  _items_p[OPTIONS_ITEM_SOUND] = new CL_Sprite("menu_options/sound/unselected", &gfx);
  _items_selected_p[OPTIONS_ITEM_SOUND] = new CL_Sprite("menu_options/sound/selected", &gfx);

  _items_p[OPTIONS_ITEM_MUSIC] = new CL_Sprite("menu_options/music/unselected", &gfx);
  _items_selected_p[OPTIONS_ITEM_MUSIC] = new CL_Sprite("menu_options/music/selected", &gfx);

  _items_p[OPTIONS_ITEM_QUIT] = new CL_Sprite("menu_options/quit/unselected", &gfx);
  _items_selected_p[OPTIONS_ITEM_QUIT] = new CL_Sprite("menu_options/quit/selected", &gfx);

  
  for(int i=0; i<=10; ++i)
  {
    _sound_level_sprites_p[i] = new CL_Sprite("menu_options/sound_level/"+to_string(i), &gfx);
  }


  // Then, propreties
 
  _items_left[OPTIONS_ITEM_CHANGESKIN] = CL_Integer_to_int("menu_options/changeskin/left", &gfx);
  _items_top[OPTIONS_ITEM_CHANGESKIN] = CL_Integer_to_int("menu_options/changeskin/top", &gfx);

  _items_left[OPTIONS_ITEM_FULLSCREEN] = CL_Integer_to_int("menu_options/fullscreen/left", &gfx);
  _items_top[OPTIONS_ITEM_FULLSCREEN] = CL_Integer_to_int("menu_options/fullscreen/top", &gfx);

  _items_left[OPTIONS_ITEM_SOUND] = CL_Integer_to_int("menu_options/sound/left", &gfx);
  _items_top[OPTIONS_ITEM_SOUND] = CL_Integer_to_int("menu_options/sound/top", &gfx);

  _items_left[OPTIONS_ITEM_MUSIC] = CL_Integer_to_int("menu_options/music/left", &gfx);
  _items_top[OPTIONS_ITEM_MUSIC] = CL_Integer_to_int("menu_options/music/top", &gfx);

  _items_left[OPTIONS_ITEM_QUIT] = CL_Integer_to_int("menu_options/quit/left", &gfx);
  _items_top[OPTIONS_ITEM_QUIT] = CL_Integer_to_int("menu_options/quit/top", &gfx);
  

  _sound_level_left = CL_Integer_to_int("menu_options/sound_level/left", &gfx);

  
}

void OptionsMenuState::unload_gfx()
{

}

void OptionsMenuState::draw()
{
  int x = 400 - _p_background -> get_width()/2;
  int y = 300 - _p_background -> get_height()/2;
  _p_background -> draw(x,y);

  // Drawing 
  for(int i=0; i<OPTIONS_NUMBER_OF_ITEMS; ++i)
  {

    if(i == _selection)
    {
      _items_selected_p[i] -> draw(x + _items_left[i], y + _items_top[i]);
      _items_selected_p[i] -> update(_p_common_resources -> time_interval);
     
    }
    else
    {
        _items_p[i] -> draw(x + _items_left[i], y + _items_top[i]);
        _items_p[i] -> update(_p_common_resources -> time_interval);
    }
  }

  _sound_level_sprites_p[_sound_level] -> draw(x + _sound_level_left, y 
                                           + _items_top[OPTIONS_ITEM_SOUND]);
  _sound_level_sprites_p[_music_level] -> draw(x + _sound_level_left, y 
                                           + _items_top[OPTIONS_ITEM_MUSIC]);
  _sound_level_sprites_p[_sound_level] -> update();
  _sound_level_sprites_p[_music_level] -> update();

}

void OptionsMenuState::update()
{
  switch(_step)
  {
  case STEP_APPEARING:
    _appear();
    break;
  case STEP_DISAPPEARING:
    _disappear();
    break;
  }
}

void OptionsMenuState::events()
{
  if(_step != STEP_NORMAL)
    return;

  if(_p_common_resources -> key.escape -> get() || _p_common_resources -> key.options -> get())
  {   
    _step = STEP_DISAPPEARING;
    _selection = OPTIONS_ITEM_QUIT;
  }

  if(_p_common_resources -> key.skins -> get())
  {   
    _step = STEP_DISAPPEARING;
  }
  if(_p_common_resources -> key.up -> get())
  {
    if(_selection == 0)
      _selection = OPTIONS_ITEM_QUIT;
    else
    {
      _selection --;
    }
  }

  if(_p_common_resources -> key.down -> get())
  {
    if(_selection == OPTIONS_ITEM_QUIT)
      _selection = 0;
    else
    {
      _selection ++;
    }
  }

  if(_selection == OPTIONS_ITEM_SOUND && _p_common_resources -> key.left -> get())
  {
    if(_sound_level > 0)
      _sound_level--;
  }

  if(_selection == OPTIONS_ITEM_SOUND && _p_common_resources -> key.right -> get())
  {
    if(_sound_level < 10)
      _sound_level++;
  }

  if(_selection == OPTIONS_ITEM_MUSIC && _p_common_resources -> key.left -> get())
  {
    if(_music_level > 0)
      _music_level--;
  }

  if(_selection == OPTIONS_ITEM_MUSIC && _p_common_resources -> key.right -> get())
  {
    if(_music_level < 10)
      _music_level++;
  }

  if(_p_common_resources -> key.enter -> get())
  {    
    switch(_selection)
    {
    case OPTIONS_ITEM_FULLSCREEN:
      _p_common_resources -> p_engine -> toggle_screen();
      break;
    case OPTIONS_ITEM_CHANGESKIN:
    case OPTIONS_ITEM_QUIT:
      _step = STEP_DISAPPEARING;
      break;
    }

  }
}

void OptionsMenuState::_appear()
{ 
  if(_alpha + APPEARING_SPEED*_p_common_resources -> time_interval >= 1.0)
  {
    _step = STEP_NORMAL;
    _alpha = 1.0;
  }
  else
    _alpha += APPEARING_SPEED * _p_common_resources -> time_interval;

  _p_background -> set_alpha(_alpha);

  for(int i=0; i<OPTIONS_NUMBER_OF_ITEMS; ++i)
  {
    _items_p[i] -> set_alpha(_alpha);
    _items_selected_p[i] -> set_alpha(_alpha);
  }

  _sound_level_sprites_p[_sound_level] -> set_alpha(_alpha);
  _sound_level_sprites_p[_music_level] -> set_alpha(_alpha);

}

void OptionsMenuState::_disappear()
{  
  _alpha -= APPEARING_SPEED * _p_common_resources -> time_interval;

  _p_background -> set_alpha(_alpha);

  for(int i=0; i<OPTIONS_NUMBER_OF_ITEMS; ++i)
  {
    _items_p[i] -> set_alpha(_alpha);
    _items_selected_p[i] -> set_alpha(_alpha);
  }

  _sound_level_sprites_p[_sound_level] -> set_alpha(_alpha);
  _sound_level_sprites_p[_music_level] -> set_alpha(_alpha);


  if(_alpha <= 0.0 || !_p_common_resources -> p_engine -> is_opengl_used())
  {
    switch(_selection)
    {
    case OPTIONS_ITEM_CHANGESKIN:
      _p_common_resources -> p_engine -> stop_current_state();
      _p_common_resources -> p_engine -> set_state_skin_menu();
      break;
    default:
      _p_common_resources -> p_engine -> stop_current_state();           
    }
  }
 
}

void OptionsMenuState::start()
{
  _selection = 0;
  if(_p_common_resources -> p_engine -> is_opengl_used())
  {
    _step = STEP_APPEARING;
    _alpha = 0.0;
  }
  else
  {
    _step = STEP_NORMAL;
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



