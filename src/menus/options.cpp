/* OpenAlchemist - just a simple game 
 * ----------------------------------
 *
 * Copyright (C) 2006 Guillaume Delhumeau <guillaume.delhumeau@gmail.com>
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.
 */

#include "headers.h"

#define OPTIONS_ITEM_RESUME 0
#define OPTIONS_ITEM_CHANGESKIN 1
#define OPTIONS_ITEM_FULLSCREEN 2
#define OPTIONS_ITEM_SOUND 3
#define OPTIONS_ITEM_MUSIC 4


void OptionsMenu::load_gfx(CL_ResourceManager *gfx_options)
{
  // First, the sprites
  background = new CL_Sprite("menu/options/background", gfx_options); 

  items[OPTIONS_ITEM_RESUME] = new CL_Sprite("menu/options/resume/unselected", gfx_options);
  items_selected[OPTIONS_ITEM_RESUME] = new CL_Sprite("menu/options/resume/selected", gfx_options);

  items[OPTIONS_ITEM_CHANGESKIN] = new CL_Sprite("menu/options/changeskin/unselected", gfx_options);
  items_selected[OPTIONS_ITEM_CHANGESKIN] = new CL_Sprite("menu/options/changeskin/selected", gfx_options);

  items[OPTIONS_ITEM_FULLSCREEN] = new CL_Sprite("menu/options/fullscreen/unselected", gfx_options);
  items_selected[OPTIONS_ITEM_FULLSCREEN] = new CL_Sprite("menu/options/fullscreen/selected", gfx_options);

  items[OPTIONS_ITEM_SOUND] = new CL_Sprite("menu/options/sound/unselected", gfx_options);
  items_selected[OPTIONS_ITEM_SOUND] = new CL_Sprite("menu/options/sound/selected", gfx_options);

  items[OPTIONS_ITEM_MUSIC] = new CL_Sprite("menu/options/music/unselected", gfx_options);
  items_selected[OPTIONS_ITEM_MUSIC] = new CL_Sprite("menu/options/music/selected", gfx_options);

  
  for(int i=0; i<=10; ++i)
  {
    sound_level[i] = new CL_Sprite("menu/options/sound-level/"+to_string(i), gfx_options);
  }


  // Then, propreties
  items_left[OPTIONS_ITEM_RESUME] = CL_Integer_to_int("menu/options/resume/left", gfx_options);
  items_top[OPTIONS_ITEM_RESUME] = CL_Integer_to_int("menu/options/resume/top", gfx_options);

  items_left[OPTIONS_ITEM_CHANGESKIN] = CL_Integer_to_int("menu/options/changeskin/left", gfx_options);
  items_top[OPTIONS_ITEM_CHANGESKIN] = CL_Integer_to_int("menu/options/changeskin/top", gfx_options);

  items_left[OPTIONS_ITEM_FULLSCREEN] = CL_Integer_to_int("menu/options/fullscreen/left", gfx_options);
  items_top[OPTIONS_ITEM_FULLSCREEN] = CL_Integer_to_int("menu/options/fullscreen/top", gfx_options);

  items_left[OPTIONS_ITEM_SOUND] = CL_Integer_to_int("menu/options/sound/left", gfx_options);
  items_top[OPTIONS_ITEM_SOUND] = CL_Integer_to_int("menu/options/sound/top", gfx_options);

  items_left[OPTIONS_ITEM_MUSIC] = CL_Integer_to_int("menu/options/music/left", gfx_options);
  items_top[OPTIONS_ITEM_MUSIC] = CL_Integer_to_int("menu/options/music/top", gfx_options);
  

  sound_level_left = CL_Integer_to_int("menu/options/sound-level/left", gfx_options);

  if(CL_Boolean_to_bool("menu/options/alpha_appearing", gfx_options))
  {
    appearing = true;
    max_alpha =(float)CL_Integer_to_int("menu/options/alpha_max", gfx_options) / 100.0;
  }
  else
    appearing = false;

}


void OptionsMenu::unload_gfx()
{
  delete background;

  for(int i=0; i<OPTIONS_NUMBER_OF_ITEMS; ++i)
  {
    delete items[i];
    delete items_selected[i];
  }

  for(int i=0; i<=10; i++)
  {
    delete sound_level[i];
  }

}


void Game::draw_options_menu()
{
  if(MENU_STEP_APPEARING == options.step)
  {
    if(options.alpha+0.003*time_interval >= options.max_alpha)
    {
      options.step = MENU_STEP_MENU;
      options.alpha = 1.0;
    }
    options.alpha += 0.003*time_interval;

    int x = 400 - options.background -> get_width()/2;
    int y = 300 - options.background -> get_height()/2;
    options.background -> set_alpha(options.alpha);
    options.background -> draw(x,y);

    for(int i=0; i<OPTIONS_NUMBER_OF_ITEMS; ++i)
    {
      options.items[i] -> set_alpha(options.alpha);
      options.items_selected[i] -> set_alpha(options.alpha);
    }

  
    options.sound_level[sound_level] -> set_alpha(options.alpha);
    options.sound_level[music_level] -> set_alpha(options.alpha);


  }
  else if(MENU_STEP_DISAPPEARING == options.step)
  {
    options.alpha -= 0.007*time_interval;
    if(options.alpha <= 0.0)
    {
      options.is_optionsd = false;
      playable = true;
    }

    int x = 400 - options.background -> get_width()/2;
    int y = 300 - options.background -> get_height()/2;
    options.background -> set_alpha(options.alpha);
    options.background -> draw(x,y);    

    for(int i=0; i<OPTIONS_NUMBER_OF_ITEMS; ++i)
    {
      options.items[i] -> set_alpha(options.alpha);
      options.items_selected[i] -> set_alpha(options.alpha);
    }
   
       
    options.sound_level[sound_level] -> set_alpha(options.alpha);
    options.sound_level[music_level] -> set_alpha(options.alpha);
    
    
  }

    int x = 400 - options.background -> get_width()/2;
    int y = 300 - options.background -> get_height()/2;
    options.background -> draw(x,y);
    options.background -> update();


    // Drawing 
    for(int i=0; i<OPTIONS_NUMBER_OF_ITEMS; ++i)
    {

      if(i == options.selection)
      {
        options.items_selected[i] -> draw(x + options.items_left[i], y + options.items_top[i]);
        options.items_selected[i] -> update();
     
      }
      else
      {
          options.items[i] -> draw(x + options.items_left[i], y + options.items_top[i]);
          options.items[i] -> update();
       
        }
    }
    


    options.sound_level[sound_level] -> draw(x + options.sound_level_left, y 
                                           + options.items_top[OPTIONS_ITEM_SOUND]);
    options.sound_level[music_level] -> draw(x + options.sound_level_left, y 
                                           + options.items_top[OPTIONS_ITEM_MUSIC]);
    options.sound_level[sound_level] -> update();
    options.sound_level[music_level] -> update();

  
}

void Game::key_events_options_menu()
{
  if(options.step == MENU_STEP_APPEARING)
    return;
   
  if(key.echap->get())
  {   
    if(options.appearing && opengl)
      options.step = MENU_STEP_DISAPPEARING;
    else
    {
      options.is_optionsd = false;
      playable = true;
    }
    
  }


  if(options.selection == OPTIONS_ITEM_SOUND && key.left -> get())
  {
    if(sound_level > 0)
      sound_level--;
  }

  if(options.selection == OPTIONS_ITEM_SOUND && key.right -> get())
  {
    if(sound_level < 10)
      sound_level++;
  }

  if(options.selection == OPTIONS_ITEM_MUSIC && key.left -> get())
  {
    if(music_level > 0)
      music_level--;
  }

  if(options.selection == OPTIONS_ITEM_MUSIC && key.right -> get())
  {
    if(music_level < 10)
      music_level++;
  }

  if(key.down -> get())
  {
    if(options.selection == OPTIONS_ITEM_MUSIC)
      options.selection = 0;
    else
      options.selection++;

  }
  
   if(key.up -> get())
  {
    if(options.selection == 0)
      options.selection = OPTIONS_ITEM_MUSIC;
    else
        options.selection--;

  }
  

  if(key.enter -> get())
  {
    switch(options.selection)
    {
    case OPTIONS_ITEM_RESUME:
      if(options.appearing && opengl)
        options.step = MENU_STEP_DISAPPEARING;
      else
        options.is_optionsd = false;
        playable = true;
      break;
    case OPTIONS_ITEM_CHANGESKIN:
      choose_skin();
      break;
    case OPTIONS_ITEM_FULLSCREEN:
      toggle_screen();
      break;
    }
  }



}
